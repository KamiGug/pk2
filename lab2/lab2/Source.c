#include "header.h"

int main()
{
	int x, y;
	printf("podaj dlugosc tablicy: ");
	scanf_s("%d", &x);
	printf("podaj szerokosc tablicy: ");
	scanf_s("%d", &y);
	printf("podaj nazwe pliku do ktorego chcesz zapisac: ");
	char nazwa[100];
	scanf_s("%s", nazwa, 100);
	ZliczanieElementow(x, y, nazwa);

	return 0;
}