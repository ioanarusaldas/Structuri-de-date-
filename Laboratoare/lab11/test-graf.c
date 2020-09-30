/*--- test-graf.c ---*/
#include "graf.h"

void AfiM(void* g)
{ int i,j,k, n = NrNoduri(g);
  for (i = 1; i <= n; i++)
  { for (j = 1; j <= n; j++)
    { k = CostArc(g,i,j);
      if(k == ArcInex) printf("  - ");
      else printf("%3i ", k);
    }
    printf("\n");
  }
}

int main()
{
  void* g;
  int grad,grad2;

  if (CitGraf(&g) <= 0)
  { printf("-=- eroare la citire -=-\n"); return -1;}
  printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
  AfiM(g);
  int v[10];
 // grad=grad_iesire(g,2);
  //printf("%d\n",grad );
  // grad2=grad_iesireL(g,3);
   // printf("%d\n",grad2 );
  //adiacenta( g,3);
  //adiacentaL(g,3);
  bonus(g);
   

  /*-- apel functii definite --*/
  DistrG(&g);
  return 0;
}
