/*
 * cio32.h
 *
 *  Created on: 2019-12-06
 *      Author: KSEM
 */
#include <stdint.h>
#ifndef CIO32_H_
#define CIO32_H_

//struktura opisujaca IO Space w karcie cio32
typedef struct cio32IOSpace {
	uint8_t un1;
	uint8_t PEDR;
	uint8_t un2;
	uint8_t PBDR;
	uint8_t un3;
	uint8_t PADR;
	uint8_t un4;
	uint8_t PCIO1;
	uint8_t un5;
	uint8_t PFDR;
	uint8_t un6;
	uint8_t PDDR;
	uint8_t un7;
	uint8_t PCDR;
	uint8_t un8;
	uint8_t PCIO;
	uint8_t un9[112];

	} cioIO;

//struktura opisujaca ID Space w karcie cio32
typedef struct cio32IDSpace {
	uint8_t un1;
	uint8_t ASCII_I;
	uint8_t un2;
	uint8_t ASCII_P;
	uint8_t un3;
	uint8_t ASCII_A;
	uint8_t un4;
	uint8_t ASCII_C;
	uint8_t un5;
	uint8_t MANUFACTURER_IDENTIFICATION;
	uint8_t un6;
	uint8_t MODULE_TYPE;
	uint8_t un7;
	uint8_t REVISION_MODULE;
	uint8_t un8;
	uint8_t REVERSED_$00;

	uint8_t un9;
	uint8_t SOFTWARE_DRIVER1;
	uint8_t un10;
	uint8_t SOFTWARE_DRIVER2;
	uint8_t un11;
	uint8_t NR_OF_BYTES;
	uint8_t un12;
	uint8_t CRC;
	uint8_t un13[40];
} cioID;

#endif /* CIO32_H_ */
