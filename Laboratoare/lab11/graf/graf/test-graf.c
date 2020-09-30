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

  if (CitGraf(&g) <= 0)
  { printf("-=- eroare la citire -=-\n"); return -1;}
  printf(" -=- graf cu %i noduri -=-\n", NrNoduri(g));
  AfiM(g);

  /*-- apel functii definite --*/
  DistrG(&g);
  return 0;
}
