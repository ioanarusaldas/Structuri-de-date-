//Savu Ioana Rusalda
	//315 CB
#include <stdio.h>
#include <string.h>
#include "structuri.h"
#include "functii.c"
#include "comenzi.c"

int main()
{
	FILE *out;
	out = fopen("output.out", "w");
	FILE *input;
	input = fopen("input.in", "r");
	FILE *error;
	error = fopen("error.out", "w");
	if (input == NULL) {
		fprintf(stderr, "ERROR: Can't open file %s\n", "input.txt");
		return -1;
	}
	//deschidere si verificare rezultat functie fopen
	int nrOperatii, i;
	char op[10], cale[100] = "\0", aux[50], str[50], caleaux[100] = "\0";
	Trie arb = alocare('-');
	//alocare arbore
	Trie arbAux;
	cale[0] = '/';
	fscanf(input, "%d", &nrOperatii);
	while (fscanf(input, "%s", op) != EOF) {//citire operatii si apelare functie
												//corespunzatoare
		if (strcmp(op, "mkdir") == 0) {
			fscanf(input, "%[^\n]", str);
			mkdir(str, &arb);
			arbAux = arb;//actualizare arbore auxiliar
		}
		if (strcmp(op, "cd") == 0) {

			fscanf(input, "%s", aux);
			strcpy(str, aux);
			if (str[0] == '.') {

				arbAux = cdPunct(arbAux, str, cale);//pozitionare in arbore 
													//conform comenzii cd
				if (arbAux == NULL) {
					fprintf(error,
						"%s: No such file or directory\n",
						aux);
					arbAux = arb;
				}

			} else {
				arbAux = cd(arbAux, str, cale);
				if (arbAux == NULL) {
					fprintf(error,
						"%s: No such file or directory\n",
						aux);
				} else {
					if (str[0] == '/')
						for (i = 0; i < strlen(aux);
						     i++)

							aux[i] = aux[i + 1];
					for (i = 0; i < strlen(aux); i++) {
						caleaux[i] = aux[i];
					}

					strcat(cale, caleaux);
				}

			}
		}

		if (strcmp(op, "ls") == 0) {
			if (arbAux == NULL)//verificare arbore NULL
				fprintf(out, "\n");
		}
		if (strcmp(op, "pwd") == 0) {//afisare cale catre director curent
			for (i = 0; i < strlen(cale); i++)
				fprintf(out, "%c", cale[i]);
			fprintf(out, "\n");

		}

	}
	DistrArb(&arb);
	fclose(out);
	fclose(input);
	fclose(error);
	return 0;
}
