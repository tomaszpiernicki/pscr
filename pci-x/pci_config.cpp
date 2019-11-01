#include <stdio.h>
#include <stdint.h>
#include <pci/pci.h>	//wygl¹da na to, ¿e bilbioteka pci jest bilbiotek¹ linuxow¹.

struct pci_config {
	uint32_t devi_veni;
	uint32_t stat_cmmd;
	uint32_t clas_revi;
	uint32_t rsvd_head_mlat_clsz;  
	uint32_t mbarl;
	uint32_t mbaru;
	uint32_t rsvd_array_1[5];
	uint32_t subi_subv;
	uint32_t rsvd_capp;
	uint32_t rsvd_blank;     //  0x38 - 0x038
	uint32_t mxla_mngn_uint32_tp_uint32_tl;
	uint32_t pcixcap;
	uint32_t pcixstat;
	uint32_t rsvd_array_2[47];
};

int structure_size = 256;

int main()
{

	if (sizeof(struct pci_config) != structure_size) {
		printf("ERROR: Structure's size is wrong.");
		return -1;
	}

	return 0;
}