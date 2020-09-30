/*--- TestLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include "tlista.h"

TLista CitireL(size_t *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  for(*lg = 0; scanf("%i", &x) == 1; )
  {
    aux = AlocCelula(x);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
    (*lg)++;
  }

  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

int main ()
{ TLista x = NULL;     /* Lista prelucrata */
  TLista y = NULL;  
  TLista r=NULL;
  int a=2,b=9;
  //int r;
  size_t lx;   
  size_t ly;         /* lungime lista */

  for (;;)
  {
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    x = CitireL(&lx);
    AfisareL(x);
    if(!x) continue;

/* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    y = CitireL(&ly);
    AfisareL(x);
    if(!y) continue;
0    /* apeluri functii implementate */
    //r=Copie(x);

    r=Copie(x,a,b);
    //r=Mutare(&x);
    //r=ex3(x,y);
    AfisareL(r);

    DistrugeL(&x);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}
