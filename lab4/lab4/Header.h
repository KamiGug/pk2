#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wielkoscbuffora 30

typedef enum { nasluch, polaczenie, oczekiwanie, zajety, wolny }stany;

typedef enum { flase = 0, true } bool;

typedef struct buffer
{
	stany stan[wielkoscbuffora];
	bool wyjscie;
	int czytany;
	int zapisywany;
}buffor;

void InicjalizujBuffor(buffor** tak);

void DodajDoBuffora(buffor* tak, stany uzytkownika, bool wyjscie);

void CzytajZBuffora(buffor* tak, FILE* plik);

void Dzialaj(stany* uzytkownicy, bool wejscie, bool wyjscie, buffor* buff);