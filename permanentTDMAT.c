#include <stdio.h>
#include <stdlib.h>

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

TDMAT *tdmat_create_with_type(unsigned int size) // vytvorenie miesta pre tridiagonalnu maticu
{
	TDMAT *tdm = (TDMAT*)malloc(sizeof(TDMAT));
	if (tdm == NULL) return NULL;
	
	tdm->size = size;
	
	tdm->Udiag = (float*)malloc(sizeof(float) * (size - 1));
	if (tdm->Udiag == NULL)
	{
		 free(tdm);
		 
		 return NULL;
	}
	
	tdm->diag = (float*)malloc(sizeof(float) * size);
	if (tdm->diag == NULL)
	{
		free(tdm->Udiag);
		free(tdm);
		
		return NULL;
	}
	
	tdm->Ldiag = (float*)malloc(sizeof(float) * (size - 1));
	if (tdm->Ldiag == NULL)
	{
		free(tdm->Udiag);
		free(tdm->diag);
		free(tdm);
		
		return NULL;
	}
	
	return tdm;
}

MAT *mat_create(unsigned int size) // obycajna reprezentacia matice
{
	MAT *mat = (MAT*)malloc(sizeof(MAT));
	if (mat == NULL) return NULL;
	
	mat->size = size;
	
	mat->elem = (float*)malloc(sizeof(float)*size*size);
	if (mat->elem == NULL)
	{
		free(mat);
		
		return NULL;
	}
	
	return mat;
}

void tdmat_destroy(TDMAT *tdm) // "vycistenie miesta" po tridiagonalnej matici
{
 	free(tdm->Udiag);
 	free(tdm->diag);
 	free(tdm->Ldiag);
     
     free(tdm);
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
}

void tdmat_random(TDMAT *tdm) // nahodne prvky na diag, Udiag a Ldiag
{
	float num;
	int i;
	
	for (i = 0; i < tdm->size; i++) // hlavna diagonala
	{
		num = -1.0 + ((float)rand()/(float)(RAND_MAX)) * 2.0;
		tdm->diag[i] = num;
	}
	
	for (i = 0; i < (tdm->size - 1); i++) // super/subdiagonala
	{
		num = -1.0 + ((float)rand()/(float)(RAND_MAX)) * 2.0;
		tdm->Udiag[i] = num;
		
		num = -1.0 + ((float)rand()/(float)(RAND_MAX)) * 2.0;
		tdm->Ldiag[i] = num;
	}
}

void tdmat_print(TDMAT *tdm)
{
	int i, j, d = 0, Ud = 0, Ld = 0; // d, Ud a Ld na indexi prvkov pre diag, Udiag a Ldiag
	
	for (i = 0; i < tdm->size; i++)
	{
		for (j = 0; j < tdm->size; j++)
		{
			if (i == j) 
			{
				printf("%10.4f", tdm->diag[d]);
				d++;
			} else if ((j - 1) == i)
				{
					printf("%10.4f", tdm->Udiag[Ud]);
					Ud++;
				} else if ((j + 1) == i)
					{
						printf("%10.4f", tdm->Ldiag[Ld]);
						Ld++;
					} else
						{
							printf("%10.4f", 0.0);
						}
		}
		printf("\n");
	}
	printf("\n");
}

void mat_print(MAT *mat)
{
	int i, j;
	
	for (i = 0; i < mat->size; i++)
	{
		for (j = 0; j < mat->size; j++)
		{
			printf("%10.4f", mat->elem[i * mat->size + j]);
		}
		printf("\n");
	}
}

