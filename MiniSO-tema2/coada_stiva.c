//Savu Ioana Rusalda 
	//315CB

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void *InitQ(void *c, size_t d)
{
    //alocare coada
	c = (TC) malloc(sizeof(TCoada));
    //setare dimensiune elemente coada
	((TCoada *) c)->dime = d;
	((TCoada *) c)->ic = NULL;
	((TCoada *) c)->sc = NULL;
    //setare inceput/sfarsit coada pe NULL(coada vida)
	return (void *)c;
}

int IntrQ(void *c, void *ae, size_t d)
{
	TLG aux;
	aux = AlocCelulaG(ae, d);//alocare celula lista generica
	if (!aux)
		return 0;
    //test coada vida
	if (((TCoada *) c)->sc == NULL && ((TCoada *) c)->ic == NULL) 
    {
        //inserare element in coada vida
		((TCoada *) c)->sc = aux;
		((TCoada *) c)->ic = aux;
	} 
    else 
    {
        //inserare element in coada
		((TCoada *) c)->sc->urm = aux;
		((TCoada *) c)->sc = aux;//actualizare sfarsit
	}
	return 1;
}

int ExtrQ(void *c, void *ae)
{
	TLG aux;
    //test coada vida
	if (((TCoada *) c)->ic == NULL)
		return 0;
	aux = ((TCoada *) c)->ic;
	if (!aux)
		return 0;
    //atualizare inceput coada
	((TCoada *) c)->ic = aux->urm;
	memcpy(ae, aux->info, ((TCoada *) c)->dime);
	free(aux->info);
	free(aux);
    //eliberare informatie coada
	if (!((TCoada *) c)->ic)
		((TCoada *) c)->sc = NULL;
    //actualizare sfarsit in cazul in care coada devine vida
	return 1;
}

void DistrQ(void *c)
{
	void *el;
	el = malloc(sizeof(PROC));
    //test coada vida
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
    {
		ExtrQ(c, el);
		free(el);
        //eliberare element coada
	}
	free(((TCoada *) c)->ic);
	free(((TCoada *) c)->sc);
	free(c);
	free(el);
}

int sizeQ(void *c)
{
	void *caux;
	int nr = 0;
	void *el;
	el = malloc(sizeof(PROC));
	caux = (TC) malloc(sizeof(TCoada));
	caux = InitQ(caux, sizeof(PROC));
    //initializare coada auxiliara
    //test coada vida
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
    {
		ExtrQ(c, el);
		nr++;//nr numara elementele din coada
		IntrQ(caux, el, sizeof(PROC));
        //extragere element din coada si introducerea lui in coada auxiliara
	}
    //test coada vida
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
    {
		ExtrQ(caux, el);
		IntrQ(c, el, sizeof(PROC));
        //extragere element din coada auxiliara si introducere in coada initiala
	}
	DistrQ(caux);
	free(el);
    //se returneaza numarul de elemente din coada
	return nr;
}

void SortQ(void *c)
{

	int i, j;
	void *a, *b;
	size_t d = sizeof(PROC);
	a = malloc(sizeof(PROC));
	b = malloc(sizeof(PROC));
	int size = sizeQ(c);
    //size retine dimensiunea cozii
	for (i = 0; i <= size - 1; i++) 
    {
		ExtrQ(c, a);//extragere element coada
		for (j = 1; j <= size - 1; j++) 
        {
			ExtrQ(c, b);
            //sortare dupa prioritate
			if (((PROC *) b)->prioritate < ((PROC *) a)->prioritate)
            {
				IntrQ(c, a, d);
				memcpy(a, b, d);
			} 
            else
			    if (((PROC *) b)->prioritate ==
				((PROC *) a)->prioritate) 
                {
                    //sortare dupa timp de executie
				    if (((PROC *) b)->timp_exec >
				        ((PROC *) a)->timp_exec) 
                    {
					   {
						  IntrQ(c, a, d);
						  memcpy(a, b, d);
					   }
				    } 
                    else
				        if (((PROC *) b)->PID > ((PROC *) a)->PID) 
                        {
                            //sortare dupa PID
					       IntrQ(c, a, d);
					       memcpy(a, b, d);
				        } 
                        else
					       IntrQ(c, b, d);
                } 
                else
				    IntrQ(c, b, d);
		}
		IntrQ(c, a, d);
	}
	free(a);
	free(b);
}

void *InitS(void *s, size_t d)
{
    //initializare stiva
	s = (TS) malloc(sizeof(TStiva));
    //setare dimensiune elemente stiva
	((TStiva *) s)->dime = d;
    //initializare varf si baza stiva
	((TStiva *) s)->vf = NULL;
	((TStiva *) s)->b = NULL;
	return (void *)s;
}

int Push(void *s, void *ae, size_t d)
{

	TLG aux;
    //alocare celula lista generica
	aux = AlocCelulaG(ae, d);
	if (!aux)
		return 0;
    //test stiva vida
	if (((TStiva *) s)->vf == NULL) 
    {
		((TStiva *) s)->vf = aux;
		((TStiva *) s)->b = aux;
	} 
    else 
    {
		aux->urm = ((TStiva *) s)->vf;
		((TStiva *) s)->vf = aux;
        //actualizare varf stiva
	}
	return 1;
}

int Pop(void *s, void *ae)
{
	TLG aux;
    //test stiva vida
	if (((TStiva *) s)->vf == NULL) 
    {
		return 0;
	}
	aux = ((TStiva *) s)->vf;
    //test un singur element stiva
	if (((TStiva *) s)->vf == ((TStiva *) s)->b) 
    {
		((TStiva *) s)->vf = NULL;
	}
	memcpy(ae, aux->info, ((TStiva *) s)->dime);
	((TStiva *) s)->vf = aux->urm;
	free(aux->info);
	free(aux);
    //eliberare element stiva
	return 1;
}
