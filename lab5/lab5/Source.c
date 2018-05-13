#include "Header.h"

int main()
{
	buffor* buff = malloc(sizeof(buffor));
	buff->czytany = 0;
	buff->zapisywany = 0;
	char* ToBeTested;
	char* tested;
	int test;

	ToBeTested = "CDXLIX";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "IX";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "XI";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "MMMCMXXI";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "MCII";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "MMCDIX";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "AHA";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	ToBeTested = "MMMCMXXI";
	printf("%s: %d\n", ToBeTested, RomToDec(ToBeTested, strlen(ToBeTested)));

	test = 16;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 1234;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 3290;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 509;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 3888;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 0;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 3999;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 14;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 4;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 3444;
	ToBeTested = DecToRom(test);
	printf("%d: %s\n", test, ToBeTested);
	free(ToBeTested);

	test = 250;
	ToBeTested = "Tu znajduje sie 250!";
	printf("Szukane: %d, w: \"%s\". Znaleziono poczatek na znaku: %d\n", test, ToBeTested, FindDec(ToBeTested, test));

	test = 2314;
	ToBeTested = "2314";
	printf("Szukane: %d, w: \"%s\". Znaleziono poczatek na znaku: %d\n", test, ToBeTested, FindDec(ToBeTested, test));

	test = 420;
	ToBeTested = "420 ahdfkfhsdkj";
	printf("Szukane: %d, w: \"%s\". Znaleziono poczatek na znaku: %d\n", test, ToBeTested, FindDec(ToBeTested, test));

	test = 1243;
	ToBeTested = "According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway because 1243s don't care what humans think is impossible. ";
	printf("Szukane: %d, w: \"%s\". Znaleziono poczatek na znaku: %d\n", test, ToBeTested, FindDec(ToBeTested, test));
	
	test = 13;
	ToBeTested = DecToRom(test);
	tested = "According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its XIII little body off the ground. The bee, of course, flies anyway because bees don't care what humans think is impossible. ";
	printf("Szukane: %d, w: \"%s\". Znaleziono poczatek na znaku: %d\n", test, tested, FindRom(tested, ToBeTested));
	free(ToBeTested);

	char Nazwa[250];
	printf("Podaj Nazwe pliku: ");
	scanf_s("%s", Nazwa, 250);
	Szukaj* name = Szukaj_W_Pliku(Nazwa);

	if (name == NULL)
	{
		printf("\nNie znaleziono liczby");
	}
	else
	{
		printf("Znaleziono liczbe %s(%d), w %d. slowie, ktora zaczyna sie od %d. znaku tego slowa.", name->ZnalezionaLiczba, RomToDec(name->ZnalezionaLiczba, strlen(name->ZnalezionaLiczba)), name->KtoreSlowo, name->poczatek);
	}
	
	free(name);
	free(buff);
	return 0;
}