#include <stdio.h>
#include <stdlib.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "tsi148.h"
#include "cio32.h"
#include "ip235.h"
#include "avme9630.h"
#include "interrupt.h"
#include "set_master.h"
#include "set_slave.h"
#include <pthread.h>
#include <sched.h>


struct pci_dev_info info;

struct cio32IOSpace cio_io_space;
struct cio32IDSpace cio_id_space;
struct ip235IOSpace ip_io_space;
struct ip235IDSpace ip_id_space;
struct avmeIO_memorymap *avme9630_mm_space;

volatile struct TSI148* deviceRegisters;
volatile int tsi148_intl=0;
int16_t IP235_Data[4096]={0};
int16_t temp[4096]={0};

int main(void)
{
	int hpci;
	int i,j;
	int16_t sample;
	void* hdev;
	pthread_t           threadID [0];  // a place to hold the thread ID's
	pthread_attr_t      attrib;                 // scheduling attributes
	struct sched_param  param;                  // for setting priority
	int                  policy;

	uint8_t* master0 = NULL;
	uint32_t* master1 = NULL;
	uint32_t* slave1 = NULL;
	int64_t ph_addr;
	uint32_t tmp;

	printf("Avme9660 Memory Map Space size: %d, %x\n",sizeof(avme9630_mm_space),offsetof(struct avme9630MMSpace, IP_ICR));
	//clear PCI device info structure
	memset(&info, 0, sizeof(info));

	//fill structure fields .VendorId and .DeviceId data from Tsi148 manual
	info.VendorId = VENDOR_ID;
	info.DeviceId = DEVICE_ID;

	//connect to pci server
	hpci = pci_attach(NULL);
	if(hpci != -1)
	{
		int pidx = 0;
		//Attach a driver to a PCI device and fill info structure
		hdev = pci_attach_device(NULL, (PCI_SEARCH_VENDEV | PCI_INIT_ALL), pidx, &info);
		if(hdev != NULL)
		{
			//Get physical address of the Tsi148 bridge
			ph_addr = GetBaseAddress(&info);

			//translate physical address to virtual address
			deviceRegisters = (struct TSI148 *)mmap_device_memory(
					NULL,
					sizeof(tsi148_reg),
					PROT_NOCACHE | PROT_READ | PROT_WRITE,
					MAP_SHARED,
					ph_addr);

			//Dostep do rejestrów:
			//printf("Vendor ID: 0x%X, Device ID: 0x%X.\n", deviceRegisters->pcfs.veni, deviceRegisters->pcfs.devi);
			//printf("Reg Size: %d\n",sizeof(tsi148_reg));
			//printf("Virtual address: %p, IntL: %X, IntP: %X\n", (void *)deviceRegisters, deviceRegisters->pcfs.intl, deviceRegisters->pcfs.intp);

			//Marek Sudol
			//Bartosz Konikowski
			//17.02.2020
			//Inicjalizacia przerwan
			tmp=(deviceRegisters->lcsr.ints&0xFF000000);
			deviceRegisters->lcsr.inteo = 0x00;
			deviceRegisters->lcsr.inten = 0x00;

			tmp = deviceRegisters->lcsr.vicr;
			tmp &= 0x700000;
			tmp >>= 20;

			if(tmp) tmp=deviceRegisters->lcsr.viack[1];

			/* Set BusMastering */
			Tsi148BusMastering((struct TSI148 *)deviceRegisters);

			/* Set Master Channel 0 */
			uint8_t* master0;
			int offset_upper = 0;
			int offset_lower = 0;

			master0 = (uint8_t*) set_master((struct TSI148 *) deviceRegisters, 0, 0, 0xC1000000, 0, 0xC1010000, offset_upper, offset_lower, 0, (0<<8));

			/* Set Addresses Master Channel 0 */
			//SetMasterAdress((struct TSI148 *)deviceRegisters, 0, 0, 0xC1000000, 0x10000, 0, (0xC1000000 * (-1)));

			/* Set Attributes Master Channel 0 */
//			master0 = (uint8_t *)SetMasterAttr((struct TSI148 *)deviceRegisters, 0, MasterFlag_AMODE_A16 | MasterFlag_DBW_D16,
//							0, 0xC1000000, 0x10000);
//			avme9630_mm_space = (struct avmeIO_memorymap *)SetMasterAttr((struct TSI148 *)deviceRegisters, 0, MasterFlag_AMODE_A16 | MasterFlag_DBW_D16,
//										        0, 0xC1000000, 0x10000);

			avme9630_mm_space=(struct avmeIO_memorymap *)master0;

			printf("IP MEM ID: %c", avme9630_mm_space->IP_A_ID.ASCII_I);
			printf("%c", avme9630_mm_space->IP_A_ID.ASCII_P);
			printf("%c", avme9630_mm_space->IP_A_ID.ASCII_A);
			printf("%c, Vendor ID: 0x%X, Model ID: 0x%X.\n", avme9630_mm_space->IP_A_ID.ASCII_C, avme9630_mm_space->IP_A_ID.ACROMAG_ID_CODE,
					                                        avme9630_mm_space->IP_A_ID.IP_MODEL_CODE);

			for(i=0;i<2048;i++){
			   temp[i]=(int16_t)(32760.0*sin(2.0*M_PI*10.0*(double)i/2048.0));
			   IP235_Data[i]=((temp[i]&0xFF00)>>8)+((temp[i]&0x00FF)<<8);
			}

			pthread_getschedparam( pthread_self(), &policy, &param );

			pthread_attr_init (&attrib);
			pthread_attr_setinheritsched (&attrib, PTHREAD_EXPLICIT_SCHED);
			pthread_attr_setschedpolicy (&attrib, SCHED_RR);
			param.sched_priority -= 2;      // drop priority a couple levels
			pthread_attr_setschedparam (&attrib, &param);

			pthread_create (&threadID [0], &attrib, &tsiInterrupt, NULL);

//			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x0080;
//			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x1105;
//			avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_ADDRESS_REGISTER = 0x0;
//			for(i=0;i<2048;i++){
//			   avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_DATA_REGISTER=IP235_Data[i];
//			}
//
//			avme9630_mm_space->IP_A_IO.TIMER_PRESCALER = 0x3500;
//			avme9630_mm_space->IP_A_IO.CONVERSION_TIMER = 0x0100;
//			avme9630_mm_space->IP_A_IO.START_CONVERT = 0x0100;

/*
			uint8_t temp = 0;
			master0 += 129;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c\n", temp);
*/
//			sleep(10);
//			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x0080;
//
//			sleep(5);
//
//			for(i=0;i<2048;i++){
//			   temp[i]=(int16_t)(32760.0*sin(2.0*M_PI*10.0*(double)i/2048.0));
//			   IP235_Data[i]=((temp[i]&0xFF00)>>8)+((temp[i]&0x00FF)<<8);
//			}
//
//			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x0080;
//			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x1105;
//			avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_ADDRESS_REGISTER = 0x0;
//			for(i=0;i<2048;i++){
//			   avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_DATA_REGISTER=IP235_Data[i];
//			}
//
//			avme9630_mm_space->IP_A_IO.TIMER_PRESCALER = 0x3500;
//			avme9630_mm_space->IP_A_IO.CONVERSION_TIMER = 0x0100;
//			avme9630_mm_space->IP_A_IO.START_CONVERT = 0x0100;

/*
			uint8_t temp = 0;
			master0 += 129;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c", temp);
			master0 += 2;
			temp = *master0;
			printf("%c\n", temp);
*/
			sleep(10);
			avme9630_mm_space->IP_A_IO.CONTROL_REGISTER = 0x0080;

			pci_detach_device(hdev);
		}
		else
		{
			printf("Error code %x, implies %s\n",errno,sys_errlist[errno]);
		}

		pci_detach(hpci);
	}
	else
	{
		printf("Cannot attach to PCI Bus\n");
	}


	return EXIT_SUCCESS;
}
//2048 16 bit
