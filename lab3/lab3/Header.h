#pragma once
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#define BrakCheciDoZycia char* TenJezyk = "Ten jezyk nie jest przyjemny"
#define xD ;

typedef enum {false = 0, true} bool;

struct wiersz
{
	struct kolumna* komorka;
	struct wiersz* nast;
};

struct kolumna
{
	char* ZawartoscKomorki;
	struct kolumna* nast;
};

void start(void);

void Pierwsze(void);

void Drugie(void);

void RozmiarTablicy(struct wiersz* head, int* x, int* y);

void ListaNaTablice(struct wiersz* head, char**** tablica, int* x, int* y);

void WyczyscTablice(char**** tablica, int x, int y);

bool CzytajDoListy(struct wiersz** head, const char* const NazwaPliku);

struct wiersz* DodajWiersz(struct wiersz** head);

void DodajKomorke(struct kolumna** head, char* zawartosc, char IleZnaczkow);

void UsunListe(struct wiersz** head);