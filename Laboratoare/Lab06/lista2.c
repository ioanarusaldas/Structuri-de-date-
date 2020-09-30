/*--- lista2.c ---
      operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "lista2.h"

int InsDupa(TLDI a, void* x)  /* inserare dupa celula cu adresa a -> 1/0 */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
	if(!aux) return 0;
	aux->info = x;
	aux->ant = a;
	aux->urm = a->urm;
	a->urm->ant = aux;
	a->urm = aux;
    return 1;
}


void ResetLDI(TLDI s)
     /* transforma lista in lista vida */
{
	TLDI p = s->urm, aux;
	while(p != s)
	{
		aux = p;
		p = p->urm;
		free(aux->info);
		free(aux);
	}
	s->urm = s->ant = s;
}

void DistrLDI(TLDI* as)
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{
	ResetLDI(*as);
	free(*as);
	*as = NULL;
}

TLDI InitLDI()
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{
	TLDI aux = (TLDI)malloc(sizeof(TCelula2));
    if (!aux) return NULL;

	aux->ant = aux->urm = aux;
    aux->info = NULL;

	return aux;     /* rezultatul este adresa santinelei sau NULL */
}

void AfisareLDI(TLDI s, void (*afiEl)(void *))
    /* afisare lista */
{
	TLDI p;
	printf("Lista: ");
	if(s->urm == s)
	{
		printf("vida\n");
		return;
	}
	for(p = s->urm; p != s; p = p->urm)
		afiEl(p->info);
	printf("\n");
}
 TLDI ex2(TLDI s)
 {
 	TLDI p = s->urm, aux;
 	int i=1;
	while(p != s)
	{

		if(i%2==1)
		{
			aux=p;
			p->urm->ant=p->ant;
			p->ant->urm=p->urm;
			//free(aux->info);
			free(aux);
		}
		p=p->urm;
		i++;
	}

 }
  TLDI ex1(TLDI s1,TLDI s2)
  {
  	TLDI L1=s1->urm,aux;
  	TLDI L2=s2->urm;
  	TLDI p=s1;

  	while((L1!=s1)&&(L2!=s2))
  	{
  		if((*(int *)L2->info) < (*(int *) L1->info))
  		{
  			aux=L2;
  			p->urm=aux;
  			aux->ant=p;
  			p=aux;
  			L2=L2->urm;


  		}
  		
  		else
  		{
  			aux=L1;
  			p->urm=aux;
  			aux->ant=p;
  			p=aux;
  			L1=L1->urm;

  		}
  	
  	}
  	while(L1!=s1)
  	{
  		aux=L1;
  			p->urm=aux;
  			aux->ant=p;
  			p=aux;
  			L1=L1->urm;

  	}
  	while(L2!=s2)
  	{
  			aux=L2;
  			p->urm=aux;
  			aux->ant=p;
  			p=aux;
  			L2=L2->urm;
  	}
  	p->urm=L1;
  	L1->ant=p;

  }