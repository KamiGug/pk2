#pragma once
#include <stdio.h>
#include <stdlib.h>

#define JakDuzyStos 500

typedef enum { false, true } bool;

struct ElementStosu
{
	int liczba;
	struct ElementStosu* poprzedni;
};

struct TaggedFizyczne
{
	union Fizyczne
	{
		float GodzinaLubMinuta;
		int Sekunda;
	};
	enum { Godzina, Minuta, Sekunda } fizyka;
};

void Pierwsze(const char* plik);
void Drugie(const char* plik);
void Trzecie(void);

void ZliczanieElementow(int x, int y, const char* nazwa);
void start(void); 
void NaLiscie(const char* plik);
void NaTablicy(const char* plik);
void DodajDoListy(struct ElementStosu** head, int liczba);
void UsunListe(struct ElementStosu** head);
double SredniaZListy(struct ElementStosu** head);
void WypiszLista(struct ElementStosu** head, const char* NazwaPliku);
double SredniaTablica(int* stos, int OstatniNaStosie);
void WypiszTablica(int* stos, int OstatniNaStosie, const char* NazwaPliku);
void Ustalenie(struct TaggedFizyczne* nazwa);
void Przeliczanie(struct TaggedFizyczne* nazwa, char NaCo);
void Dodawanie(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos);
void Odejmowanie(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos);
void Wyswietl(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos);