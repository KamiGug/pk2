#include "Header.h"

const char ok[7] = { 'I','V','X','L','C', 'D', 'M' };
const int okk[7] = { 1,5,10,50,100,500,1000 };

char* DecToRom(int liczba) //3888
{
	char* wynik;
	if (liczba >= 4000 || liczba < 0)
	{
		wynik = (char*)malloc(3);
		strcpy_s(wynik, 3, "-1");
		return wynik;
	}
	
	if (liczba == 0)
	{
		wynik = (char*)malloc(3);
		strcpy_s(wynik, 3, "0");
		return wynik;
	}
	
	
	char buffer[15]; //największa liczba zapisana w systemie rzymskim ma 15 znaków
	int a = 0;
	for (short i = 0; i < 4; i++)
	{
		switch (liczba % 10) //obróć
		{
		case 3:
			buffer[a++] = ok[2 * i];
		case 2:
			buffer[a++] = ok[2 * i];
		case 1:
			buffer[a++] = ok[2 * i];
			break;

		case 9:
			buffer[a++] = ok[2 * i + 2];
			buffer[a++] = ok[2 * i];
			break;

		case 4:
			buffer[a++] = ok[2 * i + 1];
			buffer[a++] = ok[2 * i];
			break;
		case 5:
			buffer[a++] = ok[2 * i + 1];
			break;

		case 8:
			buffer[a++] = ok[2 * i];
		case 7:
			buffer[a++] = ok[2 * i];
		case 6:
			buffer[a++] = ok[2 * i];
			buffer[a++] = ok[2 * i + 1];
			break;
		}
		liczba /= 10;
	}
	wynik = (char*)malloc(a+1);
	for (int i = 0; i < a; i++)
	{
		wynik[i] = buffer[a - i - 1];
	}
	wynik[a] = 0;
	return wynik;
}

bool IsOkRoman(char* liczba, int len)
{
	char nwm = 0;
	int JakDuzyZnak = 0, IlePodrzad = 0, poprzedni, najm;
	while (--len >= 0)
	{
		if (nwm != 0) nwm = (nwm + 1) % 3;
		poprzedni = -1;
		while (ok[++poprzedni] != liczba[len]) {}
		if (poprzedni != 0 && poprzedni != 1 && poprzedni != 2 && poprzedni != 3 && poprzedni != 4 && poprzedni != 5 && poprzedni != 6)
		{
			return false;
		}
		if (poprzedni == JakDuzyZnak)
		{
			if (IlePodrzad == 3)
			{
				return false;
			}
			if (JakDuzyZnak % 2 == 1)
			{
				return false;
			}
			IlePodrzad++;
			continue;
		}
		if (poprzedni > JakDuzyZnak)
		{
			IlePodrzad = 1;
			JakDuzyZnak = poprzedni;
			continue;
		}
		if ((poprzedni == JakDuzyZnak - 2 || poprzedni == JakDuzyZnak - 1) && poprzedni % 2 == 0 && nwm == 0)
		{
			IlePodrzad = 0;
			nwm++;
			continue;
		}
		if (poprzedni < JakDuzyZnak) return false;
		
	}
	return true;
}

int RomToDec(const char* liczba, int len)
{
	if (!IsOkRoman(liczba, len)) return -1;
	int JakDuzy, poprzedni = -1, wynik = 0;
	while (--len >= 0 )
	{
		JakDuzy = -1;
		while (ok[++JakDuzy] != liczba[len]) {}
		if (JakDuzy >= poprzedni)
		{
			wynik += okk[JakDuzy];
			poprzedni = JakDuzy;
		}
		else
		{
			wynik -= okk[JakDuzy];
		}
	}
	return wynik;
}

void DoBuffora(buffor* buff, int NumerLoga)
{
	buff->buffered[buff->zapisywany] = NumerLoga;
	buff->zapisywany = (buff->zapisywany + 1) % SizeOfBuffor;
}


