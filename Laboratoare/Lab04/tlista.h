/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef struct {
    char nume[30], prenume[30];
    int nota_sd, nota_pc;
} TStudent;

typedef struct celula
{ TStudent info;
  struct celula * urm;
} TCelula, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

#define VidaL(L) ((L) == NULL)

/*-- operatii elementare --*/

TLista AlocCelula(TStudent *e);          /* adresa celulei create sau NULL */
void   DistrugeL (ALista);       /* elimina toate celulele din lista */

void AfisareL (TLista L);

#endif
