/*Savu Ioana Rusalda*/
/*315CB*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*functia poz calculeaza pozitia unui card 
		dupa formula din enunt*/
int poz(unsigned long long NrCard, int NrMax)
{
	int sum = 0;
	int j;
	while (NrCard != 0) 
	{
		sum = sum + NrCard % 10;
		NrCard = NrCard / 10;
	}
	/*in while se calculeaza suma cifrelor*/
	j = sum % NrMax;
	/*j devine pozitia*/
	return j;
}
/*functia valid_pin verifica daca PIN-ul 
		este format doar din cifre*/
int valid_pin(char PIN[10])
{
	int i,nr = 0;
	for ( i = 0; i < strlen(PIN); ++i) 
	{
		if (('0' <= PIN[i]) && (PIN[i] <= '9'))
			nr++;
		/*nr numara cate cifre se afla 
			in vectorul atribuit PIN-ului*/
	}
	if (nr == strlen(PIN))
		return 1;
	else
		return 0;
	/*verific daca toate caracterele sunt cifre*/
}
/*alocaLC aloca o celula de tip LC si 
		seteaza campurile pe NULL*/
TLLC alocaLC()
{
	TLLC aux = (TLLC) malloc(sizeof(TLC));
	if (!aux)
		return NULL;
	aux->subset = NULL;
	aux->urmLC = NULL;
	return aux;
}
/*alocarecard aloca un camp din LSC si seteaza
		 campurile din structura cardului*/
TLSC alocarecard(unsigned long long NrCard, char pin[10], char dataexp[10],
	char CVV[5],char status[20],unsigned long  balance,int wrong,TH history)
{
	TLSC aux;
	aux = (TLSC) malloc(sizeof(LSC));
	if (!aux)
		return NULL;
	aux->infocard = (Tcard) malloc(sizeof(card));
	if (!aux->infocard) 
	{
		free(aux);
		return NULL;
	}
	/*se seteaza campurile structurii card*/
	aux->infocard->nrCard = NrCard;
	strcpy(aux->infocard->pin, pin);
	strcpy(aux->infocard->lastpin, pin);
	strcpy(aux->infocard->dataexp, dataexp);
	strcpy(aux->infocard->CVV, CVV);
	strcpy(aux->infocard->status, status);
	aux->infocard->balance = balance;
	aux->infocard->wrong = wrong;
	aux->infocard->Hy = history;
	aux->urmcard = NULL;
	return aux;
}
/*aloca o celula de istoric*/
TH alochistory(char info[1000])
{
	TH aux = (TH) malloc(sizeof(History));
	if (!aux)
		return NULL;
	strcpy(aux->info, info);
	/*se copiaza informatia*/
	aux->urmhy = NULL;
	return aux;
}
/*se face inserare la inceput pentru istoric*/
int inshy(TH * L, char info[1000])
{
	TH aux;
	aux = alochistory(info);
	if (!aux)
		return 0;
	aux->urmhy = *L;
	*L = aux;
	return 1;
}
/*se face inserarea la 
	inceput pentru o celula LC*/

int InsInc(TLLC * L)
{
	TLLC aux;
	aux = alocaLC();
	if (!aux)
		return 0;
	aux->urmLC = *L;
	*L = aux;
	return 1;
}

void showcard(TLLC L, unsigned long long nrCard, FILE * f)
{
	int i = -1;
	TLLC aux;
	TLSC aux2;
	TH aux3;
	for (aux = L; aux != NULL; aux = aux->urmLC) /*parcurgere LC*/
	{
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
		 /*parcurgere LSC*/
		{
			i++;
			if (aux2->infocard->nrCard == nrCard) /*identificare card*/
			{
				/*printare campuri*/
				fprintf(f, "(card number: %016llu, ",
					aux2->infocard->nrCard);
				fprintf(f, "PIN: %s, ", aux2->infocard->pin);
				fprintf(f, "expiry date: %s, ",
					aux2->infocard->dataexp);
				fprintf(f, "CVV: %s, ", aux2->infocard->CVV);
				fprintf(f, "balance: %lu, ",
					aux2->infocard->balance);
				fprintf(f, "status: %s, ",
					aux2->infocard->status);
				if (aux2->infocard->Hy == NULL)
					fprintf(f, "history: []");
				else 
				{ /*printare istoric*/
					fprintf(f, "history: [");
					for (aux3 = aux2->infocard->Hy;
					     aux3 != NULL; aux3 = aux3->urmhy) 
					{
						if (aux3->urmhy == NULL)
							fprintf(f, "(%s)]",
								aux3->info);
						else
							fprintf(f, "(%s), ",
								aux3->info);
					}
				}
				fprintf(f, ")\n");
			}

		}
	}
}

