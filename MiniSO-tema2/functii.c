//Savu Ioana Rusalda 
	//315CB

#include<stdio.h>
#include<string.h>
#include <stdlib.h>

void add(void *c, void *p, FILE * output_file, int PID, int Imem)
{
	size_t d = sizeof(PROC);
	if (IntrQ(c, p, d) == 1)	//se afiseaza mesaj in caz de succes
	{
		fprintf(output_file, "Process created successfully: PID: ");
		fprintf(output_file, "%d, ", PID);
		fprintf(output_file, "Memory starts at ");
		fprintf(output_file, "0x%x.\n", Imem);
	}

}

void add2(void *c, void *p, FILE * output_file, int PID, int Imem)
{
	size_t d = sizeof(PROC);
	IntrQ(c, p, d);//adaugare proces in lista de procese
}

int Memorie(void *c, int PID)
{				//aceasta functie returneaza sfarsitul zonei de memorie al unui proces
	void *caux = NULL;
	int m = 0;
	void *el;
	el = malloc(((TCoada *) c)->dime);
	caux = InitQ(caux, ((TCoada *) c)->dime);
  //initializare coada auxiliara
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
		ExtrQ(c, el);
		if (((PROC *) el)->PID == PID)
			m = ((PROC *) el)->Smem;
      /*m retine sfarsitul zonei de memorie al procesului cautat*/
		IntrQ(caux, el, ((TCoada *) c)->dime);
    //introducere element coada auxiliara
	}
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere element coada auxiliara si adaugare in coada initiala
		ExtrQ(caux, el);
		IntrQ(c, el, ((TCoada *) c)->dime);
	}

	free(el);
	DistrQ(caux);
  //distrugere coada auxiliara
	return m;
}

int get(void *c, int PID, FILE * f)
{
	void *caux;
	void *el;
	int ok = 0;
	el = malloc(sizeof(PROC));
	caux = (TC) malloc(sizeof(TCoada));
	caux = InitQ(caux, sizeof(PROC));
  //test coada vida
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
    //extragere element din coada
		ExtrQ(c, el);
		IntrQ(caux, el, sizeof(PROC));
		if (((PROC *) el)->PID == PID) 
    {
      //afisare timp ramas proces
			fprintf(f, "Process %d is %s (", PID,
				((PROC *) el)->stare);
			fprintf(f, "remaining_time: %lu).\n",
				((PROC *) el)->timp_exec);
			ok = 1;//retine 1 daca procesul a fost gasit in coada
		}

	}
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere proces coada auxiliara si introducere in coada initiala
		ExtrQ(caux, el);
		IntrQ(c, el, sizeof(PROC));
	}
	DistrQ(caux);
	free(el);
  //distrugere coada auxiliara
	return ok;
}

void printW(void *c, FILE * f)
{
  //functia afiseaza procesele din coada de asteptare
	void *caux;
	void *el;
	el = malloc(sizeof(PROC));
	caux = (TC) malloc(sizeof(TCoada));
	caux = InitQ(caux, sizeof(PROC));
	int k = sizeQ(c);
  //k=nr elemente coada;
	fprintf(f, "Waiting queue:\n[");
  //test coada vida
	if (((TCoada *) c)->sc == NULL && ((TCoada *) c)->ic == NULL) 
  {
		fprintf(f, "]\n");
	}
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
    //extragere elemente coada si inroducere in coada auxiliara
		ExtrQ(c, el);
		IntrQ(caux, el, sizeof(PROC));
		if (k != 1) 
    {
			fprintf(f, "(%d: priority = %d, ", ((PROC *) el)->PID,
				((PROC *) el)->prioritate);
			fprintf(f, "remaining_time = %lu),\n",
				((PROC *) el)->timp_exec);
		}
    else
    {
			fprintf(f, "(%d: priority = %d, ", ((PROC *) el)->PID,
				((PROC *) el)->prioritate);
			fprintf(f, "remaining_time = %lu)]\n",
				((PROC *) el)->timp_exec);
		}

		k--;
	}
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere elemente coada auxiliara si introducere in coada initiala
		ExtrQ(caux, el);
		IntrQ(c, el, sizeof(PROC));
	}
	DistrQ(caux);
	free(el);
  //distrugere coada auxiliara
}

void printF(void *c, FILE * f)
{
	void *caux;
	void *el;
	el = malloc(sizeof(PROC));
	caux = (TC) malloc(sizeof(TCoada));
	caux = InitQ(caux, sizeof(PROC));
	fprintf(f, "Finished queue:\n");
  //test coada vida
	if (((TCoada *) c)->sc == NULL && ((TCoada *) c)->ic == NULL) 
  {
		fprintf(f, "[]\n");
	}
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
    //extragere elemente coada si introducere elemente coada auxiliara
		ExtrQ(c, el);
		IntrQ(caux, el, sizeof(PROC));
		fprintf(f, "[(%d: priority = %d, ", ((PROC *) el)->PID,
			((PROC *) el)->prioritate);
		fprintf(f, "executed_time = %lu)]\n",
			((PROC *) el)->timp_exec1);
	}
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere elemente coada auxiliara si introducere in coada initiala
		ExtrQ(caux, el);
		IntrQ(c, el, sizeof(PROC));
	}
	DistrQ(caux);
	free(el);
  //distrugere oada auxiliara
}

