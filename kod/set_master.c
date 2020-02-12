/*
 * Cezary Pietrzak, 160667
 * Martyna Kulbacka, 160515
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include "set_master.h"
#include "convert_endian.h"
#include "dev_mem.h"

void bus_mastering (struct dev_mem_t* tsi148ptr) {
	uint32_t temp = tsi148ptr->pcfs.stat_cmmd;
	temp |= (0x06);
    tsi148ptr->pcfs.stat_cmmd = temp;
}

void* set_master (	struct dev_mem_t* tsi148ptr,    // wskaźnik na tsi148
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
            tsi148ptr->lcsr.out_trans[0].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[0].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[0].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[0].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[0].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[0].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[0].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[0].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            uint32_t d32;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[0].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[0].OTAT=convert_endian(d32);
            return mmap_device_memory( NULL, end_addr_lower - start_addr_lower, PROT_READ|PROT_WRITE|PROT_NOCACHE, 0, addr_s );
            break;

        case 1:
            tsi148ptr->lcsr.out_trans[1].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[1].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[1].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[1].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[1].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[1].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[1].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[1].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[1].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[1].OTAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED, addr_s );
            break;

        case 2:
            tsi148ptr->lcsr.out_trans[2].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[2].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[2].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[2].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[2].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[2].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[2].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[2].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[2].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[2].OTAT=convert_endian(d32);
            return mmap_device_memory( 2, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 3:
            tsi148ptr->lcsr.out_trans[3].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[3].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[3].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[3].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[3].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[3].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[3].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[3].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[3].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[3].OTAT=convert_endian(d32);
            return mmap_device_memory( 3, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 4:
            tsi148ptr->lcsr.out_trans[4].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[4].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[4].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[4].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[4].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[4].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[4].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[4].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[4].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[4].OTAT=convert_endian(d32);
            return mmap_device_memory( 4, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 5:
            tsi148ptr->lcsr.out_trans[5].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[5].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[5].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[5].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[5].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[5].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[5].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[5].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[5].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[5].OTAT=convert_endian(d32);
            return mmap_device_memory( 5, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 6:
            tsi148ptr->lcsr.out_trans[6].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[6].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[6].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[6].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[6].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[6].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[6].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[6].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[6].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[6].OTAT=convert_endian(d32);
            return mmap_device_memory( 6, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 7:
            tsi148ptr->lcsr.out_trans[7].OTSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.out_trans[7].OTSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.out_trans[7].OTEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.out_trans[7].OTEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.out_trans[7].OTOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.out_trans[7].OTOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.out_trans[7].OTBS=(volatile unsigned int)convert_endian(sst);
            tsi148ptr->lcsr.out_trans[7].OTAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.out_trans[7].OTAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.out_trans[7].OTAT=convert_endian(d32);
            return mmap_device_memory( 7, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;
	}
}