void show(TLLC L, FILE * f, int max)
{
	int i = -1;
	/*i este un contor ce numara pozitia*/
	TLLC aux;
	TLSC aux2;
	TH aux3;
	/*parcurgere LC*/
	for (aux = L; aux != NULL && max != -1; aux = aux->urmLC) 
	{
		i++;
		if (aux->subset == NULL) 
		{
			fprintf(f, "pos%d: []\n", i);

		} 
		else 
		{
			/*parcurgere LSC*/
			fprintf(f, "pos%d: [\n", i);
			for (aux2 = aux->subset; aux2 != NULL;
			     aux2 = aux2->urmcard) 
			{
				fprintf(f, "(card number: %016llu, ",
					aux2->infocard->nrCard);
				fprintf(f, "PIN: %s, ", aux2->infocard->pin);
				fprintf(f, "expiry date: %s, ",
					aux2->infocard->dataexp);
				fprintf(f, "CVV: %s, ", aux2->infocard->CVV);
				fprintf(f, "balance: %lu, ",
					aux2->infocard->balance);
				fprintf(f, "status: %s, ",
					aux2->infocard->status);
				if (aux2->infocard->Hy == NULL)
					fprintf(f, "history: []");
				else 
				{
					fprintf(f, "history: [");
					for (aux3 = aux2->infocard->Hy;
					     aux3 != NULL; aux3 = aux3->urmhy) 
					{
						if (aux3->urmhy == NULL)
							fprintf(f, "(%s)]",
								aux3->info);
						else
							fprintf(f, "(%s), ",
								aux3->info);
					}
				}

				fprintf(f, ")\n");
			}
			fprintf(f, "]\n");
		}
		max--;
		/*max retine pozitia maxima unde exista un card*/

	}
}
/*functia exist verifica daca exista un anumit card in lista*/

int exist(TLSC L, unsigned long long NrCard)
{

	TLSC aux;
	if (L != NULL) 
	{
		/*parcurgere LC*/
		for (aux = L; aux != NULL; aux = aux->urmcard)
			if (aux->infocard->nrCard == NrCard)
				return 1;
	}
	return 0;
}
/*functia de addcard face inserarea la inceput a unui card*/
int add_card(TLSC * L,unsigned long long NrCard, char pin[10], char dataexp[10],
	char CVV[5],char status[20],unsigned long  balance,int wrong,TH history)
{
	if (exist(*L, NrCard) == 0) 
	{
		TLSC aux;
		aux = alocarecard(NrCard, pin, dataexp, CVV,status,balance,wrong,
							history);
		if (!aux)
			return 0;
		aux->urmcard = *L;
		*L = aux;
		return 1;
	} 
	else {					

		return -1;
	}
}
/*se elimina un card*/

int delete_card(TLSC * L, unsigned long long NrCard)
{
	TLSC ant, p;
	for (p = *L, ant = NULL; p != NULL; ant = p, p = p->urmcard)
		if (p->infocard->nrCard == NrCard)/*identificare card*/
			break;
	if (p == NULL)
		return 0;
	if (ant == NULL)
		*L = p->urmcard;
	else
		ant->urmcard = p->urmcard;
		/*refacere legaturi*/
	free(p);
	return 1;
}

void insert_card(unsigned long long NrCard, char PIN[10], TLLC * L, FILE * f,
					int inserare)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)/*parcurgere LC*/
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
		/*parcurgere LSC*/
			if (aux2->infocard->nrCard == NrCard)
			{
				/*verificare status*/
				if(strcmp(aux2->infocard->status,"LOCKED")==0)
				{
					fprintf(f,
					"The card is blocked. Please contact the administrator.\n");
			/*trece in info informatia ce urmeaza sa fie adaugata in istoric*/
							sprintf(info,
							"FAIL, insert_card %016llu %s",
							NrCard, PIN);
			/*se adauga o noua informatie in istoric prin inserare la inceput*/
						inshy(&aux2->infocard->Hy,
						      info);
						return;
				}
				/*daca pinul introdus este diferit de pinul cardului:*/
				if(strcmp(aux2->infocard->pin,PIN)!=0)
				{
					fprintf(f,"Invalid PIN\n");/*afisare eroare*/
						(aux2->infocard->wrong)++;
					if(aux2->infocard->wrong==3)
					{	/*daca pinul a fost gresit de 3 ori cardul este blocat*/
						fprintf(f, 
				"The card is blocked. Please contact the administrator.\n" );
						strcpy(aux2->infocard->status,"LOCKED");
					}
						sprintf(info,
							"FAIL, insert_card %016llu %s",
							NrCard, PIN);
						inshy(&aux2->infocard->Hy,
						      info);
					}
				else
				{
					if(strcmp(aux2->infocard->lastpin,aux2->infocard->pin)==0)
					{
				/*daca pinul nu a fost schimbat niciodata se afiseaza un mesaj*/	
						if(strcmp(aux2->infocard->status,"NEW")==0)
						fprintf(f,"You must change your PIN.\n");
					}
					sprintf(info,"SUCCESS, insert_card %016llu %s",
							NrCard, PIN);
					inshy(&aux2->infocard->Hy,
						      info);
							aux2->infocard->wrong=0;
					}
			}
}

