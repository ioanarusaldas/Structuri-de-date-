/*--- graf-M.c --- Graf implementat cu Matrice de adiacente --*/
#include "graf-M.h"
#include <string.h>

void* AlocG(int nr)
{ int i;
  AGM g = (AGM)malloc (sizeof(TGM));              /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (int*)malloc(nr * nr * sizeof(int)); /* matrice liniarizata */
  if (!g->x) { free(g); return NULL; }
  for (i = 0; i < nr * nr; i++)
    g->x[i] = ArcInex;
  g->n = nr;
  return (void*)g;
}


void DistrG(void** ag)
{ free (((AGM)(*ag))->x);
  free(*ag);
  * ag = NULL;
}

int CostArc(void* g, int s, int d)
{
  /* functia intoarce costul arcului (s, d); daca arcul nu exista intoarce ArcInex */
  if( ( (s-1)*((AGM)g)->n + d-1 ) < ((AGM)g)->n * ((AGM)g)->n )
    return ((AGM)g)->x[(s-1)*((AGM)g)->n + d-1];

  return ArcInex;
}

int NrNoduri(void* g)
{
    return ((AGM)g)->n;
}

int CitGraf(void** ag)
{ FILE * f;
  char numefis[21];
  int i, j, n;
  int x;
  AGM g;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return -1;
  f = fopen(numefis, "rt");
  if (!f) return -2;
  if (!fscanf(f, "%i", &n) || n <= 0) return -3;
  *ag = g = (AGM)AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &i, &j, &x) == 3)
  { if (i < 1 || i > n || j < 1 || j > n)
    { fclose(f); return -4;}
      ((AGM)g)->x[(i-1)*((AGM)g)->n + j-1] = x;
  }
  fclose(f);
  return 1;
}
int grad_iesire(AGM g,int nod)
{
  int grad=0;
  int* p = g->x + g->n*(nod-1);
  for(int i=0;i<g->n;i++)
  { if(*p!=0)
        grad++;
      p++;
    }
  return grad;
}
void adiacenta(AGM g,int nod)
{
  int grad=0,j=1;
  int m=g->n;
  int v[m];
  for(int i=0;i<m;i++)
    v[i]=0;
  int* p = g->x + g->n*(nod-1);
  for(int i=1;i<g->n;i++)
  { if(*p!=0)
       { v[j]=i;
        j++;}
      p++;

  }
  for(int i=1;i<j;i++)
    printf("%d ",v[i]);
}
void bonus(AGM g)
{
  int grad=0;
  int t;
  int y;
  int min=100;
 int nr=g->n;
  int* p = g->x ;
  for(int i=0;i<g->n;i++)
  {
    for(int j=0;j<nr;j++)
   if(p[j]!=0)
       {
        if(p[j]<min)
        {
          min=p[j];
          t=i/(nr)+1;
          y=j%(nr)+1;
        }

       }
      p=p+nr;
    }
  printf("s=%d\n",t );
   printf("d=%d\n",y );
     printf("min=%d\n",min );
}
