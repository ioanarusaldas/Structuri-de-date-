/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

TLista Copie(TLista L)
{
  TLista r,aux,u;
  r=NULL;
  while(L)
  {
    aux=AlocCelula(L->info);
    if(!aux)
      return r;
    if(r==NULL)
      r=aux;
    else
      u->urm=aux;
    u=aux;
    L=L->urm;
  }
  return r;
}
