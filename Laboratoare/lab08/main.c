/**-- main.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"

/*-- se completeaza cu definitiile functiilor implementate --*/

void RSD(TArb a)
{
	if(!a) {printf("-"); return;}
	if(!a->st && !a->dr) {printf(" %d ", a->info); return;}
	printf(" %d ", a->info);
	printf("(");
	RSD(a->st);
	printf(",");
	RSD(a->dr);
	printf(")");
}
int sum(TArb a)
{
	if(a==NULL)
		return 0;
	return sum(a->st)+a->info+sum(a->dr);
}

int numara(TArb a)
{
	int nr,sum=0;
	if(a==NULL)
		return 0;
	nr=numara(a->st)+numara(a->dr);
	if(a->st!=NULL)
		sum = sum+a->st->info;
	if(a->dr!=NULL)
		sum = sum+a->dr->info;
	if(a->info>sum)
		nr++;
	return nr;

}
int vector(TArb a,int v[20],int niv)
{
	if(a==NULL)
		return 0;
	if(a->info<v[niv])
		v[niv]=a->info;
	vector(a->st,v,niv+1);
	vector(a->dr,v,niv+1);

}

int maxim(TArb a)
{
	int dr,st,p;
	if(a==NULL)
		return 0;
	p=a->info;
	dr=maxim(a->dr);
	st=maxim(a->st);
	if(a->dr!=NULL)
		if(dr>p)
			p=dr;
	if(a->st!=NULL)
		if(st>p)
			p=st;
	return p;
}

int identici(TArb a,TArb b)
{
	if(a==NULL && b==NULL)
		return 1;
	if((a==NULL && b!=NULL)||(b==NULL && a!=NULL))
		return 0;
	if(a->info == b->info && identici(a->st,b->st)==1 && identici(a->dr,b->dr)==1)
		return 1;
	return 0;

}
int nrlab9(int x,int y,TArb a)
{
	
	if(!a)
		return 0;
	if(a->info<=y && a->info >=x)
	{
		//nr++;
		printf(" interval =%d\n",a->info);
		return 1+nrlab9(x,y,a->st)+nrlab9(x,y,a->dr);
	}
	else
		if(a->info>=y)
			return nrlab9(x,y,a->st);
		else
			return nrlab9(x,y,a->dr);

}
void pr2(TArb a)
{
	TArb dr1,st1;

	if(a->st!=NULL)
		st1=a->st;
	if(a->dr!=NULL)
		dr1=a->dr;
	while(st1->dr)
		st1=st1->dr;
	while(dr1->st)
		dr1=dr1->st;
	if(a->st!=NULL && a->dr!=NULL)
		if(a->info-st1->info < a->info-dr1->info)
			printf("pr%d\n", st1->info);
		else
			printf("pr%d\n", dr1->info);
	if(a->st==NULL)
	printf("pr%d\n", dr1->info);


	if(a->dr==NULL)
		printf("pr%d\n", st1->info);



}
int main ()
{
	TArb arb;
	int v[20];
	int i;

	randomize();
	do {
		arb = ConstrAA (4, -50, 50);
		AfiArb (arb);
		printf ("noduri: %i   niveluri: %i\n",
			NrNoduri(arb), NrNiv(arb));
		RSD(arb);
		 int Z=nrlab9(-50,20,arb);
		 printf("%d\n",Z );
		 pr2(arb);
		/*printf("\nex1=%d\n",numara(arb));
			printf("\nex3=%d\n",maxim(arb));
			for(i=0;i<NrNiv(arb);i++)
				v[i]=60;
			vector(arb,v,0);
			for(i=0;i<NrNiv(arb);i++)
				printf("%d ",v[i]);

				if( identici(arb,b)==1)
					printf("identici\n");
				else
					printf("diferiti\n");*/
				
		/*-- se completeaza cu apelurile functiilor implementate --*/

		DistrArb (&arb);
		//DistrArb (&b);

		printf ("\nInca un arbore ? [D/N] ");

		if (getchar() == 'n') break;
		printf("\n");
	} while (1);

	return 0;
}
