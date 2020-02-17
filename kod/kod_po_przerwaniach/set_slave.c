#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include "set_slave.h"
#include "convert_endian.h"
#include "tsi148.h"

void* set_slave (   int nr, 					    // numer slave'a            (max 8x slave: [0-7])
					unsigned int start_addr_upper, 	// poczatek adresu gorny    (Start Address Upper)
					unsigned int start_addr_lower, 	// poczatek adresu dolny    (Start Address Lower)
					unsigned int end_addr_upper, 	// koniec adresu gorny      (End Address Upper)
					unsigned int end_addr_lower,	// koniec adresu dolny      (End Address Lower)
					unsigned int offset_upper, 		// offset gorny             (Translation Offset Upper)
					unsigned int offset_lower, 		// offset dolny	            (Translation Offset Lower)
					unsigned int attrib,		    // atrybuty translacji      (Translation Attribute)
					struct TSI148* tsi148ptr)       // wskaznik na tsi148
					{

    uint64_t addr_s;
    uint64_t addr_k;
    uint64_t addr;


	switch (nr) {
        case 0:
            tsi148ptr->lcsr.itrans[0].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[0].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[0].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[0].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[0].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[0].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[0].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<31) + (start_addr_lower);
            addr_k = (end_addr_upper<<31) + (end_addr_lower);
            addr = addr_k - addr_s;
            uint32_t d32;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[0].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[0].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 1:
            tsi148ptr->lcsr.itrans[1].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[1].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[1].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[1].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[1].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[1].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[1].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (((uint64_t)(start_addr_upper<<32)) + (start_addr_lower));
            addr_k = (((uint64_t)(end_addr_upper<<32)) + (end_addr_lower));
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[1].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[1].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED, addr_s );
            break;

        case 2:
            tsi148ptr->lcsr.itrans[2].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[2].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[2].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[2].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[2].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[2].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[2].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[2].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[2].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 3:
            tsi148ptr->lcsr.itrans[3].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[3].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[3].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[3].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[3].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[3].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[3].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[3].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[3].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 4:
            tsi148ptr->lcsr.itrans[4].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[4].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[4].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[4].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[4].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[4].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[4].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[4].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[4].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 5:
            tsi148ptr->lcsr.itrans[5].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[5].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[5].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[5].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[5].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[5].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[5].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[5].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[5].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 6:
            tsi148ptr->lcsr.itrans[6].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[6].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[6].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[6].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[6].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[6].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[6].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[6].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[6].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        case 7:
            tsi148ptr->lcsr.itrans[7].itsau=(volatile unsigned int)convert_endian(start_addr_upper);
            tsi148ptr->lcsr.itrans[7].itsal=(volatile unsigned int)convert_endian(start_addr_lower);
            tsi148ptr->lcsr.itrans[7].iteau=(volatile unsigned int)convert_endian(end_addr_upper);
            tsi148ptr->lcsr.itrans[7].iteal=(volatile unsigned int)convert_endian(end_addr_lower);
            tsi148ptr->lcsr.itrans[7].itofu=(volatile unsigned int)convert_endian(offset_upper);
            offset_lower = start_addr_lower * (-1);
            tsi148ptr->lcsr.itrans[7].itofl=(volatile unsigned int)convert_endian(offset_lower);
            tsi148ptr->lcsr.itrans[7].itat=(volatile unsigned int)convert_endian(attrib);

            addr_s = (start_addr_upper<<32) + (start_addr_lower);
            addr_k = (end_addr_upper<<32) + (end_addr_lower);
            addr = addr_k - addr_s;
            d32 = convert_endian(tsi148ptr->lcsr.itrans[7].itat);
            d32 |= 0x80000000;
            tsi148ptr->lcsr.itrans[7].itat=convert_endian(d32);
            return mmap_device_memory( NULL, addr, PROT_READ|PROT_WRITE|PROT_NOCACHE, MAP_SHARED|MAP_PHYS, addr_s );
            break;

        default:
            break;
	}
}
