/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct celula
{ int info;
  struct celula * urm;
} TCelula, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(int);          /* adresa celulei create sau NULL */
void   DistrugeL (ALista);       /* elimina toate celulele din lista */

void AfisareL (TLista L);
TLista Copie(TLista L,int a ,int b);
TLista Mutare(ALista aL);
int prim(int x);
int Inserarefinal(ALista aL, int x);
TLista ex3(TLista a,TLista b);
TLista bonus(TLista a,TLista b);
#endif
