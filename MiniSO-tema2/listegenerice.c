//Savu Ioana Rusalda 
	//315CB

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

TLG AlocCelulaG(void *ae, size_t d)
{
	TLG aux;
	aux = (TLG) malloc(sizeof(TCelulaG));
	if (!aux)
		return NULL;
	aux->info = malloc(d);
	if (!aux->info) 
  {
		free(aux);
		return NULL;
	}
	memcpy(aux->info, ae, d);
	aux->urm = NULL;
	return aux;
}

int InsLG(ALG aL, void *ae, size_t d)
{
	TLG aux = AlocCelulaG(ae, d);
	if (!aux)
		return 0;
	aux->urm = *aL;
	*aL = aux;
	return 1;
}