void cancel(unsigned long long NrCard, TLLC * L)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
			if (aux2->infocard->nrCard == NrCard) 
			{
				sprintf(info, "SUCCESS, cancel %016llu", NrCard);
				inshy(&aux2->infocard->Hy, info);
				/*adaugare in istoric operatie*/

			}
}

void unblock_card(unsigned long long NrCard, TLLC * L)
{
	TLLC aux;
	TLSC aux2;
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
			if (aux2->infocard->nrCard == NrCard) 
			{
				/*se seteaza statusul pe activ si se reseteaza nr de greseli*/
				strcpy(aux2->infocard->status, "ACTIVE");
				aux2->infocard->wrong=0;
			}
}


void pin_change(unsigned long long NrCard, TLLC * L, char PIN[10], int ok,
		FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard) 
		{

			if (aux2->infocard->nrCard == NrCard) 
			{
				if (ok == 1) 
				{
					strcpy(aux2->infocard->lastpin,
					       aux2->infocard->pin);
					strcpy(aux2->infocard->pin, PIN);

					strcpy(aux2->infocard->status,
					       "ACTIVE");
					sprintf(info,
						"SUCCESS, pin_change %016llu %s",
						NrCard, PIN);
					inshy(&aux2->infocard->Hy, info);
				} 
				else 
				{
					fprintf(f, "Invalid PIN\n");
					sprintf(info,
						"FAIL, pin_change %016llu %s",
						NrCard, PIN);
					inshy(&aux2->infocard->Hy, info);

				}
				
	/*in cazul in care reuseste schimbarea PIN-ului se actualizeaza statusul*/
			}
		}
}

void balance_inquiry(unsigned long long NrCard, TLLC * L, FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
			if (aux2->infocard->nrCard == NrCard) {
				fprintf(f, "%lu\n", aux2->infocard->balance);
				sprintf(info, "SUCCESS, balance_inquiry %016llu",
					NrCard);
				inshy(&aux2->infocard->Hy, info);
			}

}

void recharge(unsigned long long NrCard, TLLC * L, unsigned long SUM, FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
			if (aux2->infocard->nrCard == NrCard) 
			{
				if (SUM % 10 == 0) /*verific multiplu de 10*/
				{

					aux2->infocard->balance =
					    aux2->infocard->balance + SUM;
					sprintf(info,
						"SUCCESS, recharge %016llu %lu",
						NrCard, SUM);
					inshy(&aux2->infocard->Hy, info);
					fprintf(f, "%lu\n",
						aux2->infocard->balance);

				} 
				else 
				{
					fprintf(f, "%s\n",
						"The added amount must be multiple of 10");
					sprintf(info, "FAIL, recharge %016llu %lu",
						NrCard, SUM);
					inshy(&aux2->infocard->Hy, info);
				}
			}
}

void cash_withdrawal(unsigned long long NrCard, TLLC * L, unsigned long SUM,
		     FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard)
			if (aux2->infocard->nrCard == NrCard) 
			{
				if (SUM % 10 == 0) 
				{
					if (SUM > aux2->infocard->balance) 
			/*verificare daca exista suficienti bani pt a efectua tranzactia*/
					{
						fprintf(f,
							"Insufficient funds\n");
						sprintf(info,
							"FAIL, cash_withdrawal %016llu %lu",
							NrCard, SUM);
						inshy(&aux2->infocard->Hy,
						      info);
					} 
					else 
					{
						aux2->infocard->balance =
						    aux2->infocard->balance -
						    SUM;
						fprintf(f, "%lu\n",
							aux2->infocard->
							balance);
						sprintf(info,
							"SUCCESS, cash_withdrawal %016llu %lu",
							NrCard, SUM);
						inshy(&aux2->infocard->Hy,
						      info);
					}

				} 
				else 
				{
					fprintf(f, "%s\n",
						"The requested amount must be multiple of 10");
					sprintf(info,
						"FAIL, cash_withdrawal %016llu %lu",
						NrCard, SUM);
					inshy(&aux2->infocard->Hy, info);
				}
			}
}

