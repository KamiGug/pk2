#include "header.h"

void start(void)
{
	char nazwa[100] = "plik.txt";
	char z;
	do
	{
		printf_s("Wpisz 1, aby zobaczyc pierwsze zadanie.\nWpisz 2, aby zobaczyc drugie zadanie.\nWpisz 3, aby zobaczyc trzecie zadanie.\nWpisz 4, aby zmienic plik docelowy.\nWpisz q, aby wyjsc z programu.\n");
		scanf_s("\n%c", &z);
		switch (z)
		{
		case '1':
			Pierwsze(nazwa);
			break;

		case '2':
			Drugie(nazwa);
			break;

		case '3':
			Trzecie();
			break;

		case '4':
			printf_s("podaj nazwe pliku do ktorego chcesz zapisac: ");
			char nazwa[100];
			scanf_s("\n%s", nazwa, 100);
			FILE* plik;
			fopen_s(&plik, nazwa, "w");
			if (plik == NULL)
			{
				printf_s("Nie mozna tu zapisac.");
				return;
			}
			fclose(plik);
			break;

		case 'q':
		case 'Q':
			printf_s("generic goodbye message.");
			break;

		}
	} while (z != 'q' && z != 'Q');
}

//1.

void Pierwsze(const char* plik)
{
	int x, y;
	printf_s("podaj dlugosc tablicy: ");
	scanf_s("%d", &x);
	printf_s("podaj szerokosc tablicy: ");
	scanf_s("%d", &y);
	ZliczanieElementow(x, y, plik);
}

void ZliczanieElementow(int x, int y, const char* nazwa)
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
			do
			{
				printf_s("%u na %u: ", i + 1, j + 1);
				scanf_s("\n%c", &a);
			} while (a - '0' != 0 && a - '1' != 0);
			tablica[i][j] = a - '0';
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
		printf_s("Nie mozna zapisac w tym pliku.");
	}
	else
	{
		printf_s(plik, "Liczba jedynek: %d\nLiczba zer: %d\n", LiczbaJedynek, LiczbaZer);
		fprintf_s(plik, "Liczba jedynek: %d\nLiczba zer: %d\n", LiczbaJedynek, LiczbaZer);
		if (LiczbaZer < LiczbaJedynek)
		{
			fprintf_s(plik, "WJ");
			printf_s("WJ");
		}
		else
		{
			if (LiczbaZer == LiczbaJedynek)
			{
				fprintf_s(plik, "EQ");
				printf_s("EQ");
			}
			else
			{
				fprintf_s(plik, "WZ");
				printf_s("WZ");
			}
		}
		fclose(plik);
	}
	free(tablica);
}

//2.

void Drugie(const char* plik)
{
	char lista;
	do
	{
		printf_s("Jesli chcesz stos na liscie wpisz 1, jesli nie wpisz 0: ");
		scanf_s("\n%c", &lista);
		switch (lista)
		{
		case '1':
			NaLiscie(plik);
			break;

		case '0':
			NaTablicy(plik);
			break;
		}
	} while (lista != '0' && lista != '1');
}

void NaLiscie(const char* plik)
{

	printf_s("Dodawaj kolejne liczby, az do podania q.\n");
	struct ElementStosu* head = NULL;
	char liczba[10];
	do
	{
		scanf_s("\n%s", liczba, 10);
		DodajDoListy(&head, atoi(liczba));
	} while (liczba[0] != 'q' && liczba[0] != 'Q');
	UsunListe(&head);
	WypiszLista(&head, plik);
	while (head != NULL)
	{
		UsunListe(&head);
	}
}

void DodajDoListy(struct ElementStosu** head, int liczba)
{
	struct ElementStosu* tmp = (*head);
	*head = malloc(sizeof(struct ElementStosu));
	(*head)->liczba = liczba;
	(*head)->poprzedni = tmp;
}

double SredniaZListy(struct ElementStosu** head)
{
	int suma = 0, ile = 0;
	struct ElementStosu* tmp = *head;
	while (tmp != NULL)
	{
		ile++;
		suma += tmp->liczba;
		tmp = tmp->poprzedni;
	}
	double wynik = suma;
	wynik /= ile;
	return wynik;
}

