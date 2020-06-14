#include <stdio.h>
#include <stdlib.h>

#define ELEM(M, rNum, row, column) (M[row*rNum+culumn])

typedef struct // riedka reprezentacia matice
{
	unsigned int size;
	float *Udiag;
	float *diag;
	float *Ldiag;
}TDMAT;

typedef struct // husta reprezentacia matice
{
	unsigned int size;
	float *elem;
} MAT;

void done(char msg[])
{
	printf("%s done\n", msg);
}

TDMAT *tdmat_create_with_type(unsigned int size) // vytvorenie miesta pre tridiagonalnu maticu
{
	TDMAT *tdm = (TDMAT*)malloc(sizeof(TDMAT));
	if (tdm == NULL) return NULL;
	//printf("alokovana adresa: %p\n", tdm);
	
	tdm->size = size;
	
	tdm->Udiag = (float*)malloc(sizeof(float) * (size - 1)); // size - 1, lebo "Udiag" a "Ldiag" maju o jeden prvok menej ako "diag"
	if (tdm->Udiag == NULL) return NULL;
	
	tdm->diag = (float*)malloc(sizeof(float) * size);
	if (tdm->diag == NULL) return NULL;
	
	tdm->Ldiag = (float*)malloc(sizeof(float) * (size - 1));
	if (tdm->Ldiag == NULL) return NULL;
	
	return tdm;
}

MAT *mat_create(unsigned int size) // obycajna reprezentacia matice
{
	MAT *mat = (MAT*)malloc(sizeof(MAT));
	if (mat == NULL) return NULL;
	
	mat->size = size;
	
	mat->elem = (float*)malloc(sizeof(float)*size*size);
	if (mat->elem == NULL) return NULL;
	
	return mat;
}

void tdmat_destroy(TDMAT *tdm) // "vycistenie miesta" po tridiagonalnej matici
{
 	free(tdm->Udiag);
 	free(tdm->diag);
 	free(tdm->Ldiag);
     
     free(tdm);
     	
 	//done("destroy");
}

void mat_destroy(MAT *mat) // "vycistenie miesta" po obycajnej matici
{
	free(mat->elem);
	
	free(mat);		
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
	
	
	//done("unit");
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
	
	//done("random");
}

void tdmat_print(TDMAT *tdm)
{
	int i, j, d = 0, Ud = 0, Ld = 0; // d, Ud a Ld 
	
	for (i = 0; i < tdm->size; i++)
	{
		for (j = 0; j < tdm->size; j++)
		{
			if (i == j) 
			{
				if (tdm->diag[d] == 1.0)
				{
					printf("%10d", 1);
					d++;
				} else
				{
				printf("%10.4f", tdm->diag[d]);
				d++;
				}
			} else if ((j - 1) == i)
				{
					if (tdm->Udiag[Ud] == 0.0)
					{
						printf("%10d", 0);
						Ud++;
					} else
						{
							printf("%10.4f", tdm->Udiag[Ud]);
							Ud++;
						}
				} else if ((j + 1) == i)
					{
						if (tdm->Ldiag[Ld] == 0.0)
						{
							printf("%10d", 0);
							Ld++;
						} else
							{
								printf("%10.4f", tdm->Ldiag[Ld]);
								Ld++;
							}
					} else
						{
							printf("%10d", 0);
						}
		}
		printf("\n");
	}
	printf("\n");
	//done("print");
}

float mat_permanent(MAT *mat) // vypocet permanentu "obycajnej" matice
{
	int i,j;
		
}

float tdmat_permanent(TDMAT *tdm) // vypocet permanentu tridiagonalnej matice
{
	if (tdm->size == 1) return tdm->diag[0];
	else if (tdm->size == 2) return (tdm->diag[0] * tdm->diag[1] - (tdm->Ldiag[0] * tdm->Udiag[0]));
	else
	{
		int i,j, col;
		float permanent = 0.0;
	
		for (col = 0; col < tdm->size; col++)
		{
			MAT *mat;
			mat = mat_create(tdm->size - 1);
			
			for (i = 0; i < (tdm->size - 1); i++)
			{
				for (j = 0; j < (tdm->size - 1); j++)
				{
					if (i == col)
					{
						
					}
				}
			}
		}	
	}
	
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
	
	tdm = tdmat_create_with_type(size); // vytvorenie

	tdmat_unit(tdm); // zadanie hodnot na identity matrix
	tdmat_print(tdm); // vypis matice
	
	tdmat_random(tdm); // zdanie hodnot na nahodne float cisla
	tdmat_print(tdm); // vypis matice
	
	printf("permnent: %.4f\n", tdmat_permanent(tdm)); // vypis permanentu
	
	tdmat_destroy(tdm); // "znicenie matice"
	
	
	printf("\n\nTask failed successufully.\n");
}