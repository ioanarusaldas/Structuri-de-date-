//Savu Ioana Rusalda 
	//315CB

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "structuri.h"
#include "listegenerice.c"
#include "coada_stiva.c"
#include "functii.c"

int main(int argc, char *argv[])
{
	if (argc != 3) 
	{	// verificare numar de argumente corect
		fprintf(stderr,
			"Usage: %s operations_string in_file out_file\n",
			argv[0]);
		return -1;
	}
	// deschidere fisier pentru citire
	FILE *input_file = fopen(argv[1], "r");

	if (input_file == NULL) 
	{ 	//verificare gasire fisier
		fprintf(stderr, "File \"%s\" not found\n", argv[1]);
		return -2;
	}
	FILE *output_file = fopen(argv[2], "w");
	if (output_file == NULL) 
	{	//deschidere fisier output
		fprintf(stderr, "File \"%s\" not found\n", argv[2]);
		return -2;
	}
	unsigned long timp_total = 0, timp_exec = 0;
	int cuanta = 0, prioritate, v[3000], pr, i, 
	last =0, PID, timpR, pid, n = 0;
	int date;
	char op[15], tip[10];
	unsigned long long memorie, timp;
	PROC proces, runP;
	void *a, *cAsteptare = NULL, *cProcese = NULL, *cFinish = NULL, 
	*s =NULL, *el;
	a = malloc(sizeof(PROC));
	el = malloc(sizeof(int));
	//initializare coada Asteptare,coada de procese si coada de finish
	//cAsteptare=procese in waiting
	//cProcese=toate procesele din sistem
	//cFinish=procese din finish
	cAsteptare = InitQ(cAsteptare, sizeof(PROC));
	cProcese = InitQ(cAsteptare, sizeof(PROC));
	cFinish = InitQ(cAsteptare, sizeof(PROC));
	//initializare stiva
	s = InitS(s, sizeof(int));
	//initializare vector de pid
	for (i = 1; i <= 3000; i++)
		v[i] = 0;
	//citire cuanta de timp
	fscanf(input_file, "%d", &cuanta);

	pr = 0;
	//pr numara procesele adaugate in sistem
	while (fscanf(input_file, "%s", op) != EOF) 
	{

		if (strcmp(op, "add") == 0) 
		{
			pr++;
			//citire argumente funtie add
			fscanf(input_file, "%llu", &memorie);
			fscanf(input_file, "%llu", &timp);
			fscanf(input_file, "%d", &prioritate);
			timp_total = timp_total + timp;
			for (i = 1; i <= pr; i++)
				if (v[i] == 0) 
				{	//verific daca un pid a fost deja atribuit unui alt proces
					//setez pid pentru procesul de adaugat
					proces.PID = i;
					v[i] = i;
				}
			//setez campurile structurii proces
			proces.prioritate = prioritate;
			proces.timp_exec = timp;
			proces.timp_exec1 = timp;
			proces.dim = memorie;
			if (last == 0)
				proces.Imem = 0;
			proces.Imem = Memorie(cProcese, last);
			proces.Smem = proces.Imem + memorie;
			proces.st = InitS(proces.st, sizeof(int));
			//toate procesele sunt adaugate intr-o coada de procese
				//iar intr-o coada de asteptare sunt adaugate procesele care
					// nu ruleaza inca
			if (proces.PID == 1)	//se seteaza starea procesului
			{
				strcpy(proces.stare, "running");
				runP = proces;
			} else
				strcpy(proces.stare, "waiting");
			*(PROC *) a = proces;
			if (((PROC *) a)->PID != 1) 
			{
				//functia add adauga procese in coada si afiseaza mesaj in caz 
					//de succes
				add(cAsteptare, a, output_file, proces.PID,
				    proces.Imem);
				add2(cProcese, a, output_file, proces.PID,
				     proces.Imem);
				//functia add2 adauga procese in coada de procese
			} 
			else 
			{
				add(cProcese, a, output_file, proces.PID,
				    proces.Imem);
			}

			SortQ(cAsteptare);	//se sorteaza coada

			last = proces.PID;
			//last pid retine pid-ul ultimului proces adaugat
		}

		if (strcmp(op, "get") == 0) 
		{
			int n = 0;
			fscanf(input_file, "%d", &PID);
			//se verifica daca procesul cautat se afla in running
			if (runP.PID == PID) 
			{
				fprintf(output_file, "Process %d is %s (", PID,
					runP.stare);
				fprintf(output_file, "remaining_time: %lu).\n",
					runP.timp_exec);
				n = 1;//n retine daca procesul a fost gasit 
			}
			else
				n = get(cAsteptare, PID, output_file);	//apelare functie get
			if (n == 0) 
			{	//daca functia returneaza 0 inseamna ca in coada nu s-a 
					//gasit procesul cu pidul respectiv

				fprintf(output_file, "Process %d not found.\n",
					PID);
			}

		}
		if (strcmp(op, "print") == 0) 
		{

			fscanf(input_file, "%s", tip);
			if (strcmp(tip, "waiting") == 0)
				printW(cAsteptare, output_file);
			else 
				if (strcmp(tip, "finished") == 0) 
				{
					printF(cFinish, output_file);
				} 
				else 
					if (strcmp(tip, "stack") == 0) 
					{
						n = 0;
						fscanf(input_file, "%d", &pid);
						n = printStack(cAsteptare, output_file, pid);
						if (runP.PID == pid) 
						{
							n = 1;
							//n retine daca procesul a fost gasit
							if (runP.st->vf == NULL)
								fprintf(output_file,
								"Empty stack PID %d.\n",
									pid);
							else 
							{//se printeaza stiva procesului
								while (runP.st->vf != NULL) 
								{
									Pop(&runP.st, el);
									fprintf(output_file,
										"Stack of PID %d: %d.\n",pid,
												*((int *)el));
								}
							}
						}

						if (n == 0)//test proces gasit
							fprintf(output_file,
								"PID %d not found.\n", pid);
					}
		}
		if (strcmp(op, "run") == 0) 
		{
			fscanf(input_file, "%d", &timpR);
			timp_exec = timp_exec + timpR;
			void *ae;
			int t = timpR;	//t retine timpul de executie al proceselor
			ae = malloc(sizeof(PROC));
			while (t > 0) 
			{
				runP.timp_exec = runP.timp_exec - cuanta;
				if (runP.timp_exec != 0)	//se verifica daca procesul 
												//s-a terminat
				{
					strcpy(runP.stare, "waiting");
					IntrQ(cAsteptare, &runP, sizeof(PROC));
					//procesul din running este trecut in coada de asteptare
					ExtrQ(cAsteptare, ae);
					//se extrage primul proces din coada de asteptare
					SortQ(cAsteptare);
					//se sorteaza coada
					runP = *(PROC *) ae;
					strcpy(runP.stare, "running");
					//procesul extras anterior este trecut in running

				} 
				else 
				{
					//procesele terminate sunt trecute in coada de finish
					IntrQ(cFinish, &runP, sizeof(PROC));
					v[runP.PID] = 0;
					//pid-ul procesului devine disponibil
					pr--;
					last = last - 1;
					ExtrQ(cAsteptare, ae);
					runP = *(PROC *) ae;
					//un nou element e trecut in running
				}
				t = t - cuanta;
				//se micsoreaza timpul de executie al proceselor
			}
		}

		if (strcmp(op, "push") == 0) 
		{
			int n = 0;
			fscanf(input_file, "%d", &pid);
			fscanf(input_file, "%d", &date);
			n = PushS(cAsteptare, pid, date);
			//se face push pe stiva procesului cu pid-ul cautat
			//daca s-a gasit procesul ,functia returneaza 1 si returneaza 0 in 
				//caz contrar
			if (runP.PID == pid) 
			{
				n = 1;
				Push(&runP.st, el, sizeof(int));
				//se face push pe procesul din running
			}
			if (n == 0)
				//verificare existenta proces cu pid-ul cautat
				fprintf(output_file, "PID %d not found.\n",
					pid);
		}
		if (strcmp(op, "pop") == 0) 
		{

			int n = 0;
			fscanf(input_file, "%d", &pid);
			n = PopS(cAsteptare, pid, output_file);
			//functia pop returneaza 1 daca procesul a fost gasit
			if (runP.PID == pid)
				n = 1;
			if (n == 0)
				fprintf(output_file, "PID %d not found.\n",
					pid);
		}
		if (strcmp(op, "finish") == 0) 
		{
			//timpul total este calculat ca diferenta dintre timpul total
			//necesar rularii proceselor si timpul de executia realizat pana
					//la apelarea functiei finish
			fprintf(output_file, "Total time: %lu\n",
				timp_total - timp_exec);
		}

	}
	fclose(input_file);
	fclose(output_file);
	return 0;
}
