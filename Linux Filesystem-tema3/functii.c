//Savu Ioana Rusalda
	//315 CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Trie alocare(char tip)
{
	int i;
	Trie nod = (Trie) malloc(sizeof(Tnod_trie));//alocare nod
	if (!nod)
		return NULL;
	nod->tip = tip;
	for (i = 0; i <= 37; i++)
		nod->copii[i] = NULL;//initializare nod
	return nod;
}

int insert(Trie * arb, char *str, char tip)
{

	int index = 0;
	Trie arbAux = *arb;
	while (*str) {//convert caracter in index conform codului ascii
		if (*str >= '.' && *str <= '9')
			index = *str - '.' + 26;
		else if (*str >= 'a' && *str <= 'z')
			index = *str - 'a';
		else
			return 0;
		if (arbAux->copii[index] == NULL) {
			arbAux->copii[index] = alocare('-');//alocare nod
		}
		if (!arbAux->copii[index])
			return 0;

		arbAux = arbAux->copii[index];

		str++;
	}
	arbAux->tip = tip;//setare sfarsit de cuvant
	return 1;

}

void distruge(Trie arb)
{
	int i;
	if (!arb)
		return;
	for (i = 0; i <= 36; i++)
		distruge((arb)->copii[i]);//distrugere nod
	free(arb);
}

void DistrArb(Trie * arb)
{
	if (!(*arb))
		return;
	distruge(*arb);
	*arb = NULL;
}

int Cauta(Trie arb, char *str)
{

	if (arb == NULL)
		return 0;

	Trie arbAux = arb;
	while (*str) {//cautare caracter din cuvant

		arbAux = arbAux->copii[*str - 'a'];

		if (arbAux == NULL)
			return 0;

		str++;
	}

	if (arbAux->tip == '/')//verificare sfarsit de cuvant
		return 1;
	return 0;
}

void pwd(Trie arb)
{
	int i;
	if (!arb)
		return;
	for (i = 0; i <= 36; i++) {
		if (arb->copii[i] != NULL)
			printf("%c", (i + ('a' - '0')) + '0');//convert int in char
		pwd(arb->copii[i]);
	}

}

int verificare(char str[10])
{

	int i = 0;
	while (str[i]) {
		if (str[i] != '.') {//verificare punct
			if (str[i] < '0' || str[i] > '9')//verifcare cifre
				if (str[i] < 'A' || str[i] > 'z')//verificare litere
					return 0;
		}
		i++;
	}
	return 1;
}

Trie Cauta2(Trie arb, char *str)
{

	if (arb == NULL)
		return NULL;

	Trie arbAux = arb;
	while (*str) {

		arbAux = arbAux->copii[*str - 'a'];

		if (arbAux == NULL)
			return NULL;

		str++;
	}

	if (arbAux->tip == '/')//verificare sfarsit cuvant
		return arbAux;
	return NULL;
}

char caracter(int x)
{
	//transformare conform cod ascii
	if (x >= 0 && x <= 25)
		return x + 'a';
	else if (x >= 48 && x <= 57)
		return x + '.' - 26;
	return '-';

}
