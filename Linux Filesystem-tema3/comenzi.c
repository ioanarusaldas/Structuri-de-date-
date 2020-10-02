//Savu Ioana Rusalda
	//315 CB
#include <stdio.h>
#include <string.h>

void mkdir(char str[50], Trie * arb)
{
	char *p;
	char director[50];
	int i, n;
	p = strtok(str, " ");//despartire sir dupa spatiu
	while (p != NULL) {
		strcpy(director, p);
		if (director[0] == '/')//verificare pozitionare in root
			for (i = 0; i < strlen(director); i++)
				director[i] = director[i + 1];
		n = insert(arb, director, '/');
		if (n == 0)//verificare succes inserare
			fprintf(stderr, "ERROR: Can't create director\n");
		p = strtok(NULL, " ");
	}
}

Trie cdPunct(Trie arb, char str[100], char cale[100])
{
	char s[100], back[10], director[10];
	char *p, *p2;
	int i;
	strcpy(s, str);
	Trie arbAux = arb;
	if (strchr(s, '/') == NULL) {//verificare sir contine /

		if (strcmp(cale, "/") == 0)//verificare pozitionare in root
			return arbAux;
		else {
			if (strlen(str) == 2 && str[1] == '.') {//verificare argument
															//cd=".."
				for (i = strlen(cale); i >= 0; i--) {
					if (cale[i] == '/')
						cale[i + 1] = '\0';//eliminare  director curent din cale
				}
				if (strcmp(cale, "/") != 0) {
					p = strtok(str, "/");//impartire dupa /
					while (p != NULL) {
						strcpy(back, p);
						p = strtok(NULL, "/");
					}
					//cautare cuvant si pozitionare in arbore
					arbAux = Cauta2(arbAux, back);
					return arbAux;
				} else
					return NULL;

			}
		}

	} else {
		p2 = strtok(str, "/");//impartire dupa /
		while (p2 != NULL) {
			strcpy(director, p2);
			if (strcmp(cale, "/") == 0)
				return arbAux;
			else {
				if (strlen(director) == 2 && director[1] == '.') {
					//verificare ..
					for (i = strlen(cale); i >= 0; i--) {
						if (cale[i] == '/')
							cale[i + 1] = '\0';//actualizare cale
					}
					if (strcmp(cale, "/") != 0) {
						p = strtok(str, "/");//impartire dupa /
						while (p != NULL) {
							strcpy(back, p);
							p = strtok(NULL, "/");
						}
						arbAux = Cauta2(arbAux, back);//cautare cuvant
						return arbAux;
					} else
						return NULL;

				}
			}
			p2 = strtok(NULL, "/");
		}

	}
	return arbAux;

}

Trie cd(Trie arb, char str[100], char cale[100])
{
	char s[100], director[10];
	char *p;
	strcpy(s, str);
	Trie arbAux = arb;
	if (strchr(s, '/') != NULL) {//impartire dupa /
		p = strtok(str, "/");

		while (p != NULL) {
			strcpy(director, p);
			arbAux = Cauta2(arbAux, director);//cautare+pozitionare in arbore
			if (arbAux == NULL) {
				break;
			}
			p = strtok(NULL, "/");
		}
	} else {
		strcpy(director, str);
		arbAux = Cauta2(arbAux, director);

	}
	return arbAux;
}
