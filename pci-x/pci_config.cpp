#include <stdio.h>
#include <stdint.h>

struct pci_config {
	uint32_t devi_veni;
	uint32_t stat_cmmd;
	uint32_t clas_revi;
	uint32_t rsvd_head_mlat_clsz;  // rsvd = reserved
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


int main()
{
	printf("%i" , sizeof(struct pci_config));
}