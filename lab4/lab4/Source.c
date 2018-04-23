#include "Header.h"


int main()
{
	char* zapis[300];
	printf("Podaj lokalizacje zapisu: ");
	scanf_s("%s", zapis, 300);
	FILE* plik;
	fopen_s(&plik, zapis, "w");
	if (plik == NULL) return;
	buffor* buff;
	InicjalizujBuffor(&buff);
	stany uzytkownik = nasluch;
	bool wyjscie;

	for (int i = 0; i < wielkoscbuffora/5; i++)
	{
		wyjscie = rand() % 2;
		Dzialaj(&uzytkownik, rand() % 2, wyjscie, buff);
	}

	for (int i = 0; i < 4; i++)
	{
		wyjscie = rand() % 2;
		Dzialaj(&uzytkownik, 1, wyjscie, buff);
		CzytajZBuffora(buff, plik);
	}

	for (int i = 0; i < 50; i++)
	{
		wyjscie = rand() % 2;
		Dzialaj(&uzytkownik, 1, wyjscie, buff);
		CzytajZBuffora(buff, plik);
	}

	for (int i = 0; i < wielkoscbuffora*4; i++)
	{
		wyjscie = rand() % 2;
		Dzialaj(&uzytkownik, rand() % 2, wyjscie, buff);
		CzytajZBuffora(buff, plik);
	}

	for (int i = 0; i < wielkoscbuffora / 5; i++)
	{
		CzytajZBuffora(buff, plik);
	}

	free(buff);
	if (plik != NULL) fclose(plik);
	return 0;
}