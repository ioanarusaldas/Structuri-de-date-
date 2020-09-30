/*--- TestLista.c ---*/
#include <ctype.h>
#include <stdio.h>
#include "tlista.h"

TLista CitireL(size_t *lg)     /* construieste lista cu elemente citite */
{ TLista L = NULL, u, aux;
  int x;
  char ch;
  TStudent s;

  printf("\nintrodu nr studenti:\n");
  scanf("%lu", lg);

  for(size_t i = 0; i < *lg; i++)
  {
    memset(&s, 0, sizeof(s));
    scanf("%s %s %d %d", s.nume, s.prenume, &s.nota_pc, &s.nota_sd);
    aux = AlocCelula(&s);           /* incearca inserarea valorii citite */
    if(!aux) return L;              /* alocare esuata => sfarsit citire */
    if(L == NULL) L = aux;
    else u->urm = aux;
    u = aux;
  }

  while((ch=getchar()) != EOF && ch != '\n');
  return L;                     /* intoarce lista rezultat */
}

/* pointer la functie ce primeste doi
pointeri de tip student si returneaza un int */
typedef int (*fcmp)(TStudent *s1, TStudent *s2);

int fcmp_p1(TStudent *s1, TStudent *s2) {
  int nume_cmp;

  nume_cmp = strcmp(s1->nume, s2->nume);

  return nume_cmp != 0 ? nume_cmp : (s2->nota_sd - s1->nota_sd);
}

int fcmp_p2(TStudent *s1, TStudent *s2) {
  return strcmp(s1->nume, s2->nume);
}

int fcmp_p3(TStudent *s1, TStudent *s2) {
  return s1->nota_pc + s1->nota_sd - s2->nota_pc - s2->nota_sd;
}

void insert(ALista l, TLista e, fcmp comparator) {
  TLista head = *l, pre = NULL;
  int ok = 0;

  if (*l == NULL) {
    *l = e;
    return;
  }

  for ( ; head != NULL; pre = head, head = head->urm) {
    if (comparator(&e->info, &head->info) <= 0) {
      e->urm = head;

      if (pre == NULL) {
        *l = e;
      } else {
        pre->urm = e;
      }

      ok = 1;

      break;
    }
  }

  if (ok == 0) {
    pre->urm = e;
  }
}

TLista problema1(size_t *lg) {
  TLista L = NULL, u, aux;
  TStudent s;

  printf("\nintrodu nr studenti problema1:\n");
  scanf("%lu", lg);

  for(size_t i = 0; i < *lg; i++)
  {
    memset(&s, 0, sizeof(s));
    scanf("%s %s %d %d", s.nume, s.prenume, &s.nota_pc, &s.nota_sd);
    
    aux = AlocCelula(&s);
    
    if (!aux) {
      return L;
    }

    if (L == NULL) {
      L = aux;
    } else {
      insert(&L, aux, fcmp_p1);
    }
  }

  return L;
}

TLista problema2(ALista l, int *size) {
  TLista r = NULL, head = *l, pre = NULL, aux;

  for (*size = 0; head != NULL; ) {
    if ((head->info.nota_sd >= 9) && (head->info.nota_pc >= 5)) {
      aux = head;
      (*size)++;

      if (pre == NULL) {
        *l = (*l)->urm;
      } else {
        pre->urm = head->urm;
      }

      head = head->urm;
      aux->urm = NULL;
      insert(&r, aux, fcmp_p2);
    } else {
      pre = head;
      head = head->urm;
    }
  }

  return r;
}

int exista(TLista l, TStudent *s) {
  TStudent *info;

  for (; l != NULL; l = l->urm) {
    info = &l->info;

    if ((strcmp(s->nume, info->nume) == 0) && (strcmp(s->prenume, info->prenume) == 0) &&
        (s->nota_pc == info->nota_pc) && (s->nota_sd == info->nota_sd)) {
      return 1;
    }
  }

  return 0;
}

TLista bonus(size_t *lg, int *dup) {
  TLista L = NULL, u, aux;
  TStudent s;

  printf("\nintrodu nr studenti bonus:\n");
  scanf("%lu", lg);

  *dup = 0;

  for(size_t i = 0; i < *lg; i++)
  {
    memset(&s, 0, sizeof(s));
    scanf("%s %s %d %d", s.nume, s.prenume, &s.nota_pc, &s.nota_sd);
    
    if (exista(L, &s)) {
      (*dup)++;

      continue;
    }

    aux = AlocCelula(&s);
    
    if (!aux) {
      return L;
    }

    if (L == NULL) {
      L = aux;
    } else {
      insert(&L, aux, fcmp_p3);
    }
  }

  return L;
}

int main ()
{ TLista x = NULL, y;     /* Lista prelucrata */
  size_t lx;           /* lungime lista */
  int ly, dup;

  for (;;)
  {
    /* citeste si afiseaza lista */
    // x = problema1(&lx);
    // y = problema2(&x, &ly);

    // AfisareL(x);
    // printf("\n");
    // AfisareL(y);
    // printf("\n");
    // AfisareL(x);

    x = bonus(&lx, &dup);
    AfisareL(x);
    printf("\n%d\n", dup);

    if(!x) continue;

    /* apeluri functii implementate */

    DistrugeL(&x);
    printf ("\n  Inca un test ? [d/n]");
    if (getchar() == 'n') break;
  }
}
