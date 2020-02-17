/*
 * tsi148.c
 *
 *  Created on: 2017-02-06
 *      Author: KSEM
 */
#include <stdio.h>
#include <stdlib.h>
#include <hw/pci.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include "tsi148.h"

uint64_t GetBaseAddress(struct pci_dev_info* info)
{
	uint64_t addr[2]={0};
	uint64_t out_addr;
	pci_read_config32(info->BusNumber,info->DevFunc,0x10,1,(char *)&addr[0]);
	pci_read_config32(info->BusNumber,info->DevFunc,0x14,1,(char *)&addr[1]);

	out_addr=((addr[1] << 31) | (addr[0] & 0xFFFFF000));
	return out_addr;
}

uint8_t GetIrqLine(struct pci_dev_info* info)
{
	uint8_t irqLine;
	pci_read_config8(info->BusNumber,info->DevFunc,0x3C,1,&irqLine);

	return irqLine;
}
