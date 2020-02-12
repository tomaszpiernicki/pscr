//#include <stdlib.h>
//#include <stdio.h>
//#include <stdio.h>
//#include <stdint.h>
//#include <stddef.h>
#include <hw/pci.h>
#include <hw/pci_devices.h>
#include <sys/mman.h>
#include "dev_mem.h"
#include "set_master.h"
#include "set_slave.h"

int main(int argc, uint8_t *argv[])
{
    printf("TESTING ATTENTION PLEASE!\n");

    printf("PCFS offset: %d\n", offsetof(dev_mem_t, pcfs) );
    printf("PCFS size: %d\n\n", sizeof(  pcfs_t) );

    printf("lcsr offset: %d\n", offsetof(dev_mem_t, lcsr) );
    printf("lcsr size: %d\n\n", sizeof(  lcsr_t) );

    printf("gcsr offset: %d\n", offsetof( dev_mem_t, gcsr) );
    printf("gcsr size: %d\n\n", sizeof(  gcsr_t) );

    printf("rsvd offset: %d\n\n", offsetof( dev_mem_t, rsvd) );

    printf("rcsrc offset: %d\n", offsetof( dev_mem_t, rcsrc) );
    printf("rcsrc size: %d\n\n", sizeof(  crcsr_t) );

    printf("full size: %d\n\n", sizeof(  dev_mem_t) );

    int pidx;
    void* hdl;
    int phdl;
    
    //Uchwyt do magistrali pci
	phdl = pci_attach( 0 );
	
    if( phdl == -1 ) {
        fprintf( stderr, "Unable to initialize PCI\n" );

        return EXIT_FAILURE;
    }

    memset( &inf, 0, sizeof( inf ) );
    pidx = 0;
	
	//wyszukiwanie urządzenia po id dostawcy oraz id urządzenia.
    inf.VendorId = 0x10E3; //Tsi148_User_Manaul strona 213
    inf.DeviceId = 0x0148;

	//Wypełnienie struktury pci_dev_info resztą danych
    hdl = pci_attach_device( NULL, PCI_INIT_ALL, pidx, &inf );
	
	
    if( hdl == NULL ) {
        fprintf( stderr, "Błąd, nie można zlokalizować adaptera\n" );
    } else {
		//adres linii przerwań
        uint32_t irq = inf.Irq;

        uint32_t base_address[2];

        uint32_t offset = offsetof(struct pci_dev_info, PciBaseAddress);

		//wypełnienie base_adress
        uint32_t status = pci_read_config32(inf.BusNumber, inf.DevFunc, 0x10, 2, &base_address );

        base_address[0] &= 0xFFFFF000;


        uint64_t base_address_concatenated = (base_address[1] << 32) + base_address[0];
        dev_mem_t* dev_mem = NULL;

		//zmapowanie pamięci do struktury utworzonej do nas.
        dev_mem = (struct dev_mem_t*) mmap_device_memory(NULL, 4096,PROT_NOCACHE | PROT_READ | PROT_WRITE, MAP_SHARED, base_address_concatenated );

		//sprawdzenie.
        printf("Veni: %x Devi: %x\n", dev_mem->pcfs.devi_veni & 0x0000FFFF, (dev_mem->pcfs.devi_veni & 0xFFFF0000) >> 16);

        // ustawienie szyny dla master/slave
        bus_mastering((struct dev_mem_t*) dev_mem);

        // ustawienie mastera z parametrami
        uint8_t* master0;
        int offset_upper = 0;
        int offset_lower = 0;

        master0 = (uint8_t*) set_master((struct dev_mem_t*) dev_mem, 0, 0, 0xC1000000, 0, 0xC1010000, offset_upper, offset_lower, 0, (0<<8));

        //zwolnienie zasobów
        pci_detach_device( hdl );
        pci_detach( phdl );
    }
    return 0;
}

