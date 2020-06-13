#include <stdio.h>
#include <stdlib.h>

#define ELEM(M, rNum, row, column) (M[row*rNum+culumn])

typedef struct
{
	unsigned int size;
	float *Udiag;
	float *diag;
	float *Ldiag;

}TDMAT;

void done(char msg[])
{
	printf("%s done\n", msg);
}

TDMAT *tdmat_create_with_type(unsigned int size) // vytvorenie miesta pre maticu
{
	TDMAT *tdm = (TDMAT*)malloc(sizeof(TDMAT));
	
	//printf("alokovana adresa: %p\n", tdm);
	
	if (tdm == NULL) return NULL;
	
	tdm->size = size;
	
	tdm->Udiag = (float*)malloc(sizeof(float) * (size - 1)); // size - 1, lebo "udiag" a "ldiag" maju o jeden prvok menej ako "diag"
	if (tdm->Udiag == NULL) return NULL;
	
	tdm->diag = (float*)malloc(sizeof(float) * size);
	if (tdm->diag == NULL) return NULL;
	
	tdm->Ldiag = (float*)malloc(sizeof(float) * (size - 1));
	if (tdm->Ldiag == NULL) return NULL;
	
	return tdm;
}


void tdmat_destroy(TDMAT *tdm) // "vycistenie miesta" po matici
{
 	free(tdm->Udiag);
 	free(tdm->diag);
 	free(tdm->Ldiag);
 	
 	free(tdm);
 	
 	done("destroy");
}

void tdmat_unit(TDMAT *tdm) // identity matrix
{
	float num;
	int i;
	
	for (i = 0; i < tdm->size; i++) // hlavna diagonala
	{
		tdm->diag[i] = 1.0;
	}
	
	for (i = 0; i < (tdm->size - 1); i++) // super/subdiagonala
	{
		tdm->Udiag[i] = 0.0;
		tdm->Ldiag[i] = 0.0;
	}
	
	
	done("unit");
}

void tdmat_random(TDMAT *tdm) // nahodne prvky na diag, Udiag a Ldiag
{
	float num;
	int i;
	
	for (i = 0; i < tdm->size; i++) // hlavna diagonala
	{
		num = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
		tdm->diag[i] = num;
	}
	
	for (i = 0; i < (tdm->size - 1); i++) // super/subdiagonala
	{
		num = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
		tdm->Udiag[i] = num;
		num = -1 + ((float)rand()/(float)(RAND_MAX)) * 2;
		tdm->Ldiag[i] = num;
	}
	
	done("random");
}

main()
{
	srand(time(0));
	TDMAT *tdm;
	unsigned int size;
	unsigned int i;
	float num;
	
	num = 1.0;
	
	printf("Zadaj rozmer (stvorcovej) matice:\n");
	scanf("%d", &size);
	
	tdm = tdmat_create_with_type(size);

	tdmat_unit(tdm);
	
	tdmat_random(tdm);
	
	tdmat_destroy(tdm);
	
	
	printf("\n\nTask failed successufully.\n");
}