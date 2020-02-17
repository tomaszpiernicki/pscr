//Marek Sudol
//Bartosz Konikowski
//17.02.2020

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>
#include "interrupt.h"
#include "tsi148.h"
#include "cio32.h"
#include "ip235.h"
#include "avme9630.h"
#include <pthread.h>
#include <sched.h>
#include <hw/pci.h>

//wydarzenie, ktore powoluje watek
struct sigevent int_event;

//definicja handlera
const struct sigevent *hdlr( void *blah, int id )
{
	static uint32_t reg1;
	static uint32_t reg2;
	uint32_t IACK_cycle;

	reg2 = deviceRegisters->lcsr.ints;

	reg1 = deviceRegisters->lcsr.vicr;
	reg1 &= 0x700000;
	reg1 >>= 20;
	if (reg2){
		IACK_cycle = deviceRegisters->lcsr.viack[1];
		avme9630_mm_space->AVME9630_regs.IP_ICR = 0x01;
		deviceRegisters->lcsr.intc = 0x02000000;
		//zwrocenie eventu
		return &int_event;
	}
	return NULL;
}

//funkcja inicjalizujaca przerwanie
void interruptInit(){
	setvbuf (stdout, NULL, _IOLBF, 0);
	ThreadCtl(_NTO_TCTL_IO, 0);


	uint8_t tsi148intl = deviceRegisters->pcfs.intl;
	printf("INTL Register: 0x%X \n", tsi148intl);

	deviceRegisters->lcsr.inten = 0x00000000;
	deviceRegisters->lcsr.inteo = 0x00000000;
}

//glowna funkcja, ktora wykonuje powolany przez przerwanie watek
void *tsiInterrupt (void *th){
	//zmienne lokalne
	int id,i;
    setvbuf (stdout, NULL, _IOLBF, 0);
    uint32_t tmp;
    int series=0;

	//powiazanie z systemem I/O
	ThreadCtl(_NTO_TCTL_IO, 0);

	//ustawienie eventu dla handlera
	SIGEV_INTR_INIT(&int_event);

    //inicjalizacja przerwania
	interruptInit();
	tsi148_intl = (int)deviceRegisters->pcfs.intl;
	id = InterruptAttach( tsi148_intl, hdlr, NULL, 0, _NTO_INTR_FLAGS_TRK_MSK );

	tmp=deviceRegisters->lcsr.inteo;
    tmp |= 0x02000000;
	deviceRegisters->lcsr.inten = tmp;
	deviceRegisters->lcsr.inteo = tmp;

	avme9630_mm_space->AVME9630_regs.CBSR = 0x88;	//uruchomienie
	avme9630_mm_space->AVME9630_regs.ILR = 0x01;	//wlaczenie pierwszego przerwania
	avme9630_mm_space->AVME9630_regs.IP_IER = 0x01;
	avme9630_mm_space->AVME9630_regs.IP_ICR = 0x01;

	//sygnal w trybie przerwaniowym
	avme9630_mm_space->IP_A_IO.CONTROL_REGISTER                 = 0x0080;
	avme9630_mm_space->IP_A_IO.START_CONVERT                    = 0x0000;
	avme9630_mm_space->IP_A_IO.CONTROL_REGISTER                 = 0x1104; //0x1105
	avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_ADDRESS_REGISTER = 0x0;

	for(i=0;i<2048;i++){
	   avme9630_mm_space->IP_A_IO.WAVEFORM_MEMORY_DATA_REGISTER=IP235_Data[i];
	}

	avme9630_mm_space->IP_A_IO.TIMER_PRESCALER = 0x3500;
	avme9630_mm_space->IP_A_IO.CONVERSION_TIMER = 0x0100;

	avme9630_mm_space->IP_A_IO.START_CONVERT = 0x0100;

	while (1) {
		// czekanie na wydarzenie
    	InterruptWait(0, NULL );

    	//wyswietlanie okreslonej liczby probek przerwania
    	if(series++ < 500 ){
            printf ("IRQ: %d \n",series);
			//zapalenie bitu startujacego
    		avme9630_mm_space->IP_A_IO.START_CONVERT = 0x0100;
    	}
    	else{
           printf ("Finish %d\n", series-1);
           break;
    	}
    }
}
