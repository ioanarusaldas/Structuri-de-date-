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
  size_t lx;  
  TLista y = NULL;     /* Lista prelucrata */
  size_t ly; 
  int nr;         /* lungime lista */

  for (;;)
  {
    /* citeste si afiseaza lista */
    printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    x = CitireL(&lx);
    AfisareL(x);
    if(!x) continue;
     /*printf("\nIntroduceti valori elemente terminate cu valoare nenumerica:\n");
    y = CitireL(&ly);
    AfisareL(y);
    if(!y) continue;*/

    /* apeluri functii implementate */
    /*nr=el(x);
    printf("\n nr elemente=%d\n",nr );
    par(x);*/
    printf("\n");
    //perechi(x);
    /*int c=0;


    c=identic(x);
    if(c==0)
      printf("nu\n");
    else
      printf("da\n");*/
    int c;
    int n=0;
    //c=sub(x,y,&n);
    //printf("%d\n",c );
    bonus(x);
    AfisareL(x);

    DistrugeL(&x);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}