float mat_permanent(MAT *mat) // vypocet permanentu "obycajnej" matice
{	
	float permanent = 0.0;
	
	if (mat->size == 1) return mat->elem[0];
	else if (mat->size == 2) return (mat->elem[0] * mat->elem[3] + mat->elem[2] * mat->elem[1]);
	else
	{
		int i, j, col = 0, minorMatIndex = 0;
		
		for (col = 0; col < mat->size; col++)
		{
			if (mat->elem[col] != 0) // ak prvok matice [0, col] == 0, tak netreba nic pocitat
			{
			MAT *minorMat;
			minorMat = mat_create(mat->size - 1); // # este doplnit varovnu spravu, ak minorMat == NULL
			
			minorMatIndex = 0;
			
			for (i = 1; i < mat->size; i++)
			{
				for (j = 0; j < mat->size; j++)
				{
					if (j != col)
					{
						minorMat->elem[minorMatIndex] = mat->elem[i * mat->size + j];
						minorMatIndex++;
					}
				}
			}
			
			permanent += mat->elem[col] * mat_permanent(minorMat);
			
			mat_destroy(minorMat);
			}
		}
	}
	
	return permanent;	
}

float tdmat_permanent(TDMAT *tdm) // vypocet permanentu tridiagonalnej matice
{
	float permanent = 0.0;
	
	if (tdm->size == 1) return tdm->diag[0];
	else if (tdm->size == 2) return (tdm->diag[0] * tdm->diag[1] + tdm->Ldiag[0] * tdm->Udiag[0]);
	else
	{
		int i, j, col, indexMat = 0, d = 1, Ud = 1, Ld = 0, helpd, helpUd, helpLd;
			
		for (col = 0; col < 2; col++) // cyklus pre rozvoj
		{
			MAT *mat; 
			mat = mat_create(tdm->size - 1); // #aj tu este doplnil varovnu spravu pre pripad NULL
			
			for (i = 1; i < tdm->size; i++)
			{
				helpd = 0, helpUd = 0, helpLd = 0;
				
				for (j = 0; j < tdm->size; j++)
				{
					if (j != col)
					{
						if (i == j) // prvok hlavnej diagonaly
						{
							mat->elem[indexMat] = tdm->diag[d];
							indexMat++;
							d++;
							helpd++; // d bolo zmenene
							
							if (helpLd == 0) Ld++;
							
						} else if ((j - 1) == i) // prvok superdiagonaly
							{
								mat->elem[indexMat] = tdm->Udiag[Ud];
								indexMat++;
								Ud++;
								helpUd++;
								
								if (helpd == 0) d++;
								
							} else if ((j + 1) == i) // prvok subdiagonaly
								{
									mat->elem[indexMat] = tdm->Ldiag[Ld];
									indexMat++;
									Ld++;
									helpLd++;
								} else // inak nula
									{
										mat->elem[indexMat] = 0.0;
										indexMat++;
										
										if ((tdm->size % 2) == 0) // kontrola pre spravne posuvanie Ud indexu
										{
											if ((helpUd == 0) && (j > (tdm->size / 2))) Ud++;
										} else 
											{
												if ((helpUd == 0) && (j > ((tdm->size / 2) + 1))) Ud++;
											}
									}
					
					if (Ld == (tdm->size - 1)) Ld = 0;
					
					if (d == tdm->size) d = 1;
					
					if (Ud == (tdm->size - 1)) Ud = 1;
									
					}
				}
			}
			
			if (col == 0) permanent += tdm->diag[0] * mat_permanent(mat);
			else if (col == 1) permanent += tdm->Udiag[0] * mat_permanent(mat);
			
			mat_destroy(mat); 
			
			indexMat = 0, d = 1, Ud = 1, Ld = 0;		
		}	
	}
	
	return permanent;
}

main()
{
	srand(time(0));
	TDMAT *tdm;
	unsigned int size;
	
	printf("Zadaj rozmer (stvorcovej) matice:\n");
	scanf("%d", &size);
	
	tdm = tdmat_create_with_type(size); // vytvorenie

	//tdmat_unit(tdm); // zadanie hodnot na identity matrix
	//tdmat_print(tdm); // vypis matice
	
	tdmat_random(tdm); // zdanie hodnot na nahodne float cisla
	tdmat_print(tdm); // vypis matice
	
	printf("Permanent matice = %.5f\n", tdmat_permanent(tdm)); // vypis permanentu
	
	tdmat_destroy(tdm); // "znicenie matice"
	
	printf("\n\nTask failed successufully.\n");
}