void WypiszLista(struct ElementStosu** head, const char* NazwaPliku)
{
	double srednia = SredniaZListy(head);
	FILE* plik;
	fopen_s(&plik, NazwaPliku, "w");
	if (plik == NULL)
	{
		printf_s("Nie mozna tu zapisac.");
		return;
	}
	fprintf_s(plik, "Liczby: ");
	struct ElementStosu* tmp = *head;
	while (tmp != NULL)
	{
		fprintf_s(plik, "%d ", tmp->liczba);
		tmp = tmp->poprzedni;
	}
	fprintf_s(plik, "\nsrednia: %f ", srednia);
	fclose(plik);
}

void UsunListe(struct ElementStosu** head)
{
	if (*head == NULL) return;
	struct ElementStosu* tmp = *head;
	*head = (*head)->poprzedni;
	free(tmp);
}

void NaTablicy(const char* plik)
{
	int OstatniNaStosie = -1;
	int Sztos[JakDuzyStos]; 
	printf("Podawaj liczby i zakoncz podajac \"q\": ");
	char liczba[10];
	do
	{
		scanf_s("\n%s", liczba, 10);
		OstatniNaStosie++;
		Sztos[OstatniNaStosie] = atoi(liczba);
	} while (liczba[0] != 'q' && liczba[0] != 'Q' && OstatniNaStosie < JakDuzyStos-1);
	if (liczba[0] == 'q' || liczba[0] == 'Q')
	{
		--OstatniNaStosie;
	}
	WypiszTablica(Sztos, OstatniNaStosie, plik);
}

double SredniaTablica(int* stos, int OstatniNaStosie)
{
	double wynik = 0;
	for (int i = 0; i < OstatniNaStosie + 1; i++)
	{
		wynik += stos[OstatniNaStosie - i];
	}
	wynik /= (OstatniNaStosie + 1);
	return wynik;
}

void WypiszTablica(int* stos, int OstatniNaStosie, const char* NazwaPliku)
{
	double srednia = SredniaTablica(stos, OstatniNaStosie);
	FILE* plik;
	fopen_s(&plik, NazwaPliku, "w");
	if (plik == NULL)
	{
		printf_s("Nie mozna tu zapisac.");
		return;
	}
	fprintf_s(plik, "Liczby: ");
	for (int i = 0; i < OstatniNaStosie + 1; i++)
	{
		fprintf_s(plik, "%d ", stos[OstatniNaStosie - i]);
	}
	fprintf_s(plik, "\nsrednia: %f ", srednia);
	fclose(plik);
}

//3.

void Trzecie(void)
{
	struct TaggedFizyczne* uno = malloc(sizeof(struct TaggedFizyczne));
	struct TaggedFizyczne* dos = malloc(sizeof(struct TaggedFizyczne));
	Ustalenie(uno);
	Ustalenie(dos);
	char z;
	do
	{
		printf_s("Wpisz 1, aby dodac.\nWpisz 2, aby odjac drugą liczbe od pierwszej.\nWpisz 3, aby przeliczyc pierwsza liczbe na inna jednostke.\nWpisz 4, aby przeliczyc druga liczbe na inna jednostke.\nWpisz 5, aby podac nowa pierwsza liczbe.\nWpisz 6, aby podac nowa druga liczbe.\nWpisz 7, aby wyswietlic liczby.\nWpisz q, aby wyjsc.\n");
		scanf_s("\n%c", &z);
		switch (z)
		{
		case '1': //dodawanie
			Dodawanie(uno, dos);
			break;

		case '2': //odejmowanie
			Odejmowanie(uno, dos);
			break;

		case '3': 
			printf("Na jakie jednostki chcesz przeliczyć czas? Wpisz 1, dla godzin. Wpisz 2, dla minut. Wpisz 3, dla sekund.: ");
			do
			{
				scanf_s("\n%c", &z);
			} while (z < '1' || z > '3');
			z -= '1';
			Przeliczanie(uno, z);
			break;

		case '4': 
			printf("Na jakie jednostki chcesz przeliczyć czas? Wpisz 1, dla godzin. Wpisz 2, dla minut. Wpisz 3, dla sekund.: ");
			do
			{
				scanf_s("\n%c", &z);
			} while (z < '1' || z > '3');
			z -= '1';
			Przeliczanie(dos, z);
			break;

		case '5':
			Ustalenie(uno);
			break;

		case '6':
			Ustalenie(dos);
			break;

		case '7': //wypisz
			Wyswietl(uno, dos);
			break;

		case 'q':
		case 'Q':
			printf_s("generic goodbye message.\n");
			break;

		}
	} while (z != 'q' && z != 'Q');
	free(uno);
	free(dos);
}

