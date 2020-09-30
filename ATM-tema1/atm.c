/*Savu Ioana Rusalda*/
/*315CB*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structuri.h"
#include "functii.c"
int main()
{

	char op[10];
	int nrMaxcard,card =0;
	unsigned long long Nrcard, Nrcard2;
	char pin[10];
	char dataexp[10];
	char CVV[5];
	int max = -1;
	int insert;
	unsigned long balance;
	unsigned long sum;
	TLLC aux = NULL;
	TLLC L = NULL;
	TLLC L2 = NULL;

	FILE *f;
	f = fopen("output.out", "w");

	FILE *file;
	file = fopen("input.in", "r");

	if (file == NULL)
		fprintf(stderr, "ERROR: Can't open file %s", "input.txt");
	if (file) 
    {
		fscanf(file, "%d", &nrMaxcard);
        int i;
		for (i = 0; i < nrMaxcard; ++i)  
        {
			InsInc(&L);/*insert celule LC*/
		}
		insert = 0;
		while (fscanf(file, "%s", op) != EOF) /*cat timp citeste din fisier*/
        {
			if (strcmp(op, "show") == 0) 
            {
				insert = 0;
				if (fscanf(file, "%llu", &Nrcard) == 1) 
                {

					showcard(L, Nrcard, f);
				} 
                else 
                {
					show(L, f, max);
				}
			}

			if (strcmp(op, "add_card") == 0) 
            {
				int i = -1, j = -1;
				insert = 0;
				int p;
				TLLC aux1;
				TLSC aux2;
				TLLC aux3;
                Tcard a;
				fscanf(file,"%llu",&Nrcard);
				   fscanf(file,"%s",pin);
				   fscanf(file,"%s",dataexp);
				   fscanf(file,"%s",CVV); 
				L2 = NULL;
                int pozitie = poz(Nrcard,nrMaxcard);
                TLLC aux4;
                int l=0;
                int ex;
                /*verifica daca cardul ce urmeaza sa fie 
                    adaugat exista deja in functie*/
                for (aux4 = L;aux4 != NULL;aux4 = aux4->urmLC)
                {
                    if (pozitie == l)
                    {
                        ex=exist(aux4->subset,Nrcard);
                        break;
                    }
                    l++;

                }

                if(ex == 0)/*daca cardul nu exista se mareste nr de carduri */
                    card++;
                else
                    fprintf(f,"The card already exists\n");

				if (((card > nrMaxcard) && (ex == 0)))
                /*se verifica daca se mai pot adauga carduri*/
                {
					nrMaxcard = nrMaxcard * 2;
                    int k;
					for ( k = 0; k < nrMaxcard / 2; ++k) 
                    /*se completeaza lista veche cu celule*/
                    {

						InsInc(&L);
					}

					for (k = 0; k < nrMaxcard; ++k) 
                    {
						InsInc(&L2);/*se creeaza o noua lista*/
					}
					for (aux1 = L; aux1 != NULL;aux1 = aux1->urmLC) 
                    {
						for (aux2 = aux1->subset; aux2 != NULL;
                                    aux2 = aux2->urmcard) 
                        {
							j = -1;
							p = poz(aux2->infocard->nrCard,nrMaxcard);
                            /*se calculeaza noile pozitii*/
							for (aux3 = L2;aux3 != NULL;aux3 = aux3->urmLC) 
                            {
                                /*se adauga cardurile vechi in noua lista*/
								j++;
								if (p == j) 
                                {
									if (p >max)/*max retine pozitia maxima*/
										max = p;
									break;
								}
							}
                            a=aux2->infocard;
							add_card(&aux3->subset,a->nrCard,a->pin,
                            a->dataexp,a->CVV,a->status,a->balance,
                            a->wrong,a->Hy) ;
						}
					}

					L = L2;
				}
                /*lista este actualizata*/
                /*se continua adagugarea cardurilor*/
                i=-1;
				for (aux = L; aux != NULL; aux = aux->urmLC) 
                {
					i++;
					p = poz(Nrcard, nrMaxcard);
					if (p == i) 
                    {
						if (p > max)
							max = p;
						break;
					}

				}
                
           add_card(&aux->subset, Nrcard, pin, dataexp,CVV,"NEW",0,0,NULL);
			}

			if (strcmp(op, "delete_card") == 0) 
            {
				card--;
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				for (aux = L; aux != NULL; aux = aux->urmLC) 
                {
					delete_card(&aux->subset, Nrcard);
				}
			}
			if (strcmp(op, "insert_card") == 0) 
            {
				insert++;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%s", pin);
				insert_card(Nrcard, pin, &L, f, insert);

			}
			if (strcmp(op, "cancel") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				cancel(Nrcard, &L);

			}
			if (strcmp(op, "unblock_card") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				unblock_card(Nrcard, &L);
			}
			if (strcmp(op, "pin_change") == 0) 
            {

				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%s", pin);
             /*functia de inert este apelata cu 1 daca PIN-ul este corect */
				if (strlen(pin) != 4)
					pin_change(Nrcard, &L, pin, 0, f);
				else 
                {
					if (valid_pin(pin) == 0) 
                    {
						pin_change(Nrcard, &L, pin, 0,
							   f);
					} 
                    else 
                    {

						pin_change(Nrcard, &L, pin, 1,
							   f);
					}
				}

			}
			if (strcmp(op, "balance_inquiry") == 0)
			{
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				balance_inquiry(Nrcard, &L, f);
			}
			if (strcmp(op, "recharge") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%lu", &balance);
				recharge(Nrcard, &L, balance, f);
			}

			if (strcmp(op, "cash_withdrawal") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%lu", &sum);
				cash_withdrawal(Nrcard, &L, sum, f);
			}

			if (strcmp(op, "transfer_funds") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%llu", &Nrcard2);
				fscanf(file, "%lu", &sum);
				transfer_funds(Nrcard, Nrcard2, &L, sum, f);
			}
			if (strcmp(op, "reverse_transaction") == 0) 
            {
				insert = 0;
				fscanf(file, "%llu", &Nrcard);
				fscanf(file, "%llu", &Nrcard2);
				fscanf(file, "%lu", &sum);
				reverse_transaction(Nrcard, Nrcard2, &L, sum,f);
			}

		}

		fclose(file);

	}
	distrugereLC(&L);
	distrugereLC(&L2);
	fclose(f);

	return 0;
}