void ZBuffora(buffor* buff, FILE* plik)
{
	char* tmp;
	switch (buff->buffered[buff->czytany])
	{
	case 0:
		tmp = "smooth";
		break;

	case 1:
		tmp = "not so snotth";
		break;

	default:
		tmp = "Unknown error";
		break;
	}
	printf("%s \n", tmp);
	if (plik != NULL)fprintf_s(plik, "%s \n", tmp);
	buff->czytany = (buff->czytany + 1) % SizeOfBuffor;
}

int FindDec(char* Ciag, int szukana)
{
	int i = 0, a = 0;
	char zmienione[11];
	sprintf_s(zmienione, 11, "%d\0", szukana);
	while (i < (strlen(Ciag) - strlen(zmienione) + 1) && a != strlen(zmienione))
	{
		if (Ciag[i] == zmienione[0])
		{
			a++;
			while (a <= strlen(zmienione) && Ciag[i + a] == zmienione[a]) { a++; }
			if (a >= strlen(zmienione)) return i;
			a = 0;
		}
		i++;
	}
	return -1;
}

int FindRom(char* Ciag, char* szukana)
{
	if (!IsOkRoman(szukana, strlen(szukana))) return -1;
	int i = 0, a = 0;
	while (i < (strlen(Ciag) - strlen(szukana) + 1) && a != strlen(szukana))
	{
		if (Ciag[i] == szukana[0])
		{
			a++;
			while (a <= strlen(szukana) && Ciag[i + a] == szukana[a]) { a++; }
			if (a >= strlen(szukana)) return i;
			a = 0;
		}
		i++;
	}
	return -1;
}

Szukaj* Szukaj_W_Pliku(const char* const NazwaPliku)
{
	FILE* plik;

	int check = 1;
	fopen_s(&plik, NazwaPliku, "r");
	if (plik == NULL)
	{
		return -1;
	}
	char buffer[256];
	int x=0;
	char IleCudzyslow;
	Szukaj* info = NULL;
	while (fscanf_s(plik, "%s\0", buffer, 256) != EOF && info == NULL)
	{ 
		x++; 
		info = Find_A_Rom(buffer);
	}
	fclose(plik);
	info->KtoreSlowo = x;
	return info;
}

Szukaj* Find_A_Rom(char* Ciag)
{
	char nwm = 0, prawo = 0, a, limit;
	int TuJestV = -1;
	while (++TuJestV < strlen(Ciag) && Ciag[TuJestV] != 'V') {}
	if (TuJestV == strlen(Ciag)) return NULL;
	Szukaj* wynik = (Szukaj*)malloc(sizeof(Szukaj));

	char tabela[7];
	limit = tabela[3] = 1;
	
	while (++nwm < 4 && TuJestV - nwm >= 0 && ( Ciag[TuJestV - nwm] == ok[0] || Ciag[TuJestV - nwm] == ok[1] || Ciag[TuJestV - nwm] == ok[2] || 
		Ciag[TuJestV - nwm] == ok[3] || Ciag[TuJestV - nwm] == ok[4] || Ciag[TuJestV - nwm] == ok[5] || Ciag[TuJestV - nwm] == ok[6])) 
	{

		a = -1;
		while (Ciag[TuJestV - nwm] != ok[++a]) {}
		tabela[3 - nwm] = a;
		if (((a == tabela[3 - nwm + 1] || a + 2 == tabela[3 - nwm + 1] || a + 1 == tabela[3 - nwm + 1]) && (int)a % 2 == 0) || a >= limit)
		{
			limit = a > limit ? a : limit;
			continue;
		}
		--a;
		break;
	}
	while (++prawo < 4 && TuJestV + prawo >= 0 && Ciag[TuJestV + prawo] == ok[0])
	{
		tabela[3 + prawo] = 0;
	}
	wynik->poczatek = TuJestV - nwm + 2;
	wynik->ZnalezionaLiczba = (char*)malloc(prawo + nwm);
	for (char i = 0; i < prawo + nwm -1 ; i++)
	{
		wynik->ZnalezionaLiczba[i] = ok[(int)tabela[i + 4 - nwm]];
	}
	wynik->ZnalezionaLiczba[prawo + nwm - 1] = 0;
	return wynik;
}