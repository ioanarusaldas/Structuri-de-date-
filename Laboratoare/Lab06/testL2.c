#include "lista2.h"

void AfiInt(void * ax)
{
	printf("%d ", *(int*)ax);
}

void CitireLDI(TLDI s, int* lg)
{
	int *ax, x;
 	char ch;

  	printf("se citesc valori numerice, terminate cu caracter nenumeric\n");
	for(*lg = 0; scanf("%i", &x) == 1; )
  	{
        ax = (int*)malloc(sizeof(int));
		if(!ax) return;
	 	*ax = x;
		InsDupa(s->ant, ax);
    		(*lg)++;
  	}
  	while((ch=getchar()) != EOF && ch != '\n');
}

int main()
{
	TLDI s1,s2;
	int lg;

	for(; ; )
	{
		s1 = InitLDI();
		CitireLDI(s1, &lg);
		s2 = InitLDI();
		CitireLDI(s2, &lg);
		AfisareLDI(s1, AfiInt);
		AfisareLDI(s2, AfiInt);
		//ex2(s);
		ex1(s1,s2);
		AfisareLDI(s1, AfiInt);
		//AfisareLDI(s2, AfiInt);

		/* apeluri functii */

		
		printf ("\n  Inca un test ? [d/n]");
		if (getchar() == 'n') break;
	}
    return 1;
}
