/*
 * tsi148.h
 *
 *
 */
#ifndef TSI148_H_
#define TSI148_H_

#include <hw/pci.h>

#define VENDOR_ID 0x10E3
#define DEVICE_ID 0x0148

#pragma pack(1)

/*
 *  Struktura rejestrów
 *
 *  Combined Register Group (CRG) zawiera
 *
 *  offset 0x000 PCFS    - PCI Configuration Space Registers
 *  offset 0x100 LCSR    - Local Control and Status Registers
 *  offset 0x600 GCSR    - Global Control and Status Registers
 *  offset 0xff4 CR/CSR  - Subset of Configuration ROM / Control and Status Registers
 */

/*
 * DMAC descriptor registers
 */
struct dma_desc{
	uint32_t dsau;
	uint32_t dsal;
	uint32_t ddau;
	uint32_t ddal;
	uint32_t dsat;
	uint32_t ddat;
	uint32_t dnlau;
	uint32_t dnlal;
	uint32_t dcnt;
	uint32_t ddbs;
};

/*
 * DMAC registers
 */
struct dma{
	uint32_t dctl;
	uint32_t dsta;
	uint32_t dcsau;
	uint32_t dcsal;
	uint32_t dcdau;
	uint32_t dcdal;
	uint32_t dclau;
	uint32_t dclal;
	struct dma_desc dma_desc;
	uint32_t reserved[14];
};

/*
 * PCFS registers
 */
struct pcfs{
	uint16_t veni;
	uint16_t devi;
	uint16_t cmmd;
	uint16_t stat;
	uint32_t rev_class;
	uint8_t clsz;
	uint8_t mlat;
	uint8_t head;
	uint8_t reserved0;
	uint32_t mbarl;
	uint32_t mbaru;
	uint32_t reserved1[5];
	uint16_t subv;
	uint16_t subi;
	uint32_t reserved2;
	uint8_t capp;
	uint8_t reserved3[7];
	uint8_t intl;
	uint8_t intp;
	uint8_t mngn;
	uint8_t mxla;
	uint8_t pcix_cap_id;
	uint8_t pcix_next_cap_ptr;
	uint16_t pcix_command;
	uint32_t pcix_status;
	uint32_t reserved4[46];
};

/*
 * Struktury u¿ywane w LCSR
 */

/*
 * OutBound translation registers
 */
struct otrans{
	uint32_t otsau;
	uint32_t otsal;
	uint32_t oteau;
	uint32_t oteal;
	uint32_t otofu;
	uint32_t otofl;
	uint32_t otbs;
	uint32_t otat;
};

/*
 * InBound translation registers
 */
struct itrans{
	uint32_t itsau;
	uint32_t itsal;
	uint32_t iteau;
	uint32_t iteal;
	uint32_t itofu;
	uint32_t itofl;
	uint32_t itat;
	uint32_t reserved;
};

struct lcsr{
	struct otrans otrans[8];						//offset 0x100
	uint32_t viack[8];								//offset 0x200
	uint32_t rmwau;
	uint32_t rmwal;
	uint32_t rmwen;
	uint32_t rmwc;
	uint32_t rmws;
	uint32_t vmctrl;
	uint32_t vctrl;
	uint32_t vstat;
	uint32_t pstat;
	uint8_t pstatrsvd[12];
	uint32_t vmefl;
	uint8_t vmeflrsvd[12];
	uint32_t veau;
	uint32_t veal;
	uint32_t veat;
	uint8_t vearsvd[4];
	uint32_t edpau;
	uint32_t edpal;
	uint32_t edpxa;
	uint32_t edpsx;
	uint32_t edpat;
	uint8_t edparsvd[124];
	struct itrans itrans[8];						//offset 0x300
	uint32_t gbau;
	uint32_t gbal;
	uint32_t gcsrat;
	uint32_t cbau;
	uint32_t cbal;
	uint32_t crgat;
	uint32_t crou;
	uint32_t crol;
	uint32_t crat;
	uint32_t lmbau;
	uint32_t lmbal;
	uint32_t lmat;
	uint32_t bcu;
	uint32_t bcl;
	uint32_t bpgtr;
	uint32_t bpctr;
	uint32_t vicr;
	uint8_t vicrsvd[4];
	uint32_t inten;
	uint32_t inteo;
	uint32_t ints;
	uint32_t intc;
	uint32_t intm1;
	uint32_t intm2;
	uint32_t reserved[40];
	struct dma dma[2];								//offset 0x500
};

struct gcsr{
	uint16_t devi;									//offset 0x600
	uint16_t veni;
	uint16_t ctrl;
	uint8_t ga;
	uint8_t revid;
	uint8_t semaphore[8];
	uint32_t mbox[4];
};

struct crcsr{
	uint32_t csrbcr;
	uint32_t csrbsr;
	uint32_t cbar;
};

typedef struct TSI148{
	struct pcfs pcfs;
	struct lcsr lcsr;
	struct gcsr gcsr;
	uint32_t reserved[629];
	struct crcsr crcsr;
}tsi148_reg;

//Functions

uint64_t GetBaseAddress(struct pci_dev_info* info);

uint8_t GetIrqLine(struct pci_dev_info* info);

extern volatile struct TSI148* deviceRegisters;
extern volatile int tsi148_intl;
extern int16_t IP235_Data[4096];
#endif /* TSI148_H_ */
