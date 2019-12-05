#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

//#include <pci/pci.h>

struct outbound_translation {
	uint32_t OTSAU;
	uint32_t OTSAL;
	uint32_t OTEAU;
	uint32_t OTEAL;
	uint32_t OTOFU;
	uint32_t OTOFL;
	uint32_t OTBS;
	uint32_t OTAT;
};

struct inbound_translation {
	uint32_t ITSAU;
	uint32_t ITSAL;
	uint32_t ITEAU;
	uint32_t ITEAL;
	uint32_t ITOFU;
	uint32_t ITOFL;
	uint32_t ITAT;
	uint32_t rsvd;
};

struct dma_controller {
	uint32_t DCTL;
	uint32_t DSTA;
	uint32_t DCSAU;
	uint32_t DCSAL;
	uint32_t DCDAU;
	uint32_t DCDAL;
	uint32_t DCLAU;
	uint32_t DCLAL;
	uint32_t DSAU;
	uint32_t DSAL;
	uint32_t DDAU;
	uint32_t DDAL;
	uint32_t DSAT;
	uint32_t DDAT;
	uint32_t DNLAU;
	uint32_t DNLAL;
	uint32_t DCNT;
	uint32_t DDBS;
};


struct crcsr_t {
	uint32_t rsvd[253];
	uint32_t csrbcr;
	uint32_t csrbsr;
	uint32_t cbar;
};

struct gcsr_t {
	uint32_t gscr_devi_veni;
	uint32_t gscr_gctrl_ga_revid;
	uint32_t gscr_semaphore04;
	uint32_t gscr_semaphore47;
	uint32_t gscr_mbox0;
	uint32_t gscr_mbox1;
	uint32_t gscr_mbox2;
	uint32_t gscr_mbox3;
} gcsr;

struct lcsr_t {
	struct outbound_translation out_trans[8];
	uint32_t rsvd;
	uint32_t VIACK[7];
	
	uint32_t RMWAU;
	uint32_t RMWAL;
	uint32_t RMWEN;
	uint32_t RMWC;
	uint32_t RMWS;
	
	uint32_t VMCTRL;
	uint32_t VCTRL;
	uint32_t VSTAT;
	
	uint32_t PCSR;
	
	uint32_t rsvd_1[3];

	uint32_t VMEFL;
	
	uint32_t lscr_rsvd_2[3];
	
	uint32_t VEAU;
	uint32_t VEAL;
	uint32_t VEAT;
	
	uint32_t lscr_rsvd_3;
	
	uint32_t EDPAU;
	uint32_t EDPAL;
	uint32_t EDPXA;
	uint32_t EDPXS;
	uint32_t EDPAT;
	
	uint32_t lscr_rsvd_4[31]; //0x31C

	struct inbound_translation int_trans[8];

	uint32_t GBAU;
	uint32_t GBAL;
	uint32_t GCSRAT;
	
	uint32_t CBAU;
	uint32_t CBAL;
	uint32_t CRGAT;
	
	uint32_t CROU;
	uint32_t CROL;
	uint32_t CRAT;

	uint32_t LMBAU;
	uint32_t LMBAL;
	uint32_t LMAT;
	
	uint32_t BCU;
	uint32_t BCL;
	uint32_t BPGTR;
	uint32_t BPCTR;
	uint32_t VICR;
	uint32_t rsvd_5;
	
	uint32_t INTEN;
	uint32_t INTEO;
	uint32_t INTS;
	uint32_t INTC;
	uint32_t INTM1;
	uint32_t INTM2;
	uint32_t rsvd_6[40];

	struct dma_controller dma_contr_0;
	uint32_t rsvd_7[14];
	struct dma_controller dma_contr_1;
	uint32_t rsvd_8[14];
};


struct pcfs_t {
	uint32_t devi_veni;		//0x00/
	uint32_t stat_cmmd;
	uint32_t clas_revi;
	uint32_t rsvd_head_mlat_clsz;
	uint32_t mbarl;
	uint32_t mbaru;
	uint32_t rsvd_array_1[5];
	uint32_t subi_subv;
	uint32_t rsvd_0x30;
	uint32_t rsvd_capp;
	uint32_t rsvd_blank;     //  0x38
	uint32_t mxla_mngn_intp_intl;
	uint32_t pcixcap;
	uint32_t pcixstat;
	uint32_t rsvd_array_2[46];
};

struct dev_mem {
	struct pcfs_t pcfs;
	struct lcsr_t lcsr;
	struct gcsr_t gcsr;
	uint32_t rsvd[376];
	struct crcsr_t rcsrc;
} info;


int main(int argc, char *argv[])
{
	//struct pci_dev_info info;
	int pidx = 0;
	void* hdl;
	int phdl;
//	printf("%d\n", sizeof (struct crcsr_t));

	
	printf("PCFS offset: %d\n", offsetof(struct dev_mem, pcfs) );
	printf("PCFS size: %d\n\n", sizeof( struct pcfs_t) );
		
	printf("lcsr offset: %d\n", offsetof(struct dev_mem, lcsr) );		
	printf("lcsr size: %d\n\n", sizeof( struct lcsr_t) );
	
	printf("gcsr offset: %d\n", offsetof(struct dev_mem, gcsr) );		
	printf("gcsr size: %d\n\n", sizeof( struct gcsr_t) );
	
	printf("rsvd offset: %d\n\n", offsetof(struct dev_mem, rsvd) );		
	
	printf("rcsrc offset: %d\n", offsetof(struct dev_mem, rcsrc) );	
	printf("rcsrc size: %d\n\n", sizeof( struct crcsr_t) );
	
	printf("full size: %d\n\n", sizeof( struct dev_mem) );
	//phdl = pci_attach(NULL);
	//hdl = pci_attach_device(NULL, (PCI_SEARCH_VENDEV | PCI INIT_ALL), pidx, &info);
	/*if (sizeof(struct pci_config) != structure_size) {
		printf("ERROR: Structure's size is wrong.");
		return -1;
	}*/

	return 0;
}


