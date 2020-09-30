/*-- testHash.c  */
#include "tlg.h"
#include "thash.h"
#include <string.h>

//Produsul are un nume, un pret si un cod
typedef struct {char nume[10], codProdus[5]; double pret;} TProdus;


//generez un cod  unic in functie de primul caracter din sir
int codHashNume(void*a)
{
	char *p = ((TProdus*)a)->nume;
  return (*p-'a');
}

void AfiElProd(void * ae)
{
  TProdus *p = (TProdus*)ae;
  printf("[%s %s %lf]\n", p->nume, p->codProdus, p->pret);
}

TLG GenerareListaProd(size_t nrProd)
{
	/*citesc in ordine pentru nr pers
		numele - max 10 caractere
		cod produs - max 5 caractere
        pret - double
	 */
  size_t i;
  int rez;
	TLG r = NULL;
	TProdus *p;

  printf("Se vor introduce nume, cod produs, pret pentru %zu produse: \n", nrProd);
	for(i = 0; i < nrProd; i++)
	{
        p = (TProdus*)malloc(sizeof(TProdus));
        if(!p) return r;
        printf("introdu nume, cod produs, pret - produs %zu:",i+1);
        scanf("%s%s%lf", p->nume, p->codProdus, &(p->pret));

		rez = InsLG(&r,p);
		if(!rez)
		return r;
	}
	return r;
}

//functii care compara 2 persoane dupa nume respectiv dupa telefon
int cmpProdNume(void *p1,void*p2)
{
	return strcmp( ((TProdus*)p1)->nume, ((TProdus*)p2)->nume );
}

int cmpProdCod(void *p1, void*p2)
{
	return strcmp( ((TProdus*)p1)->codProdus, ((TProdus*)p2)->codProdus );
}


//generare tabela hash pe baza listei de produse - functia hash ia in calcul primele 2 caractere ale numelui (convertite in prealabil la lowercase)
TH* GenerareHash(TLG listaProd)
{
  TH *h = NULL;
	TLG p;
  TProdus *produs;
	int rez;

	//calcul dimensiuni maxime pt tabela hash
	size_t M = ('z'-'a');

	//initializare tabela hash
	h = (TH*)IniTH(M, codHashNume);
	if(!h) return NULL;

	for(p = listaProd; p != NULL; p = p->urm)
	{

        produs = (TProdus*)malloc(sizeof(TProdus));
        if(!produs) return h;
        memcpy(produs, p->info, sizeof(TProdus));
				rez = InsTH(h, produs, cmpProdNume);
        if(!rez) {free(produs); return h;}
	}

	return h;
}
int f(void *el,double max)
{
	double p=((TProdus*)el)->pret;
	if(p<max)
		return 1;
	return 0;

}

int elimina(ALG L,fcmp f,double max)
{
	TLG ant,p;
	////if(*L->urmcard==NULL)
		//L=NULL;
	for( p = *L, ant = NULL; p != NULL; /*ant = p,*/ p = p->urm )
		
		if(f(p->info,max)==1)
			//break;
	{if(p==NULL)
		return 0;
	if(ant==NULL)
		*L=p->urm;
	else 
		ant->urm=p->urm;
	free(p);}
	//p=NULL;
	return 1;
}
int ex2(ALG L,fcmp f,double max)
{
	TLG ant,p;
	////if(*L->urmcard==NULL)
		//L=NULL;
	for( p = *L, ant = NULL; p != NULL; /*ant = p,*/ p = p->urm )
		
		if(f(p->info,max)==1)
			//break;
	return p->info;
}


/*int delete (TH *h, fcmp f,double max)
{
	void * el;
	int i;
	TLG *aux; 
	for(i=0;i<h->M;i++)
		//for(aux = h->v[i]; aux != NULL; aux = aux->urm)
			elimina(&h->v[i],f,max);




}*/
void * e (TH *h, fcmp f,double max)
{
	void * el;
	int i;
	TLG *aux; 
	for(i=0;i<h->M;i++)
		//for(aux = h->v[i]; aux != NULL; aux = aux->urm)
			ex2(&h->v[i],f,max);
	}

int main()
{
 TLG x = NULL;
 TH *h = NULL;
//int max;
//printf("introduceti pret max: ");
	//fscanf("%d",&max);

	x = GenerareListaProd(3);
  if(!x)
  {
        printf("Lista nu a putut fi generata\n");
        return 0;
  }

  printf("\n");
  Afisare(&x, AfiElProd);

  h = GenerareHash(x);
  printf("Tabela hash:\n");
	AfiTH(h, AfiElProd);

  /* secvente de test */
	//e(h,f,50);
	AfiElProd(e(h,f,50));
	 printf("Tabela hash:\n");
	AfiTH(h, AfiElProd);
  Distruge(&x, free);
	DistrTH(&h, free);
  return 0;
}
