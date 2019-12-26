#pragma once
#pragma warning(disable : 4996)
#define MAX 20
#include<conio.h>
#include <stdlib.h>
#include<string>
#include <iostream>
#include <time.h>

typedef struct admin {
	char password[MAX], username[MAX];	//cuvanje korisnickog unosa
	short flag;//ako je korisnik 5 puta unio pogreesne pristupne podatke da se onemoguci ponovno unosenje neko vrijeme
}ADMIN;

typedef struct datum {
	int dan, mjesec, godina;
}DATUM;

typedef struct vrijeme {
	int sat, minute;
}VRIJEME;

typedef struct dogadjaj {
	int id;
	char naziv[100], opis, lokacija[100], kategorija[30], datum[12], vrijeme[6], komentari, preporucen;
}DOGADJAJ;

int unos_korisnickih_podataka_admina();
int logovanje_admina();
int dodaj_dogadjaj();
int unos_datuma(char*);
int prestupna_godina(int godina);
int provjera_datuma(DATUM datum);
int unos_vremena(char []);
int provjera_vremena(VRIJEME);
void sleep(unsigned int secs);

int unos_korisnickih_podataka_admina()
{
	FILE* pristupni_podaci;		//Datoteka u kojoj se nalaze pristupni podaci za logovanje administratora na sistem
	char usernamecheck[MAX], passwordcheck[MAX], ch;	//za smjestanje pristupnih podataka iz daoteke

	ADMIN admin;

	for ( int i = 0; i < MAX; i++)
		admin.password[i] = 0;

	printf("\nKorisnicko ime: "); scanf("%s", admin.username);
	if ((admin.username[0] == 'e' && admin.username[1] == 0) || (admin.username[0] == 'E' && admin.username[1] == 0))
		exit(1);
		
	printf("Lozinka: ");
	ch = _getch();
	int i = 0;
	while (ch != 13)
	{
		if (ch != 8)
		{
			admin.password[i] = ch;
			printf("*");
		}
		ch = _getch();
		i++;
	}
	if ((pristupni_podaci = fopen("../config files/Pristupni podaci za admine/admin_acc.txt", "r")) != NULL)
	{
		while (fscanf(pristupni_podaci, "%s %s", usernamecheck, passwordcheck) != EOF)
			if (strcmp(usernamecheck, admin.username) == 0 && strcmp(passwordcheck, admin.password) == 0)
				return 1;
	}
	else
		printf("Greska prilikom otvaranja datoteke u kojj se nalaze pristupni podaci administratora!\n");
	fclose(pristupni_podaci);
	
	return 0;
}

int logovanje_admina()
{
	char c[5];
	int br_pokusaja = 5;  //broji pokusaja da se unesu tacni podaci
	while (br_pokusaja && !unos_korisnickih_podataka_admina())
	{
		--br_pokusaja;

		printf("\nPorgesno korisnicko ime ili lozinka!\nUnesite 'e' za izlaz iz programa ili unesite 'p' za ponovni unos podataka!\n");
		scanf("\n%s", &c);

		while (c[1] != 0 || (c[0] != 'p' && c[0] != 'P' && c[0] != 'e' && c[0] != 'E'))
		{
			printf("Nepostojeca opcija!\nUnesite 'e' ili 'p': ");
			scanf("\n%s", &c);
		}
		if (c[0] == 'e' || c[0] == 'E')
			exit(1);
		else if (c[0] == 'p' || c[0] == 'P')
		{
			printf("\nUPOZORENJE!\nOSTALO VAM JE JOS %d POKUSAJA!\n", br_pokusaja);
			continue;
		}
	}
	if (br_pokusaja == 0)
	{
		printf("Vas nalog ce biti blokiran narednih sat vremena!");
		do
		{
			printf("Unesite 'e' za izlazak: ");
			scanf("%s", &c);
		} while (c[1] != 0 || (c[0] != 'e' && c[0] != 'E'));
	}
}


