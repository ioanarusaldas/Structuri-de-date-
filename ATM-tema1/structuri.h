#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct history
{ char info[1000];
  struct history * urmhy;
} History,*TH,**ALH;

typedef struct card
{ 
	unsigned long long nrCard;
	char pin[10];
	char lastpin[10];
	char dataexp[10];
	char CVV[5];
	unsigned long balance;
	char status[20];
	int wrong;
	History * Hy;
}  card,*Tcard;


typedef struct LSC
{ card * infocard;
  struct LSC * urmcard;
} LSC,*TLSC,**ALSC;

typedef struct LC   
{ LSC * subset;
  struct LC * urmLC;
} TLC,*TLLC;
