#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int x, y;
} TPct;

int GenereazaCoadaPct(void* c, size_t N, int v1, int v2)
{ 
  	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!IntrQ(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int GenereazaStivaPct(void* c, size_t N, int v1, int v2)
{ 
	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!Push(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{ 
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
      PrelQ (a, AfiElem);       	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a) 
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */ 
	printf ("%s", antet);          /* afiseaza antetul */
	if (VidaS (a))
    	printf ("Stiva vida!");
  	else
      	Prel_B_V (a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPct*)a).x, (*(TPct*)a).y); 
	return 1;
}

double FC1(void*c)
{
  void *caux;
  TPct x;
  int nr=0,nr_elem=0;
  caux=InitQ(sizeof(TPct), MAX);
  if(!caux)
    return -1;
  while(ExtrQ(c,&x))
  {
    if(x.y%2==1)
      nr++;
    IntrQ(caux,&x);
    nr_elem++;
  }
  while(ExtrQ(caux,&x))
    IntrQ(c,&x);
  return (double)nr*100/nr_elem;
}
double FS1(void*s)
{
  void *saux;
  TPct x;
  int nr=0,nr_elem=0;
  saux=InitS(sizeof(TPct), MAX);
  if(!saux)
    return -1;
  while(Pop(s,&x))
  {
    if(x.x%2==0)
      nr++;
    Push(saux,&x);
    nr_elem++;
  }
  while(Pop(saux,&x))
    Push(s,&x);
  return (double)nr*100/nr_elem;
}
typedef int (*Fcmp)(void*);
typedef int (*Fcmp2)(void*);
int cmp(void *p1)
{
  int x,y;
  x=((TPct*)p1)->x;
  y=((TPct*)p1)->y;
 if(x>2 && y%2==0)
  return 1;
return 0;
}

int cmp2(void *p1)
{
  int x,y;
  x=((TPct*)p1)->x;
  y=((TPct*)p1)->y;
 if(x%2==0 && y%2==0)
  return 1;
else
  if (x%2==1 && y%2==1)
  {
    return 1;
  }
return 0;
}

void FC2(void*c,Fcmp f)
{
  void *caux;
  TPct x;
  //int nr=0,nr_elem=0;
  caux=InitQ(sizeof(TPct), MAX);
  //if(!caux)
    //return -1;
  while(ExtrQ(c,&x))
  {
    //if((x.x>2)&&(x.y%2==0))
    if(f(&x)==1)
      //nr++;
    IntrQ(caux,&x);
    //nr_elem++;
  }
  while(ExtrQ(caux,&x))
    IntrQ(c,&x);
  //return (double)nr*100/nr_elem;
}
void FC3(void*c,Fcmp2 g)
{
  void *caux;
  void * caux2;
  TPct x;
  //int nr=0,nr_elem=0;
  caux=InitQ(sizeof(TPct), MAX);
    caux2=InitQ(sizeof(TPct), MAX);
  //if(!caux)
    //return -1;
  while(ExtrQ(c,&x))
  {
    //if((x.x>2)&&(x.y%2==0))
    if(g(&x)==1)
      //nr++;
      IntrQ(caux,&x);
    else
      IntrQ(caux2,&x);

    //nr_elem++;
  }
  AfiQ("Elemente coada1:\n", AfiPct, caux);
     AfiQ("Elemente coada2:\n", AfiPct, caux2);
  //while(ExtrQ(caux,&x))
    //IntrQ(c,&x);
  //return (double)nr*100/nr_elem;
}

void FS2(void*s,Fcmp f)
{
  void *saux;
  TPct x;
  //int nr=0,nr_elem=0;
  saux=InitS(sizeof(TPct), MAX);
  //if(!caux)
    //return -1;
  while(Pop(s,&x))
  {
    //if((x.x>2)&&(x.y%2==0))
    if(f(&x)==1)
      //nr++;
    Push(saux,&x);
    //nr_elem++;
  }
  while(Pop(saux,&x))
    Push(s,&x);
  //return (double)nr*100/nr_elem;
}

int main()
{ 
	void *c, *s;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	lgc = GenereazaCoadaPct(c, 8, -5, 5);
  	lgs = GenereazaStivaPct(s, 6, 8, 14);
  
	printf("\nCoada cu %d elemente\n", lgc);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	printf("\n\nStiva cu %d elemente\n", lgs);
   	AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);
   printf("FC1=%f\n", FC1(c));
    printf("FS1=%f\n", FS1(s));
    FC2(c,cmp);
    AfiQ("Elemente coada:\n", AfiPct, c);
    FS2(s,cmp);
    AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);
    /*FC2(c,cmp2);
    AfiQ("Elemente coada1:\n", AfiPct, caux);
     AfiQ("Elemente coada2:\n", AfiPct, caux2);*/
    FC3(c,cmp2);


 	/* apeluri functii */

	DistrS(&s);
  	DistrQ(&c);
  	return 0;
}
