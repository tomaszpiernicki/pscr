/*
 * avme9630.h
 *
 *  Created on: 2020-01-17
 *      Author: KSEM
 */

#include <stdint.h>
#ifndef AVME9630_H_
#define AVME9630_H_

#include "cio32.h"
//struktura opisujaca ID Space w karcie amve9360
typedef struct avme9630MMSpace {  //avme9660 memory map
	uint8_t un1;
	uint8_t CBSR;
	uint8_t un2;
	uint8_t ILR;
	uint8_t un3;
	uint8_t IP_ER;
	uint8_t un4;
	uint8_t IP_EMR;
	uint8_t un_a[8];
	uint8_t un5;
	uint8_t IP_A_MBA_SR;
	uint8_t un6;
	uint8_t IP_B_MBA_SR;
	uint8_t un7;
	uint8_t IP_C_MBA_SR;
	uint8_t un8;
	uint8_t IP_D_MBA_SR;
	uint8_t un_b[8];
	uint8_t un9;
	uint8_t IP_IER;
	uint8_t un10;
	uint8_t IP_IPR;
	uint8_t un11;
	uint8_t IP_ICR;
	uint8_t un18[26];

	//rozmiar ID_SPECIFIC_SPACE oraz Not Used po tym trzeba ustalic

}avme9630ID;

typedef struct avmeIO_memorymap{
	struct ip235IOSpace IP_A_IO;
	struct ip235IDSpace IP_A_ID;
	struct avme9630MMSpace AVME9630_regs;
	struct cio32IOSpace IP_B_IO;
	struct cio32IDSpace IP_B_ID;

}avme9630map ;
extern struct avmeIO_memorymap *avme9630_mm_space;
#endif /* AVME9630_H_ */
