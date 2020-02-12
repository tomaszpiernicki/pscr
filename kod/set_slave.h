/*
 * Cezary Pietrzak, 160667
 * Martyna Kulbacka, 160515
 */

#ifndef SET_SLAVE_H_
#define SET_SLAVE_H_

#include "dev_mem.h"

void* set_slave (struct dev_mem_t* tsi148ptr, int nr, unsigned int start_addr_upper, unsigned int start_addr_lower, unsigned int end_addr_upper, unsigned int end_addr_lower,
		unsigned int offset_upper, unsigned int offset_lower, unsigned int attrib);

#endif