void transfer_funds(unsigned long long NrCardSource,
		    unsigned long long NrCardDest, TLLC * L, unsigned long SUM,
		    FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	int ok = 0;
	/*verificare exista bani suficienti*/
	for (aux = *L; aux != NULL; aux = aux->urmLC) 
	{
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard) 
		{
			if (aux2->infocard->nrCard == NrCardSource) 
			{
				if (aux2->infocard->balance >= SUM)
					ok = 1;
			}
		}
	}

	for (aux = *L; aux != NULL; aux = aux->urmLC)
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard) 
		{
			if (aux2->infocard->nrCard == NrCardSource) 
			{
				if (SUM % 10 == 0) /*verificare suma sa fie multiplu de 10*/
				{
					if (SUM <= aux2->infocard->balance) /*verificare sold*/
					{
						aux2->infocard->balance =
						    aux2->infocard->balance -
						    SUM;
						fprintf(f, "%lu\n",
							aux2->infocard->
							balance);
						sprintf(info,
							"SUCCESS, transfer_funds %016llu %016llu %lu",
							NrCardSource,
							NrCardDest, SUM);
						inshy(&aux2->infocard->Hy,
						      info);

					} 
					else 
					{
						fprintf(f,
							"Insufficient funds\n");
						sprintf(info,
							"FAIL, transfer_funds %016llu %016llu %lu",
							NrCardSource,
							NrCardDest, SUM);
						inshy(&aux2->infocard->Hy,
						      info);

					}
				} 
				else 
				{
					ok = 0;
					fprintf(f, "%s\n",
						"The transferred amount must be multiple of 10");
					sprintf(info,
						"FAIL, transfer_funds %016llu %016llu %lu",
						NrCardSource, NrCardDest, SUM);
					inshy(&aux2->infocard->Hy, info);

				}
			}
			if (aux2->infocard->nrCard == NrCardDest) 
			{
				if (ok == 1) 
				{
					aux2->infocard->balance =
					    aux2->infocard->balance + SUM;
					sprintf(info,
						"SUCCESS, transfer_funds %016llu %016llu %lu",
						NrCardSource, NrCardDest, SUM);
					inshy(&aux2->infocard->Hy, info);
				}

			}
		}
}

int elimina_history(TH * L, char info[1000])
{
	TH ant, p;
	for (p = *L, ant = NULL; p != NULL; ant = p, p = p->urmhy)
		if (strcmp(p->info, info) == 0)
			break;
	if (p == NULL)
		return 0;
	if (ant == NULL)
		*L = p->urmhy;
	else
		ant->urmhy = p->urmhy;/*refacere legaturi*/
	free(p);
	return 1;
}

void reverse_transaction(unsigned long long NrCardSource,
			 unsigned long long NrCardDest, TLLC * L,
			 unsigned long SUM, FILE * f)
{
	TLLC aux;
	TLSC aux2;
	char info[1000];
	char removeinfo[1000];
	int ok = 0;
	/*verificare sold suficient pentru a realiza tranzactia*/
	for (aux = *L; aux != NULL; aux = aux->urmLC) 
	{
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard) 
		{
			if (aux2->infocard->nrCard == NrCardDest) 
			{
				if (aux2->infocard->balance >= SUM)
					ok = 1;
			}
		}
	}

	for (aux = *L; aux != NULL; aux = aux->urmLC) 
	{
		for (aux2 = aux->subset; aux2 != NULL; aux2 = aux2->urmcard) 
		{
			if (aux2->infocard->nrCard == NrCardSource) 
			{
				if (ok == 1) 
				{
					aux2->infocard->balance =
					    aux2->infocard->balance + SUM;
					sprintf(info,
						"SUCCESS, reverse_transaction %016llu %016llu %lu",
						NrCardSource, NrCardDest, SUM);
					inshy(&aux2->infocard->Hy, info);

				}
			}

			if (aux2->infocard->nrCard == NrCardDest) 
			{
				if (ok == 1) {
					aux2->infocard->balance =
					    aux2->infocard->balance - SUM;
					sprintf(removeinfo,
						"SUCCESS, transfer_funds %016llu %016llu %lu",
						NrCardSource, NrCardDest, SUM);

					elimina_history(&aux2->infocard->Hy,
							removeinfo);

				}

				else 
				{
					fprintf(f,
						"The transaction cannot be reversed\n");
				}

			}

		}
	}

}

void distrugerehist(TH * H)
{
	TH aux;
	while (*H) 
	{
		aux = *H;
		*H = aux->urmhy;
		free(aux);
	}
}

void distrugereLSC(ALSC L)
{
	TLSC aux;
	while (*L) 
	{
		aux = *L;
		*L = aux->urmcard;
		distrugerehist(&aux->infocard->Hy);
		free(aux->infocard);
		free(aux);
	}
}

void distrugereLC(TLLC * L)
{
	TLLC aux;
	while (*L) 
	{
		aux = *L;
		*L = aux->urmLC;
		distrugereLSC(&aux->subset);
		free(aux);
	}
}