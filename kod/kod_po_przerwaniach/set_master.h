#ifndef SET_MASTER_H_
#define SET_MASTER_H_

#include "tsi148.h"

void Tsi148BusMastering(struct TSI148* dev);

void* set_master (struct TSI148* tsi148ptr, int nr, unsigned int start_addr_upper, unsigned int start_addr_lower, unsigned int end_addr_upper, unsigned int end_addr_lower,
		unsigned int offset_upper, unsigned int offset_lower, unsigned int sst, unsigned int attrib);

#endif