void Ustalenie(struct TaggedFizyczne* nazwa)
{
	printf("W jakich jednostkach chcesz podac czas? Wpisz 1, dla godzin. Wpisz 2, dla minut. Wpisz 3, dla sekund.: ");
	char z;
	do
	{
		scanf_s("\n%c", &z);
	} while (z < '1' || z > '3');
	nazwa->fizyka = z - '1';
	printf("Podaj czas w ");
	switch (nazwa->fizyka)
	{
	case Sekunda:
		printf("sekundach: ");
		scanf_s("%i", &(nazwa->Sekunda));
		break;
		
	case Minuta:
		printf("minutach: ");
		scanf_s("%f", &(nazwa->GodzinaLubMinuta));
		break;
	case Godzina:
		printf("godzinach: ");
		scanf_s("%f", &(nazwa->GodzinaLubMinuta));
		break;
	}
}

void Przeliczanie(struct TaggedFizyczne* nazwa, char NaCo)
{
	switch (nazwa->fizyka)
	{
	case Sekunda:
		switch (NaCo)
		{
		case 1:
			nazwa->GodzinaLubMinuta = nazwa->Sekunda;
			nazwa->GodzinaLubMinuta /= 60;
			nazwa->fizyka = Minuta;
			break;

		case 0:
			nazwa->GodzinaLubMinuta = nazwa->Sekunda;
			nazwa->GodzinaLubMinuta /= 3600;
			nazwa->fizyka = Godzina;
			break;
		}
		break;

	case Minuta:
		switch (NaCo)
		{
		case 2:
			nazwa->Sekunda = nazwa->GodzinaLubMinuta * 60;
			nazwa->fizyka = Sekunda;
			break;

		case 0:
			nazwa->GodzinaLubMinuta = nazwa->GodzinaLubMinuta / 60;
			nazwa->fizyka = Godzina;
			break;
		}
		break;
	case Godzina:
		switch (NaCo)
		{
		case 2:
			nazwa->Sekunda = nazwa->GodzinaLubMinuta * 3600;
			nazwa->fizyka = Sekunda;
			break;

		case 1:
			nazwa->GodzinaLubMinuta = nazwa->GodzinaLubMinuta * 60;
			nazwa->fizyka = Minuta;
			break;
		}
		break;
	}
}

void Dodawanie(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos)
{
	if (Uno->fizyka>Dos->fizyka)
	{
		Przeliczanie(Uno, Dos->fizyka);
	}
	else
	{
		if (Uno->fizyka<Dos->fizyka) Przeliczanie(Uno, Dos->fizyka);
	}

	if (Uno->fizyka != Sekunda)
	{
		Uno->GodzinaLubMinuta += Dos->GodzinaLubMinuta;
	}
	else
	{
		Uno->Sekunda += Dos->Sekunda;
	}
}

void Odejmowanie(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos)
{
	if (Uno->fizyka>Dos->fizyka)
	{
		Przeliczanie(Uno, Dos->fizyka);
	}
	else
	{
		if (Uno->fizyka<Dos->fizyka) Przeliczanie(Uno, Dos->fizyka);
	}

	if (Uno->fizyka != Sekunda)
	{
		Uno->GodzinaLubMinuta += Dos->GodzinaLubMinuta;
	}
	else
	{
		Uno->Sekunda -= Dos->Sekunda;
	}
}

void Wyswietl(struct TaggedFizyczne* Uno, struct TaggedFizyczne* Dos)
{
	printf("Pierwsza liczba to ");
	switch (Uno->fizyka)
	{
	case Sekunda:
		printf("%i sekund. ", Uno->Sekunda);
		break;

	case Minuta:
		printf("%f minut. ", Uno->GodzinaLubMinuta);
		break;

	case Godzina:
		printf("%f godzin. ", Uno->GodzinaLubMinuta);
		break;
	}

	printf("\nDruga liczba to ");
	switch (Dos->fizyka)
	{
	case Sekunda:
		printf("%i sekund.\n", Dos->Sekunda);
		break;

	case Minuta:
		printf("%f minut.\n", Dos->GodzinaLubMinuta);
		break;

	case Godzina:
		printf("%f godzin.\n", Dos->GodzinaLubMinuta);
		break;
	}
}