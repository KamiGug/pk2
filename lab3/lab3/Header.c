#include "Header.h"

//fwrite(), fread()

void start(void)
{
	//Pierwsze();
	Drugie();
}

void Pierwsze(void)
{
	BrakCheciDoZycia xD
	char ZabawnaTablica[16], buffer[300];
	short a = 22746;
	void* hmm;
	hmm = memset(ZabawnaTablica, a, 16 * sizeof(char));
	printf("%.16s jest to sobie tablica typu char*, %p, %p", ZabawnaTablica, hmm, &ZabawnaTablica);
	char ZabawnaTablicaPowrot[85] = "According to all known laws of aviation, there is no way a bee should be able to fly";
	memmove(ZabawnaTablicaPowrot, ZabawnaTablica, 16 * sizeof(char));
	puts(" *cough*");
	puts("\n %s", ZabawnaTablicaPowrot);
	printf("%.85s", ZabawnaTablicaPowrot);
	memcpy(ZabawnaTablica, "According to all", 16);
	printf("%.16s", ZabawnaTablica);
	int x = sprintf_s(buffer, sizeof(buffer), "ZabawnaTablica to: %16s", ZabawnaTablica);//<<
	x += sprintf_s(buffer + x, sizeof(buffer) - x, " %i - liczba bajtow \"ZabawnaTablica to: %s\"", x, "%s");
	printf("\nJezyk C jest przestarzaly i niepotrzebny, ale: %s", buffer);
	printf(" %.16s\n %s\n", ZabawnaTablica, TenJezyk);
	memcpy(ZabawnaTablicaPowrot, "According to all", 16);
	FILE* pliczek;
	fopen_s(&pliczek, "plik.txt", "w");
	fputs(ZabawnaTablicaPowrot, pliczek);
	fclose(pliczek);
	fputs(ZabawnaTablicaPowrot, stdout);
	fputs("\nProsze podac cyfre: ", stdout);
	char cyfra;
	scanf_s("%c", &cyfra);
	assert(isdigit(cyfra));

}

void Drugie(void)
{
	struct wiersz* head = NULL;
	int x = 0, y = 0;
	if (!CzytajDoListy(&head, "Untitled 1.csv"))
	{
		printf("Well, fuck...");
		return;
	}
	char*** tablica;
	ListaNaTablice(head, &tablica, &x, &y);
	UsunListe(&head);



	WyczyscTablice(&tablica, x, y);

}

void RozmiarTablicy(struct wiersz* head, int* x, int* y)
{
	*x = 0;
	*y = 0;
	int tmp_x;
	struct kolumna* tmp;
	while (head != NULL)
	{
		(*y)++;
		tmp = head->komorka;
		tmp_x = 0;
		while (tmp != NULL)
		{
			tmp_x++;
			tmp = tmp->nast;
		}
		if (tmp_x > *x)
		{
			*x = tmp_x;
		}
		head = head->nast;
	}
}

void ListaNaTablice(struct wiersz* head, char**** tablica, int* x, int* y)
{
	RozmiarTablicy(head, x, y);

	*tablica = (char***)malloc((*y)*sizeof(char**));
	struct kolumna* tmp;
	int a;
	for (int i = 0; i < *y; i++)
	{
		*tablica[i] = (char**)malloc((*x)*sizeof(char*));
		tmp = head->komorka;
		a = 0;
		while (a < *x && tmp != NULL)
		{
			if (tmp->ZawartoscKomorki != NULL)
			{
				*tablica[i][a] = (char*)malloc(strlen(tmp->ZawartoscKomorki)+1);
				strcpy_s(*tablica[i][a], sizeof(*tablica[i][a])+1, tmp->ZawartoscKomorki);
			}
			else
			{
				*tablica[i][a] = NULL;
			}
			tmp = tmp->nast;
		}
		for (a; a < *x; a++)
		{
			*tablica[i][a] = NULL;
		}
		head = head->nast;
	}

}

void WyczyscTablice(char**** tablica, int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (*tablica[i][j] != NULL)
			{
				free(*tablica[i][j]);
			}
		}
		free(*tablica[i]);
	}
	free(*tablica);
	*tablica = NULL;
}

