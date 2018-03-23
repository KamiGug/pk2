#include "header.h"

void ZliczanieElementow(int x, int y, char* nazwa)
{
	bool** tablica = malloc(y * sizeof(bool*));
	for (int i = 0; i < y; i++)
	{
		tablica[i] = malloc(x * sizeof(bool));
	}
	char a;
	scanf_s("%c", &a);
	for (int j = 0; j < y; j++)
	{
		for (int i = 0; i < x; i++)
		{

			scanf_s("%c", &a);
			if (a - '0' == 0 || a - '1' == 0)
			{
				tablica[i][j] = a - '0';
			}
			else
			{
				printf("\nNiepoprawne dane.");
				return;
			}
		}
	}
	int LiczbaJedynek = 0, LiczbaZer = 0;
	for (int j = 0; j < y; j++)
	{
		for (int i = 0; i < x; i++)
		{
			if (tablica[i][j] == false) LiczbaZer++;
			else LiczbaJedynek++;
		}
	}
	FILE* plik;
	fopen_s(&plik, nazwa, "w");
	if (plik == NULL)
	{
		printf("Nie mozna zapisac w tym pliku.");
	}
	else
	{
		printf(plik, "Liczba jedynek: %d\nLiczba zer: %d\n", LiczbaJedynek, LiczbaZer);
		if (LiczbaZer < LiczbaJedynek)
		{
			printf(plik, "WJ");
			printf("WJ");
		}
		else
		{
			if (LiczbaZer == LiczbaJedynek)
			{
				printf(plik, "EQ");
				printf("EQ");
			}
			else
			{
				printf(plik, "WZ");
				printf("WZ");
			}
		}
		fclose(plik);
	}
	/*for (int i = 0; i < y; i++)
	{
		free(tablica[i]);
	}*/
	free(tablica);
}