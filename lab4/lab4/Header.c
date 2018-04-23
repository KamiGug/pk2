#include "Header.h"

void InicjalizujBuffor(buffor** tak)
{
	*tak = malloc(sizeof(buffor));
	(*tak)->czytany = 0;
	(*tak)->zapisywany = 0;
}

void DodajDoBuffora(buffor* tak, stany uzytkownika, bool wyjscie)
{
	tak->stan[tak->zapisywany] = uzytkownika;
	tak->wyjscie[tak->czytany] = wyjscie;
	tak->zapisywany = (tak->zapisywany + 1) % wielkoscbuffora;
}

void CzytajZBuffora(buffor* tak, FILE* plik)
{
	

	printf("Stan uzytkownika: ");
	if (plik != NULL)
	{
		fprintf_s(plik, "Stan uzytkownika: ");
	}
	switch (tak->stan[tak->czytany])
	{
	case nasluch:
		printf("nasluch");
		if (plik != NULL) fprintf_s(plik, "nasluch");
		break;

	case polaczenie:
		printf("polaczenie");
		if (plik != NULL) fprintf_s(plik, "polaczenie");
		break;

	case oczekiwanie:
		printf("oczekiwanie");
		if (plik != NULL) fprintf_s(plik, "oczekiwanie");
		break;

	case zajety:
		printf("zajety, wyjscie: %d", tak->wyjscie[tak->czytany]);
		if (plik != NULL) fprintf_s(plik, "zajety, wyjscie: %d", tak->wyjscie[tak->czytany]);
		break;

	case wolny:
		printf("wolny");
		if (plik != NULL) fprintf_s(plik, "wolny");
		break;
	}
	printf("\n");
	if (plik != NULL) fprintf_s(plik, "\n");
	tak->czytany = (tak->czytany + 1) % wielkoscbuffora;
}

void Dzialaj(stany* uzytkownik, bool wejscie, bool wyjscie, buffor* buff)
{
	switch (*uzytkownik)
	{
	case nasluch:
		if (wejscie)
		{
			*uzytkownik = polaczenie;
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		else
		{
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		break;


	case polaczenie:
		if (wejscie)
		{
			*uzytkownik = oczekiwanie;
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		else
		{
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		break;

	case oczekiwanie:
		if (wejscie)
		{
			*uzytkownik = wolny;
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		else
		{
			*uzytkownik = nasluch;
			DodajDoBuffora(buff, *uzytkownik,0);
		}
		break;

	case zajety:
		if (wejscie)
		{
			DodajDoBuffora(buff, *uzytkownik, wyjscie);
		}
		else
		{
			*uzytkownik = nasluch;
			DodajDoBuffora(buff, *uzytkownik, wyjscie);
		}
		break;

	case wolny:
		if (wejscie)
		{
			*uzytkownik = zajety;
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		else
		{
			*uzytkownik = nasluch;
			DodajDoBuffora(buff, *uzytkownik, 0);
		}
		break;
	}
}