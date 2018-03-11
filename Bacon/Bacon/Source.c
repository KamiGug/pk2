#include <stdio.h>/*uzywana jest druga wersja szyfru Bacona, gdzie kazda litera jest jednoznacznie określona*/
#include <stdlib.h>
#include <string.h>

#define aA  32 //róznica między 'a' i 'A'

typedef struct
{
	char rozszyfrowany[100];
	char zaszyfrowany[500];
} tekst;

/*void usuwanie(tekst* THESACREDTEXTS)
{
	if (THESACREDTEXTS->rozszyfrowany != NULL) free(THESACREDTEXTS->rozszyfrowany);
	THESACREDTEXTS->rozszyfrowany = NULL;
	if (THESACREDTEXTS->zaszyfrowany != NULL) free(THESACREDTEXTS->zaszyfrowany);
	THESACREDTEXTS->zaszyfrowany = NULL;
}*/

/*void tworzenie(int dlugosc, tekst* THESACREDTEXTS)
{
	if (THESACREDTEXTS->rozszyfrowany != NULL && THESACREDTEXTS->zaszyfrowany == NULL)
	{
		THESACREDTEXTS->zaszyfrowany = malloc(sizeof(char) * dlugosc);
		return;
	}
	if (THESACREDTEXTS->zaszyfrowany != NULL && THESACREDTEXTS->rozszyfrowany == NULL)
	{
		THESACREDTEXTS->rozszyfrowany = malloc(sizeof(char) * dlugosc * 5);
		return;
	}
	if (THESACREDTEXTS->rozszyfrowany != NULL && THESACREDTEXTS->zaszyfrowany != NULL)
	{
		usuwanie(THESACREDTEXTS);
	}
	THESACREDTEXTS->zaszyfrowany = malloc(sizeof(char) * dlugosc);
	THESACREDTEXTS->rozszyfrowany = malloc(sizeof(char) * dlugosc * 5);
}*/

void ZmniejszanieLiter(char* tekst)
{
	for (int i = 0; i < strlen(tekst); i++)
	{
		if (tekst[i] < 'Z' + 1) tekst[i] += aA;
	}
}

void Szyfrowanie(tekst* THESACREDTEXTS)
{
	char a;
	int j;
	for (j = 0; j < strlen(THESACREDTEXTS->rozszyfrowany); j++)
	{
		a = THESACREDTEXTS->rozszyfrowany[j]-'a';
		for (int i = 0; i < 5; i++)
		{
			THESACREDTEXTS->zaszyfrowany[j * 5 + 4 - i] = 'a' + a % 2;
			a /= 2;
		}
	}
	if (5 * j + 5 < 500) THESACREDTEXTS->zaszyfrowany[j * 5] = 0;
}

void odszyfrowanie(tekst* THESACREDTEXTS)
{
	char a;
	int j;
	for (j = 0; j < strlen(THESACREDTEXTS->zaszyfrowany); j+=5)
	{
		a = 0;
		for (int i = 0; i < 5; i++)
		{
			a *= 2;
			a += THESACREDTEXTS->zaszyfrowany[j + i] - 'a';
		}
		THESACREDTEXTS->rozszyfrowany[j/5] = a + 'a';
	}
	if (j < 500) THESACREDTEXTS->rozszyfrowany[j/5] = 0;
}

int main()
{
	tekst* potrzebne = malloc(sizeof(tekst));
	char przelacznik;
	printf("Wpisz znak odpowiadajacy Twojemu wyborowi:\n\"S\": szyfruj,\n\"D\": odszyfruj,\n\"Q\": wyjdz.\n");
	do
	{
		scanf_s("%c", &przelacznik);
		switch (przelacznik)
		{
		case 'q':
		case 'Q':
			break;

		case 's':
		case 'S':
			printf("Podaj tekst do zaszyfrowania(nie dluzszy niz 100 znakow i bez interpunkcji lub bialych znakow):");
			scanf_s("%s", potrzebne->rozszyfrowany, 100);
			ZmniejszanieLiter(potrzebne->rozszyfrowany);
			Szyfrowanie(potrzebne);
			printf("Zaszyfrowany tekst: %s", potrzebne->zaszyfrowany);
			break;

		case 'd':
		case 'D':
			printf("Podaj tekst do odszyfrowania(nie dluzszy niz 500 znakow i bez interpunkcji lub bialych znakow oraz skladajacy sie z a i b):");
			scanf_s("%s", potrzebne->zaszyfrowany, 500);
			if (strlen(potrzebne->zaszyfrowany) % 5 != 0) printf("Niepoprawny tekst.");
			else
			{
				ZmniejszanieLiter(potrzebne->zaszyfrowany);
				short i = 1;
				int a = 0;
				while (a < strlen(potrzebne->zaszyfrowany) && i == 1)
				{
					if (potrzebne->zaszyfrowany[a] != 'a' && potrzebne->zaszyfrowany[a] != 'b')
					{
						i = 0;
					}
					a++;
				}
				if (i == 1)
				{
					odszyfrowanie(potrzebne);
					printf("Odszyfrowany tekst: %s", potrzebne->rozszyfrowany);
				}
				else
				{
					printf("Niepoprawny tekst");
				}
			}
			break;

		default:
			printf("\nWpisz znak odpowiadajacy Twojemu wyborowi:\n\"S\": szyfruj,\n\"D\": odszyfruj,\n\"Q\": wyjdz.\n");
			break;
		}
	} while (przelacznik != 'q' && przelacznik != 'Q');
	free(potrzebne);
	return 0;
}