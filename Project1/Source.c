#include <stdio.h>

int znajdz(int* tab, int a)
{
	for (int i = 0;i < 20; i++)
	{
		if (tab[i]%a == 0) return i;
	}
	return -1;
}

int main()
{
	int tab[20];
	for (int i = 0; i < 20; i++)
	{
		printf("Podaj %d. liczbe: ", i + 1);
		scanf_s("%d", &tab[i]);
	}
	for (int i = 0; i < 20;i++)
	{
		printf("\nliczba %d.: %d", i+1, tab[i]);
	}
	int i;
	printf("\nszukane: ");
	scanf_s("%d", &i);
	printf("Szukany indeks: %d", znajdz(tab, i));
	return 0;
}