int PushS(void *c, int PID, int K)
{
	void *caux = NULL, *s = NULL;
	void *ae = NULL;
	ae = malloc(((TCoada *) c)->dime);
	caux = InitQ(caux, ((TCoada *) c)->dime);
	s = InitS(s, sizeof(int));
	int ok = 0;
  //test coada coada vida
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
    //extragere elemente coada
		ExtrQ(c, ae);
		if (((PROC *) ae)->PID == PID) 
    {

			s = ((PROC *) ae)->st;
			Push(s, &K, sizeof(int));
			ok = 1;//ok retine 1 daca procesul a fost gasit
		}
    //introducere element in coada auxiliara
		IntrQ(caux, ae, ((TCoada *) c)->dime);
	}

	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere elemente coada auxiliara si introducere in coada initiala
		ExtrQ(caux, ae);
		IntrQ(c, ae, ((TCoada *) c)->dime);
	}
	DistrQ(caux);
	free(ae);
  //distrugere coada auxiliara
	return ok;
}

int printStack(void *c, FILE * f, int pid)
{
	void *caux;
	void *saux, *saux2;
	void *el;
	void *el1;
	el = malloc(sizeof(PROC));
	el1 = malloc(sizeof(int));
	caux = (TC) malloc(sizeof(TCoada));
	caux = InitQ(caux, sizeof(PROC));
	saux = (TS) malloc(sizeof(TStiva));
	saux = InitS(saux, sizeof(int));

	saux2 = (TS) malloc(sizeof(TStiva));
	saux2 = InitS(saux, sizeof(int));
	int ok = 0;

	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
    {//extragere element coada
		ExtrQ(c, el);
		if (((PROC *) el)->PID == pid) 
    {
			ok = 1;//ok retine 1 daca procesul a fost gasit
			saux = ((PROC *) el)->st;
			if (((TStiva *) saux)->vf == NULL) 
      {
				fprintf(f, "Empty stack PID %d.\n", pid);
			} 
      else 
      {   //test stiva vida
          while (((TStiva *) saux)->vf != NULL) 
          {//extragere element stiva
					   Pop(saux, el1);
					   fprintf(f, "Stack of PID %d: %d.\n",pid, *((int *)el1));
					   Push(saux2, el1, sizeof(int));
             //adaugare element stiva auxiliara
				  }
			}
			while (((TStiva *) saux2)->vf != NULL) 
      {
        //extragere elemente stiva auxiliara si introducere in stiva initiala
				Pop(saux2, el1);
				Push(saux, el1, sizeof(int));
			}
		}
		IntrQ(caux, el, sizeof(PROC));
    //introducere element in coada auxiliara
	}
	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
    //extragere elemente coada auxiliara si introducere in coada initiala
		ExtrQ(caux, el);
		IntrQ(c, el, sizeof(PROC));
	}
	DistrQ(caux);
	free(el);
  //distrugere coada auxiliara
	return ok;

}

int PopS(void *c, int PID, FILE * output_file)
{

	void *caux = NULL, *s = NULL;
	void *el, *x;
	el = malloc(((TCoada *) c)->dime);
	x = malloc(sizeof(int));
	caux = InitQ(caux, ((TCoada *) c)->dime);
	s = InitS(s, sizeof(int));
	int ok = 0;
  //test coada vida
	while (((TCoada *) c)->sc != NULL && ((TCoada *) c)->ic != NULL) 
  {
    //extragere element coada
		ExtrQ(c, el);
		if (((PROC *) el)->PID == PID) 
    {
			ok = 1;//ok retine valoarea 1 daca procesul a fost gasit
			s = ((PROC *) el)->st;
      //test stiva vida
			if (((PROC *) el)->st->vf == NULL) 
      {
				fprintf(output_file, "Empty stack PID %d.\n",
					PID);
			}
			Pop(((PROC *) el)->st, x);
      //extragere element stiva
		}
		IntrQ(caux, el, ((TCoada *) c)->dime);
    //introducere element coada auxiliara
	}

	while (((TCoada *) caux)->sc != NULL && ((TCoada *) caux)->ic != NULL) 
  {
		ExtrQ(caux, el);
		IntrQ(c, el, ((TCoada *) c)->dime);
    //extragere element coada auxiliara si introducerea lui in coada initiala
	}
	DistrQ(caux);
	free(el);
	return ok;
}
