/*
 * Cezary Pietrzak, 160667
 * Martyna Kulbacka, 160515
 */

#ifndef SET_MASTER_H_
#define SET_MASTER_H_

#include "dev_mem.h"

void bus_mastering(struct dev_mem_t* tsi148ptr);

void* set_master (struct dev_mem_t* tsi148ptr, int nr, unsigned int start_addr_upper, unsigned int start_addr_lower, unsigned int end_addr_upper, unsigned int end_addr_lower,
		unsigned int offset_upper, unsigned int offset_lower, unsigned int sst, unsigned int attrib);

#endif
