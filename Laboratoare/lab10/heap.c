/*-- heap.c --*/
#include "heap.h"

#define NMAX 25
static char desen[20][81], cri[] = "xxx";  /* caractere reprezentare arbore, info */

AHeap AlocaHeap(int n, TRel r)
{
    AHeap a = (AHeap)malloc(sizeof(THeap));
    if(!a) return NULL;
    a->v = (int*)malloc(sizeof(int) * n);
    if (!a->v) {free(a); return NULL;}
    a->Max = n; a->ne = 0; a->rel = r;
    return a;
}

void DistrugeHeap(AHeap* aa)
{
    free((*aa)->v);
    free(*aa);
    *aa = NULL;
}

void Afi(AHeap a, int k, int centru, int linie, int dif)
     /*- functie auxiliara - pregateste desen arbore, cu radacina in centru linie
	 dif - distanta pe orizontala intre radacina si cei doi descendenti
	       Exemple:  dif = 5    |     dif = 2    |
				   xxx                 xxx
				___/ \___              / \
     -*/
{ int s, d;
  desen[linie][0] = ':';
  if (dif <= 1)      /* spatiu de afisare insuficient -> ... */
    { memset (desen[linie]+centru, '.', 3); return; }
    
  desen[linie][centru] = '|';      /* legatura spre radacina */
  sprintf (cri, "%3i", a->v[k]);   /* converteste valoare info la 3 caractere */
  d = (cri[0] == ' ') ? 2 : 1;     /* decalaj fata de centru */
  memcpy(desen[linie+1] + centru - d, cri, 3); /* copiaza cele 3 caractere in desen */
  desen[linie+1][0] = ':';  desen[linie+2][0] = ':'; 
  
  if ((s = k * 2 + 1) < a->ne)
  { desen[linie+2][centru-1] = '/';
    memset(desen[linie+2] + centru - dif + 1, '_', dif-2);
    Afi(a, s, centru - dif, linie + 3, (dif+1)/2 );
  }
    
  if (s + 1 < a->ne)
  { desen[linie + 2][centru+1] = '\\';
    memset (desen[linie+2] + centru + 2, '_', dif-2);
    Afi(a, s + 1, centru + dif, linie + 3, (dif+1)/2);
  }
}

void AfiHeap(AHeap a, int linie)
     /*- afiseaza arborele r in partea superioara a ecranului -*/
{ int j;
  for (j = 0; j < 20; j++) memset (desen[j], ' ', 79);
  if (a->ne == 0)
    printf("\t\t\t\t-=- Arbore VID -=-\n");
  else
  { printf("\n");
    Afi(a,0,40,0,19); /* afiseaza incepand de la mijlocul primei linii de pe ecran */
    for (j = 0; j < 16 && desen[j][0] == ':'; j++)
      { desen[j][79] = '\0'; printf("%s\n", desen[j]+1); }
  }
  printf("\n");
}


int MaiMic (int a, int b)
{ return a < b ? -1 : (a < b); }
int MaiMare (int a, int b)
{ return a > b ? -1 : (a > b); }
int Inserare(AHeap a,int x)
{
  int p=a->ne,parinte,aux;
  if(a->ne==a->Max)
    return 0;
  a->v[p]=x;
  a->ne++;
  while(p>0)
  {
    parinte=a->v[(p-1)/2];
    if(MaiMic(x,parinte)==-1)
    {
       aux=a->v[p];
        a->v[p]=a->v[(p-1)/2];
        a->v[(p-1)/2]=aux;
        p=(p-1)/2;
    }
    else
      break;

  }
}

int Extragere(AHeap a)
{
  int element=a->v[0],p,c,aux,ne=a->ne;
  a->v[0]=a->v[ne-1];
  a->ne--;
  p=0;
  while(2*p+1<ne)
  {
    c=2*p+1;
    if((2*p+2<ne)&&(a->v[c+1]<a->v[c]))
      c++;
    if(a->v[p]<a->v[c])
      break;
    else{
      aux=a->v[p];
      a->v[p]=a->v[c];
      a->v[c]=aux;
      p=c;}

  }
  return element;
}
void bonus(int v[6])
{
  AHeap arb;
  int i,a[6];
  arb = AlocaHeap(NMAX, MaiMic);
   for(i = 0; i < 6; i++)
        arb->v[arb->ne++] = v[i];
      for(int j=0;j<6 ;j++)
        a[j]=Extragere(arb);
       for(int j=0;j<6 ;j++)
        printf("%d ",v[j] );
      printf("\n");

}


int main()
{
    AHeap arb;
    //max int testv[] = {20, 10, 4, 3, 5, 2}, i;
      int testv[] = {2, 3, 5, 4, 10, 20}, i;
    
    arb = AlocaHeap(NMAX, MaiMare);
    if(!arb) return 0;
    
    /* copiaza in heap cele 6 elemente din vectorul testv */
    for(i = 0; i < 6; i++)
        arb->v[arb->ne++] = testv[i];

    
    AfiHeap(arb, 13);
   // Inserare(arb, 12);
      //Inserare(arb, 18);
    //int x=Extragere( arb);
    //printf("element=%d\n",x );
       // Inserare(arb, 21);
     //AfiHeap(arb, 13);
    bonus(testv);

    
    DistrugeHeap(&arb);
    return 1;
}