int dodaj_dogadjaj()
{
	int br_kategorija;
	char datum[12] = "";
	char vrijeme[6];
	DOGADJAJ dogadjaj;
	VRIJEME vrijeme_provjera;//za provjeru da li je korisnik dobro unio vrijeme
	FILE* kategorije_dat;
	char* kategorija[20];	//moram dealocirati nekada negdje
	

	if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r")) != NULL)
	{
		fscanf(kategorije_dat, "%d", &br_kategorija);
		for (int i = 0; i < br_kategorija; i++)
			kategorija[i] = (char*)calloc(br_kategorija,sizeof(char));
		int i = 0;
		while (fgets(kategorija[i], 20, kategorije_dat) != NULL)
		{
			++i;
			fgets(kategorija[i], 20, kategorije_dat);
		}
		fclose(kategorije_dat);
	}
	else
		printf("Greska u otvaranju datoteke kategorije.txt");

	printf("UNesite odgovarajuci broj da izaberete zeljenu kategoriju ili da unesete novu kategoriju.\n");
	

	/*for (int i = 0; i < br_kategorija; i++)
		printf("%s", kategorija[i]);*/
	/*
	printf("Naziv dogadjaja: ");
	scanf("\n%[^\n]s",dogadjaj.naziv);
	printf("Mjesto odrzavanja dogadjaja: ");
	scanf("\n%[^\n]s",dogadjaj.lokacija);
	printf("Vrijeme odrzavanaja dogadjaja: ");
	unos_vremena(vrijeme);
	printf("Datum odrzavanja dogadjaja: ");
	unos_datuma(datum);//korisnik ce unositi datum dok datum ne bude dobar
	*/
	return 1;
}

int unos_datuma(char* datum)
{
	DATUM datum_check;
	char mjesec[3], godina[5];
	do
	{
		printf("Dan: ");
		scanf("%d", &datum_check.dan);
		printf("Mjesec: ");
		scanf("%d", &datum_check.mjesec);
		printf("Godina: ");
		scanf("%d", &datum_check.godina);
	} while (!provjera_datuma(datum_check));
	itoa(datum_check.dan, datum,10);
	strcat(datum, ".");
	strcat(datum, itoa(datum_check.mjesec, mjesec, 10));
	strcat(datum, ".");
	strcat(datum, itoa(datum_check.godina, godina, 10));
	strcat(datum, ".");
	return 1;
}

int prestupna_godina(int godina)
{
	if ((godina % 4 == 0 && godina % 100 != 0) || (godina % 4 == 0 && godina % 400 == 0))
		return 1;
	else return 0;
}
int provjera_datuma(DATUM datum)
{
	if ((datum.mjesec == 1 || datum.mjesec == 3 || datum.mjesec == 5 || datum.mjesec == 7
		|| datum.mjesec == 8 || datum.mjesec == 10 || datum.mjesec == 12) && (datum.dan > 31 || datum.dan < 1))
		return 0;
	else if ((datum.mjesec == 4 || datum.mjesec == 6 || datum.mjesec == 9 || datum.mjesec == 11) && (datum.dan > 30 || datum.dan < 1))
		return 0;
	else if ((datum.mjesec == 2 && prestupna_godina(datum.godina)) && (datum.dan > 29 || datum.dan <1))
		return 0;
	else if ((datum.mjesec == 2 && !prestupna_godina(datum.godina)) && (datum.dan > 28 || datum.dan < 1))
		return 0;
	return 1;		
}

int unos_vremena(char vrijeme[])
{
	VRIJEME time;
	do
	{
		printf("U koliko sati: ");
		scanf("%d", &time.sat);
		printf("U koliko minuta: ");
		scanf("%d", &time.sat);
	} while (!provjera_vremena(time));
	char min[3];
	itoa(time.sat, vrijeme, 10);
	strcat(vrijeme, ".");
	strcat(vrijeme, itoa(time.minute, min, 10));
	return 1;
}

int provjera_vremena(VRIJEME time)
{
	if ((time.sat > 23 || time.sat < 0) || (time.minute > 60 || time.minute < 0))
		return 0;
	else return 1;
	
}
void sleep(unsigned int* secs)
{
	unsigned int retTime = time(0) + *secs;  
	while (time(0) < retTime);
}

