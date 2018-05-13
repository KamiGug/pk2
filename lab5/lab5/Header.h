#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SizeOfBuffor 30

typedef struct buffererer
{
	int buffered[SizeOfBuffor];
	int czytany;
	int zapisywany;
}buffor;

typedef struct DoZnalezienia
{
	int KtoreSlowo;
	int poczatek;
	char* ZnalezionaLiczba;
}Szukaj;

char* DecToRom(int liczba);

bool IsOkRoman(char* liczba, int len);

int RomToDec(const char* liczba, int len);

void DoBuffora(buffor* buff, int NumerLoga);

void ZBuffora(buffor* buff, FILE* plik);

int FindDec(char* Ciag, int szukana);

int FindRom(char* Ciag, char* szukana);

Szukaj* Szukaj_W_Pliku(const char* const NazwaPliku);

Szukaj* Find_A_Rom(char* Ciag);