#include <stdio.h>
#include <stdlib.h>

#define tabsize 20

int ZnajdzInaczej(int* tab, int a)
{
	int i = 0;
	while (i < tabsize)
	{
		if (*(tab) % a == 0) return i;
		i++;
		tab++;
	}
	return -1;
}

void ParametryDoProgramu(int* tablica, char** argumenty, int ileich, int size)
{
	int i = 0;
	while (i < size && i < ileich-1)
	{
		tablica[i] = atoi(argumenty[i+1]);
		i++;
	}
	if (i < size)
	{
		for (i; i < size; i++)
		{
			tablica[i] = 0;
		}
	}
}

int znajdz(int* tab, int a)
{
	for (int i = 0;i < tabsize; i++)
	{
		if (tab[i]%a == 0) return i;
	}
	return -1;
}

int main(int argc, char** argv)
{
	int tab[tabsize];
	/*for (int i = 0; i < tabsize; i++)
	{
		printf("Podaj %d. liczbe: ", i + 1);
		scanf_s("%d", &tab[i]);
	}*/
	ParametryDoProgramu(tab, argv, argc, tabsize);
	for (int i = 0; i < 20;i++)
	{
		printf("\nliczba %d.: %d", i+1, tab[i]);
	}
	int i;
	printf("\nszukane: ");
	scanf_s("%d", &i);
	printf("Szukany indeks: %d", ZnajdzInaczej(tab, i));
	return 0;
}