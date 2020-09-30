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

TLista Copie(TLista L,int a ,int b)
{
  TLista r,aux,u;
  r=NULL;
  while(L)
  {
    if((L->info >=a )&&(L->info <=b ))
    {
    aux=AlocCelula(L->info);
    if(!aux)
      return r;
    if(r==NULL)
      r=aux;
    else
      u->urm=aux;
    u=aux;
    }
    L=L->urm;
  }
  return r;
}
int prim(int x)
{
  int div=0;
   for(int i=1; i<=x; i++){
        if(x%i == 0)
            div++;
    }
        if (div ==2)
            return 1;
    return 0;
}
 TLista Mutare(ALista aL)
 {
  TLista r=NULL,u,ant=NULL,p=*aL,aux;
  while(p!=NULL)
    if(prim(p->info)==1)
    {
      aux=p;
      p=p->urm;
      if(r==NULL)
        r=aux;
      else
        u->urm=aux;
      u=aux;
      if(ant==NULL)
        *aL=p;
      else ant->urm=p;
    }
    else
    {
      ant=p,p=p->urm;
    }
    if(r)
      u->urm=NULL;
    return r;
 }

int Inserarefinal(ALista aL, int x) {
  TLista u = NULL, aux;
  if (*aL != NULL) {
    u = *aL;
    while (u->urm != NULL)
      u = u->urm;
  }
  aux = AlocCelula(x);
  if (!aux)
    return 0;
  if (u ==NULL) {
    *aL = aux;
  } else {
      u->urm = aux;
    }
  return 1;
}





TLista ex3(TLista a,TLista b)
{
  TLista r=NULL;
    for (; a != NULL && b != NULL ; a = a->urm,b = b->urm) 
      if(a->info>=b->info)
        Inserarefinal(&r,a->info);
      else
        Inserarefinal(&r,b->info);
    while(a!=NULL)
      {Inserarefinal(&r,a->info);
        a = a->urm;
      }
    while(b!=NULL)
    {Inserarefinal(&r,b->info);
      b = b->urm;
    }
  return r;

}
/*TLista bonus(TLista a,TLista b)
{
  TLista p=NULL;
  while((a!=NULL) && (b!=NULL))
  {
    if(a->info < b->info)
     { a=a->urm;
      Inserarefinal(&p,a->info);

    else
    {
      if(a->info==b->info)
      {

        b=b->urm;
        a=a->urm;
      }
      b=b->urm;
    }

  }
  return p;
}*/