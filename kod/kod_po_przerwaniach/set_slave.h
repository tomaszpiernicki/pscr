#ifndef SET_SLAVE_H_
#define SET_SLAVE_H_

#include "tsi148.h"

void* set_slave (int nr, unsigned int start_addr_upper, unsigned int start_addr_lower, unsigned int end_addr_upper, unsigned int end_addr_lower,
		unsigned int offset_upper, unsigned int offset_lower, unsigned int attrib, struct TSI148* tsi148ptr);

#endif
