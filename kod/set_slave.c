/*
 * Cezary Pietrzak, 160667
 * Martyna Kulbacka, 160515
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include "set_slave.h"
#include "convert_endian.h"
#include "dev_mem.h"

void* set_slave (   struct dev_mem_t* tsi148ptr,    // wskaznik na tsi148
                    int nr, 					    // numer slave'a            (max 8x slave: [0-7])
					unsigned int start_addr_upper, 	// poczatek adresu gorny    (Start Address Upper)
					unsigned int start_addr_lower, 	// poczatek adresu dolny    (Start Address Lower)
					unsigned int end_addr_upper, 	// koniec adresu gorny      (End Address Upper)
					unsigned int end_addr_lower,	// koniec adresu dolny      (End Address Lower)
					unsigned int offset_upper, 		// offset gorny             (Translation Offset Upper)
					unsigned int offset_lower, 		// offset dolny	            (Translation Offset Lower)
					unsigned int attrib,		    // atrybuty translacji      (Translation Attribute)
                    )       
					{

    uint64_t addr_s;
    uint64_t addr_k;
    uint64_t addr;


	switch (nr) {
        case 0:
            tsi148ptr->lcsr.int_trans[0].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[0].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[0].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[0].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[0].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[0].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[0].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            uint32_t d32;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[0].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[0].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 1:
            tsi148ptr->lcsr.int_trans[1].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[1].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[1].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[1].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[1].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[1].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[1].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (((uint64_t)(start_addr_upper<<32)) + (start_addr_lower));
            addr_k = (((uint64_t)(end_addr_upper<<32)) + (end_addr_lower));
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[1].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[1].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED, addr_s );
            break;

        case 2:
            tsi148ptr->lcsr.int_trans[2].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[2].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[2].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[2].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[2].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[2].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[2].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[2].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[2].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 3:
            tsi148ptr->lcsr.int_trans[3].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[3].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[3].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[3].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[3].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[3].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[3].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[3].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[3].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 4:
            tsi148ptr->lcsr.int_trans[4].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[4].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[4].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[4].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[4].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[4].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[4].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[4].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[4].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 5:
            tsi148ptr->lcsr.int_trans[5].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[5].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[5].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[5].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[5].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[5].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[5].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[5].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[5].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 6:
            tsi148ptr->lcsr.int_trans[6].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[6].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[6].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[6].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[6].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[6].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[6].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[6].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[6].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 7:
            tsi148ptr->lcsr.int_trans[7].ITSAU=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.int_trans[7].ITSAL=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.int_trans[7].ITEAU=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.int_trans[7].ITEAL=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.int_trans[7].ITOFU=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.int_trans[7].ITOFL=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.int_trans[7].ITAT=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.int_trans[7].ITAT);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.int_trans[7].ITAT=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        default:
            break;
	}
}
