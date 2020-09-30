/*-- functiiLista.c --*/
#include <ctype.h>
#include "tlista.h"

/*--- operatii de baza pentru lista simplu inlantuita ---*/

TLista AlocCelula(int e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCelula));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

void AfisareL(TLista L)
       /* afiseaza valorile elementelor din lista */
{
  printf("Lista: [");                      /* marcheaza inceput lista */
  for (; L != NULL; L = L->urm)       /* pentru fiecare celula */
    printf("%d ", L->info);              /* afiseaza informatie */
  printf("]");                               /* marcheaza sfarsit lista */
}

void DistrugeL(ALista aL)
{
  TLista aux;
  while(*aL)
  {
    aux = *aL;
    *aL = aux->urm;
    free(aux);
  }
}

int el(TLista L)
{
 TLista aux;
  int nr=0;
  for(aux=L;aux!=NULL;aux=aux->urm)
    nr++;
  return nr;
}
//leetcode.com

void par(TLista L)
{
  int i1=0,i2,nr=0;
  TLista aux;
  for(aux=L;aux!=NULL;aux=aux->urm)
  {  nr++;
      if((aux->info %2==0)&&(i1==0))
        i1=nr;
      else
        if(aux->info %2==0)
          i2=nr;  
  }
printf("\nprima aparitie= %d\n", i1);
printf("\na doua aparitie= %d\n", i2);

}

void perechi(TLista L)
{
  TLista aux,aux2;
  int nr=0,nr2,nrp=0;
  for(aux=L;aux->urm!=NULL;aux=aux->urm)
  {  nr++;
    nr2=nr+1;
    aux2=aux->urm;
    if((aux->info%2==0)&&(aux2->info%2==0))
      {printf("(%d,%d):%d %d\n",nr,nr2,aux->info,aux2->info);
    nrp++;}
    else
      if((aux->info%2==1)&&(aux2->info%2==1))
        {printf("(%d,%d):%d %d\n",nr,nr2,aux->info,aux2->info);
      nrp++;}

  }
  printf("%d\n",nrp );

  }
int identic(TLista L)
{
  TLista aux,adr;
  int i;
  int nr=0,r=0;
  for(aux=L;aux!=NULL;aux=aux->urm)
    nr++;
  if(nr%2==1)
    return 0;
  adr=L;
  aux=L;
  i=1;
  int j=1;
  while(i<=nr/2)
  {
    adr=adr->urm;
    i++;
  }
  while(j<=nr/2)
  {
    //printf("mama\n");
    if(aux->info!=adr->info)
      return 0;
    else
    {
      aux=aux->urm;
      adr=adr->urm;
      j++;
      r++;
      //printf("%d\n",r );
    }
  }
  if(r==nr/2)
    return 1;
  else
    return 0;
}

int sub(TLista A, TLista B,int *index)
{
  TLista a,b;
  int nr=0,i=0;
  int j=0;
  for(a=A;a!=NULL;a=a->urm)
  {
    nr++;
  }
  a=A;
  b=B;
   while(b)
   {
    if(a->info==b->info)
    {
      a=a->urm;
      b=b->urm;
      j++;
      i++;


    }
    else
    {
      b=b->urm;
      j++;
      a=A   ;
      i=0;
    }

   
   if(i==nr)
    { *index=j;
      printf("%d\n",*index );
      return 1;
    }
  
}
return -1;


}  

int inserareDupa(TLista L,int x,int ref)
{
  TLista p=NULL,aux;

  while(L!=NULL)
  {
    if(L->info==ref)
    {
      p=L;
      break;
    }
    L=L->urm;
  }

  if(p==NULL)
    return 0;

  aux=AlocCelula(x);

  if(!aux)
    return 0;
  aux->urm=p->urm;
  p->urm=aux;

  return 1;
}

int bonus(TLista L)
{
  TLista aux=L;

  int k=0;
  while(aux)
  {
    if(aux->info%2==1)
    {
      inserareDupa(L,aux->info,aux->info);
      aux=aux->urm;
      k++;
    } 
    aux=aux->urm;

  }
  return k;
}