bool CzytajDoListy(struct wiersz** head, const char* const NazwaPliku)
{
	FILE* plik;
	int check = 1;
	fopen_s(&plik, NazwaPliku, "r");
	if (plik == NULL)
	{
		return false;
	}
	char buffer[256];
	int x;
	char IleCudzyslow;
	struct wiersz* tmpw;
	struct kolumna* tmpk;
	while (check !=EOF)
	{
		tmpw = DodajWiersz(head);
		do
		{
			x = -1;
			IleCudzyslow = 0;
			do
			{
				x++;
				check = fscanf_s(plik, "%c", buffer + x);
				if (*(buffer + x) == '"')
				{
					IleCudzyslow++;
				}
			} while (check!=EOF && (x < 255 && !((*(buffer + x) == ',' || *(buffer + x) == 10 || *(buffer + x) == 13) &&  IleCudzyslow%2 == 0)));
			*(buffer + x + 1) = '\0';
			DodajKomorke(&(tmpw->komorka), buffer, IleCudzyslow);
		} while (check!=EOF && (*(buffer + x) != 10 && *(buffer + x) != 13));

	}
	fclose(plik);
	
	return true;
}

struct wiersz* DodajWiersz(struct wiersz** head)
{
	if (*head == NULL)
	{
		*head = malloc(sizeof(struct wiersz));
		(*head)->nast = NULL;
		(*head)->komorka = NULL;
		return *head;
	}
	struct wiersz* tmpw = *head;
	while (tmpw->nast != NULL)
	{
		tmpw = tmpw->nast;
	}
	tmpw->nast = malloc(sizeof(struct wiersz));
	tmpw->nast->nast = NULL;
	tmpw->nast->komorka = NULL;
	return tmpw->nast;
}

void DodajKomorke(struct kolumna** head, char* zawartosc, char IleZnaczkow)
{
	char i = 0;
	if (*head == NULL)
	{
		*head = malloc(sizeof(struct kolumna));
		(*head)->nast = NULL;
		if (strlen(zawartosc) - IleZnaczkow - 1 > 0) //oczekiwana jest zawartosc komorki w cudzyslowiach zakonczona przecinkiem lub znakiem konca linii
		{
			(*head)->ZawartoscKomorki = malloc(strlen(zawartosc) - IleZnaczkow - 1);
			for (i; i < strlen(zawartosc)-1; i++)
			{
				(*head)->ZawartoscKomorki[i] = zawartosc[i + (IleZnaczkow/2)];
			}
			(*head)->ZawartoscKomorki[i] = 0; //zapisywana jest zawartosc komorki zakonczona znakiem '\0'
		}
		else
		{
			(*head)->ZawartoscKomorki = NULL;
		}
		return;
	}
	struct kolumna* tmp = *head;
	while (tmp->nast != NULL)
	{
		tmp = tmp->nast;
	}
	tmp->nast = malloc(sizeof(struct kolumna));
	tmp->nast->nast = NULL;
	if (strlen(zawartosc) - 3 > 0) //oczekiwana jest zawartosc komorki w cudzyslowiach zakonczona przecinkiem lub znakiem konca linii
	{
		tmp->nast->ZawartoscKomorki = malloc(strlen(zawartosc) - IleZnaczkow);
		for (i; i < strlen(zawartosc) - 1; i++)
		{
			tmp->nast->ZawartoscKomorki[i] = zawartosc[i + (IleZnaczkow / 2) - 1];
		}
		tmp->nast->ZawartoscKomorki[i] = 0; //zapisywana jest zawartosc komorki zakonczona znakiem '\0'
	}
	else
	{
		tmp->nast->ZawartoscKomorki = NULL;
	}
}

void UsunListe(struct wiersz** head)
{
	struct wiersz* tmpw;
	struct kolumna* tmpk;
	while (*head!=NULL)
	{
		while ((*head)->komorka!=NULL)
		{
			if ((*head)->komorka->ZawartoscKomorki != NULL) free((*head)->komorka->ZawartoscKomorki);
			tmpk = (*head)->komorka;
			(*head)->komorka = (*head)->komorka->nast;
			free(tmpk);
		}
		tmpw = *head;
		*head = (*head)->nast;
		free(tmpw);
	}
	*head = NULL;
}