/*
 * ip235.h
 *
 *  Created on: 2019-12-06
 *      Author: KSEM
 */
#include <stdint.h>
#ifndef IP235_H_
#define IP235_H_

//struktura opisujaca IO Space w karcie ip235
typedef struct ip235IOSpace {
	uint16_t CONTROL_REGISTER;
	uint16_t TIMER_PRESCALER; //starsza polowa rejestru
	uint16_t CONVERSION_TIMER;
	uint16_t WAVEFORM_MEMORY_DATA_REGISTER;
	uint16_t WAVEFORM_MEMORY_ADDRESS_REGISTER;
	uint16_t CALIBRATION_COEFFICIENT_WRITE;//3 bity odczyt/zapis, 5 bitów CALIBRATION_COEFFICIENT_ADDRESS, 8 bitow CALIBRATION_COEFFICIENT_DATA
	uint16_t CALIBRATION_COEFFICIENT_READ; //8 BITOW ODCZYT, 2 BITY PUSTE, 3 BITY WR BUSY, 3 BITY RD COMP
	uint16_t START_CONVERT; //??
	uint16_t DAC_CH0;
	uint16_t DAC_CH1;
	uint16_t DAC_CH2;
	uint16_t DAC_CH3;
	uint16_t DAC_CH4;
	uint16_t DAC_CH5;
	uint16_t DAC_CH6;
	uint16_t DAC_CH7;
	uint16_t INTERRUPT_VECTOR; //8 BITOW PUSTYCH, 8 BITÓW INTERRUPT VECTOR
	uint16_t RESERVED; //8 BITOW RESERVED, 8 NU
	uint16_t un1[46];//??
} ip235IO;

//struktura opisujaca ID Space w karcie ip235
typedef struct ip235IDSpace {
	uint8_t un1;
	uint8_t ASCII_I;
	uint8_t un2;
	uint8_t ASCII_P;
	uint8_t un3;
	uint8_t ASCII_A;
	uint8_t un4;
	uint8_t ASCII_C;
	uint8_t un5;
	uint8_t ACROMAG_ID_CODE;
	uint8_t un6;
	uint8_t IP_MODEL_CODE;
	uint8_t un7;
	uint8_t un8; //Not Used (Revision)
	uint8_t un9;
	uint8_t un10; //Reserved
	uint8_t un11;
	uint8_t un12; //Not Used (Driver ID Low Byte)
	uint8_t un13;
	uint8_t un14; //Not Used (Driver ID High Byte)
	uint8_t un15;
	uint8_t TOTAL_NUMBER_OF_ID_PROM_BYTES;
	uint8_t un16;
	uint8_t CRC;
	uint8_t un17[40];
} ip235ID;

#endif /* IP235_H_ */
