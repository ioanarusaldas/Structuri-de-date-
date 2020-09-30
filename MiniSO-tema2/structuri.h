//Savu Ioana Rusalda 
	//315CB
#include<stdio.h>
#include<string.h>
#include <stdlib.h>

typedef struct celulag 
{
	void *info;
	struct celulag *urm;
} TCelulaG, *TLG, **ALG;

typedef struct 
{
	size_t dime;
	TLG ic, sc;
} TCoada, *TC;

typedef struct 
{
	size_t dime;
	TLG vf, b;
} TStiva, *TS;

typedef struct proces 
{
	int PID;
	int prioritate;
	unsigned long timp_exec;
	unsigned long timp_exec1;
	unsigned long long dim;
	int Imem;
	int Smem;
	char stare[10];
	TS st;

} PROC;
