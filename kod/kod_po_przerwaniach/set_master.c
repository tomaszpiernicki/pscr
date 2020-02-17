#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include "set_master.h"
#include "convert_endian.h"
#include "tsi148.h"

void Tsi148BusMastering(struct TSI148* tsi148ptr) {
	uint32_t temp = tsi148ptr->pcfs.cmmd;
	temp |= (0x06);
	tsi148ptr->pcfs.cmmd = temp;
}

void* set_master (	struct TSI148* tsi148ptr,		// wskaźnik na tsi148
					int nr, 				        // numer mastera                (max 8x master: [0-7])
					unsigned int start_addr_upper, 	// poczatek adresu gorny        (Start Address Upper)
					unsigned int start_addr_lower, 	// poczatek adresu dolny        (Start Address Lower)
					unsigned int end_addr_upper,	// koniec adresu gorny          (End Address Upper)
					unsigned int end_addr_lower, 	// koniec adresu dolny          (End Address Lower)
					unsigned int offset_upper, 	    // offset gorny                 (Translation Offset Upper)
					unsigned int offset_lower,	    // offset dolny                 (Translation Offset Lower)
					unsigned int sst, 		        // wybor trybu nadawania 2eSST  (2eSST Broadcast Select)
					unsigned int attrib 	        // atrybuty translacji          (Translation attribute)
					)
                    {

    uint64_t addr_s;
    uint64_t addr_k;
    uint64_t addr;

	switch (nr) {
        case 0:
            tsi148ptr->lcsr.otrans[0].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[0].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[0].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[0].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[0].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[0].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[0].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[0].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            uint32_t d32;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[0].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[0].otat=convert_endian(d32);
            return mmap_device_memory( NULL, end_addr_lower - start_addr_lower, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, addr_s );
            break;

        case 1:
            tsi148ptr->lcsr.otrans[1].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[1].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[1].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[1].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[1].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[1].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[1].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[1].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[1].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[1].otat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED, addr_s );
            break;

        case 2:
            tsi148ptr->lcsr.otrans[2].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[2].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[2].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[2].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[2].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[2].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[2].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[2].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[2].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[2].otat=convert_endian(d32);
            return mmap_device_memory( 2, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 3:
            tsi148ptr->lcsr.otrans[3].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[3].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[3].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[3].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[3].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[3].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[3].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[3].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[3].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[3].otat=convert_endian(d32);
            return mmap_device_memory( 3, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 4:
            tsi148ptr->lcsr.otrans[4].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[4].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[4].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[4].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[4].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[4].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[4].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[4].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[4].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[4].otat=convert_endian(d32);
            return mmap_device_memory( 4, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 5:
            tsi148ptr->lcsr.otrans[5].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[5].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[5].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[5].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[5].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[5].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[5].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[5].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[5].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[5].otat=convert_endian(d32);
            return mmap_device_memory( 5, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 6:
            tsi148ptr->lcsr.otrans[6].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[6].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[6].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[6].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[6].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[6].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[6].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[6].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[6].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[6].otat=convert_endian(d32);
            return mmap_device_memory( 6, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 7:
            tsi148ptr->lcsr.otrans[7].otsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.otrans[7].otsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.otrans[7].oteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.otrans[7].oteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.otrans[7].otofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.otrans[7].otofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.otrans[7].otbs=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.otrans[7].otat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.otrans[7].otat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.otrans[7].otat=convert_endian(d32);
            return mmap_device_memory( 7, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;
	}
}
