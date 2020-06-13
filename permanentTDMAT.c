#include <stdio.h>
#include <stdlib.h>

#define ELEM(M, num, row, column) (M[r*C+c])

typedef struct
{
	unsigned int size;
	float *Udiag;
	float *diag;
	float *Ldiag;

}TDMAT;

TDMAT *tdmat_create_with_type(unsigned int size) // vytvorenie miesta pre maticu
{
	TDMAT *tdm = (TDMAT*)malloc(sizeof(TDMAT));
	
	if (tdm == NULL) return NULL;
	
	tdm->Udiag = (float*)malloc(sizeof(float) * (size - 1)); // size - 1, lebo "udiag" a "ldiag" maju o jeden prvok menej ako "diag"
	if (tdm->Udiag == NULL) return NULL;
	
	tdm->diag = (float*)malloc(sizeof(float) * size);
	if (tdm->diag == NULL) return NULL;
	
	tdm->Ldiag = (float*)malloc(sizeof(float) * (size - 1));
	if (tdm->Ldiag == NULL) return NULL;
	
	return tdm;
}

main()
{
	printf("Task failed successufully.\n");
}