#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <math.h>
#include "KorisnickaAppHeader.h"
#include <iostream>
#include <conio.h>
#include <ctype.h>

typedef struct dogadjaj
{
	int id;
	char naziv[31];
	char opis;
	char lokacija[52];
	char kategorija[20];
	char datum[12];
	char vrijeme[6];
	char komentari;
	char preporucen;
}DOGADJAJ;

typedef struct zainteres
{
	int id;
	int br;
}ZAINTERESOVAN;

typedef struct datum 
{
	int dan, mjesec, godina;
}DATUM;

int ucitaj_br_dogadjaja(FILE*);
void ucitaj_dogadjaje_iz_datoteke(FILE*,DOGADJAJ*,int);
void ispisi_dogadjaj(DOGADJAJ*); //pomocna funkcija, koja ispisuje samo 1 dogadjaj
void svi_dogadjaji(DOGADJAJ*,int);
void preporuceni_dogadjaji(DOGADJAJ*,int);
int danasnji_dogadjaji(DOGADJAJ*,int);
void prosli_dogadjaji(DOGADJAJ*,int);
void buduci_dogadjaji(DOGADJAJ*,int);


int unesi_id();
DOGADJAJ* trazi_dogadjaj_id(DOGADJAJ*,int,int);
void pisi_dogadjaje_filter(DOGADJAJ*,int);
void unesi_komentar(int);
void ispisi_komentar(int);
void prikazi_opis(DOGADJAJ*, int);
void zainteresovan_za_dogadjaj(int);

int ucitaj_br_dogadjaja(FILE* dat_dogadjaji)
{
	int id, br;
	fscanf(dat_dogadjaji, "%d %d", &id, &br);
	return br;
}

void ucitaj_dogadjaje_iz_datoteke(FILE* dat_dogadjaji, DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	char temp_arr[200] = {};
	int i = 0;
	while (fscanf(dat_dogadjaji, "\n%[^\n]s", temp_arr) != EOF)
	{
		char* ostatak;
		lista_dogadjaja[i].id = strtol(temp_arr, &ostatak,10); //implicitno kastovanje iz long u int //mozda ce praviti problem
		int j = 1; // 1 zato sto je u stringu "ostatak" prvi karakter zapeta
		int t = 0;

		for (t = 0; ostatak[j] != ','; j++, t++)
			lista_dogadjaja[i].naziv[t] = ostatak[j];
		lista_dogadjaja[i].naziv[t] = '\0'; j++;

		lista_dogadjaja[i].opis = ostatak[j];
		j += 2;
		for (t = 0; ostatak[j] != ','; j++, t++)
			lista_dogadjaja[i].lokacija[t] = ostatak[j];
		lista_dogadjaja[i].lokacija[t] = '\0'; j++;

		for (t = 0; ostatak[j] != ','; j++, t++)
			lista_dogadjaja[i].kategorija[t] = ostatak[j];
		lista_dogadjaja[i].kategorija[t] = '\0'; j++;

		for (t = 0; ostatak[j] != ','; j++, t++)
			lista_dogadjaja[i].datum[t] = ostatak[j];
		lista_dogadjaja[i].datum[t] = '\0'; j++;

		for (t = 0; ostatak[j] != ','; j++, t++)
			lista_dogadjaja[i].vrijeme[t] = ostatak[j];
		lista_dogadjaja[i].vrijeme[t] = '\0'; j++;

		lista_dogadjaja[i].komentari = ostatak[j++]; j++;
		lista_dogadjaja[i].preporucen = ostatak[j++];

		++i;
	}
}

void ispisi_dogadjaj(DOGADJAJ* lista_dogadjaja)
{
	printf("%5d  %-30s  %-10s  %-50s  %-20s  %12s  %5s  %-13s  %s\n",lista_dogadjaja->id,lista_dogadjaja->naziv, lista_dogadjaja->opis=='1'?"ima opis":"nema opisa" ,lista_dogadjaja->lokacija,lista_dogadjaja->kategorija,lista_dogadjaja->datum,lista_dogadjaja->vrijeme,lista_dogadjaja->komentari=='1'?"Ima komentar":"Nema komentar",lista_dogadjaja->preporucen=='1'?"Preporucen":"");
}

void svi_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	for (int i = 0; i < br_dogadjaja; i++)
		ispisi_dogadjaj(&lista_dogadjaja[i]);
}

void preporuceni_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	for (int i = 0; i < br_dogadjaja; i++)
		if(lista_dogadjaja[i].preporucen-48)
			ispisi_dogadjaj(&lista_dogadjaja[i]);
}

int danasnji_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja) 
{
	SYSTEMTIME t;
	GetLocalTime(&t); //generise danasnji datum
	char temp_date[12] = {};
	char buffer[5];
	strcat(temp_date, itoa(t.wDay, buffer, 10));
	strcat(temp_date, ".");
	strcat(temp_date, itoa(t.wMonth, buffer, 10));
	strcat(temp_date, ".");
	strcat(temp_date, itoa(t.wYear, buffer, 10));
	strcat(temp_date, ".");
	char flag = 0;
	for (int i = 0; i < br_dogadjaja; i++)
		if (!strcmp(temp_date, lista_dogadjaja[i].datum))
		{
			ispisi_dogadjaj(&lista_dogadjaja[i]);
			flag = 1;
		}
	if (!flag) printf("\tNema desavanja u gradu danas... :(\n");
	return flag;
}

void buduci_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	//generisanje danasnjeg datuma
	SYSTEMTIME t;
	GetLocalTime(&t);
	char temp_day[3] = {};
	char temp_month[3] = {};
	char temp_year[5] = {};
	char buffer[5];
	strcpy(temp_day, itoa(t.wDay, buffer, 10));
	strcpy(temp_month, itoa(t.wMonth, buffer, 10));
	strcpy(temp_year, itoa(t.wYear, buffer, 10));


	for (int i = 0; i < br_dogadjaja; i++)
	{
		char separator[] = ".";
		char* ptr[4] = {};//niz pokazivaca (na dan, mjesec i godinu) i-tog dogadjaja
		char datum[12] = {}; strcpy(datum, lista_dogadjaja[i].datum); //jer strtok prepise originalni datum
		ptr[0] = strtok(datum, separator); //pokazivac na dan
		ptr[1] = strtok(NULL, separator); //pokazivac na mjesec
		ptr[2] = strtok(NULL, separator); //pokazivac na godinu

		if (strcmp(temp_year, ptr[2]) < 0)
			ispisi_dogadjaj(&lista_dogadjaja[i]);
		else if (strcmp(temp_year, ptr[2]) == 0)
			if (strcmp(temp_month, ptr[1]) < 0)
				ispisi_dogadjaj(&lista_dogadjaja[i]);
			else if (strcmp(temp_month, ptr[1]) == 0)
				if (strcmp(temp_day, ptr[0]) < 0)
					ispisi_dogadjaj(&lista_dogadjaja[i]);
	}
}

void prosli_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	//generisanje danasnjeg datuma
	SYSTEMTIME t;
	GetLocalTime(&t);
	char temp_day[3] = {};
	char temp_month[3] = {};
	char temp_year[5] = {};
	char buffer[5];
	strcpy(temp_day, itoa(t.wDay, buffer, 10));
	strcpy(temp_month, itoa(t.wMonth, buffer, 10));
	strcpy(temp_year, itoa(t.wYear, buffer, 10));

	
	for (int i = 0; i < br_dogadjaja; i++)
	{
		char separator[] = ".";
		char* ptr[4] = {};//niz pokazivaca (na dan, mjesec i godinu) i-tog dogadjaja
		char datum[12] = {}; strcpy(datum,lista_dogadjaja[i].datum); //jer strtok prepise originalni datum
		ptr[0]= strtok(datum, separator); //pokazivac na dan
		ptr[1] = strtok(NULL, separator); //pokazivac na mjesec
		ptr[2] = strtok(NULL, separator); //pokazivac na godinu
		
		if (strcmp(temp_year, ptr[2]) > 0)
			ispisi_dogadjaj(&lista_dogadjaja[i]);
		else if (strcmp(temp_year, ptr[2]) == 0)
			if (strcmp(temp_month, ptr[1]) > 0)
				ispisi_dogadjaj(&lista_dogadjaja[i]);
			else if (strcmp(temp_month, ptr[1]) == 0)
				if (strcmp(temp_day, ptr[0]) > 0)
					ispisi_dogadjaj(&lista_dogadjaja[i]);
	}
}

DOGADJAJ* trazi_dogadjaj_id(DOGADJAJ* lista_dogadjaja, int br_dogadjaja,int src_id)
{
	for (int i = 0; i < br_dogadjaja; i++)
		if (lista_dogadjaja[i].id == src_id)
			return &lista_dogadjaja[i];
	return NULL;
}

int unesi_id()
{
	char  niz[1000] = {};
	printf("\nUnesite id dogadjaja:");
	scanf("\n%[^\n]s",niz);
	while (niz[4] != 0 || (niz[0]<48 || niz[0]>57) || (niz[1] < 48 || niz[1]>57) || (niz[2] < 48 || niz[2]>57) || (niz[3] < 48 || niz[3]>57))
	{
		printf("\nPogresan unos. Unesite ponovo:");
		scanf("\n%[^\n]s", niz);
	}
	int id=((niz[0]-48)*1000)+((niz[1]-48)*100)+((niz[2]-48)*10)+(niz[3]-48);
	return id;
}

void prikazi_opis(DOGADJAJ* lista_dogadjaja,int br_dogadjaja)
{
	int flag = 0, pom_id = 0;
	FILE* dat_opis = NULL;
	int id = unesi_id();
	DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, id);
	if (!trazeni_dogadjaj) 
		printf("\nNe postoji dogadjaj sa unesenim id-om.\n\n");
	else if ((trazeni_dogadjaj->opis - 48)==0) 
		printf("\nDogadjaj sa unesenim id-om nema opis.\n\n");
	else
	{
		dat_opis = fopen("../config files/Dogadjaji/opis_dogadjaja.txt", "r");
		char temp_arr[200] = {};
		while ((fscanf(dat_opis, "\n%[^\n]s", temp_arr) != EOF) && !flag)
		{
			char* ostatak;
			pom_id = strtol(temp_arr, &ostatak, 10);
			if (pom_id == id)
			{
				printf("\n%s\n\n", ostatak + 1);
				flag = 1;
			}
		}
		fclose(dat_opis);
	}
}

void ispisi_komentar(int id)
{
	FILE* dat_komentari = fopen("../config files/Dogadjaji/komentari.txt", "r");
	if (!dat_komentari) { printf("Neuspjesno ucitavanje datoteke komentari.txt"); return; }
	else
	{
		int c=0;
		int temp_id=0;
		char flag = 0;
		while (c != EOF)
		{
			temp_id = 0;
			for (int i = 3; i >=0; i--)
			{
				c = fgetc(dat_komentari);
				temp_id += ((c - 48)* (int)pow(10,i));
			}
			c = fgetc(dat_komentari); //da preskoci zapetu
			if (temp_id == id) { flag = 1; printf("\n"); }
			while ((c = fgetc(dat_komentari)) != 10 && c!=EOF)
			{
				if (temp_id == id)
					printf("%c", c);
			}
			if(temp_id==id) printf("\n");
		}
		if (!flag) printf("\nNije pronadjen komentar za dogadjaj sa unesenim id-om\n");
		fclose(dat_komentari);
	}
}

void unesi_komentar(int id)
{
	FILE* dat_komentari = fopen("../config files/Dogadjaji/komentari.txt", "a+");
	if (!dat_komentari) { printf("Neuspjesno ucitavanje datoteke komentari.txt"); return; }
	else
	{
		char kom[1000] = {};
		printf("\nUnesite komentar: ");
		scanf("\n%[^\n]s", kom);
		fprintf(dat_komentari, "\n%d,%s", id, kom);
		fclose(dat_komentari);
	}
}

void zainteresovan_za_dogadjaj(int id)
{
	FILE* dat_zainteresovani = fopen("../config files/Dogadjaji/zainteresovani_za_dogadjaj.txt", "r");
	if (!dat_zainteresovani) { printf("Neuspjesno ucitavanje datoteke zainteresovani_za_dogadjaj.txt"); return; }
	else
	{
		int br_dogadjaja;
		fscanf(dat_zainteresovani, "%d", &br_dogadjaja);
		

		ZAINTERESOVAN* niz = (ZAINTERESOVAN*)calloc(4, 8);

		// ucitavanje iz datoteke u memoriju
		for (int i = 0; i < br_dogadjaja; i++)
			fscanf(dat_zainteresovani, "%d %d", &(niz+i)->id, &(niz + i)->br);
		fclose(dat_zainteresovani); dat_zainteresovani = NULL;
		char flag = 0;
		int i = 0; //brojac
		for (; i < br_dogadjaja && !flag; i++)
			if (niz[i].id == id) flag = 1;
		if (!flag) //ako ne nadje
		{
			br_dogadjaja++; //nema ga u nizu, pa povecamo niz za jedno mjesto
			niz = (ZAINTERESOVAN*)realloc(niz, br_dogadjaja);
			niz[br_dogadjaja - 1].id = id;
			niz[br_dogadjaja - 1].br++;
		
		} 
		else //ako nadje
			niz[i].br++;
	
		if (i==(br_dogadjaja-1))
			printf("\nUkupno je %d ljudi zainteresovano ta ovaj dogadjaj\n", niz[br_dogadjaja].br);
		else printf("\nUkupno je %d ljudi zainteresovano ta ovaj dogadjaj\n", niz[i].br);
		
		//vracanje niza u datoteku
		dat_zainteresovani = fopen("../config files/Dogadjaji/zainteresovani_za_dogadjaj.txt", "w");
		fprintf(dat_zainteresovani, "%d", br_dogadjaja);
		for (int j = 0; j < br_dogadjaja; j++)
			fprintf(dat_zainteresovani, "\n%d %d", niz[i].id, niz[i].br);
		free(niz);
		fclose(dat_zainteresovani);
	}
}

int prestupna_godina(int godina) // 1 prestupna, 0 nije prestupna
{
	if ((godina % 4 == 0 && godina % 100 != 0) || (godina % 4 == 0 && godina % 400 == 0))
		return 1;
	else return 0;
}

int provjera_datuma(DATUM datum) // 1 ispravan datum, 0 nije ispravan
{

	if ((datum.mjesec == 1 || datum.mjesec == 3 || datum.mjesec == 5 || datum.mjesec == 7
		|| datum.mjesec == 8 || datum.mjesec == 10 || datum.mjesec == 12) && (datum.dan > 31 || datum.dan < 1))
	{
		printf("Pogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}

	else if ((datum.mjesec == 4 || datum.mjesec == 6 || datum.mjesec == 9 || datum.mjesec == 11) && (datum.dan > 30 || datum.dan < 1))
	{
		printf("Pogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && prestupna_godina(datum.godina)) && (datum.dan > 29 || datum.dan < 1))
	{
		printf("Pogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && !prestupna_godina(datum.godina)) && (datum.dan > 28 || datum.dan < 1))
	{
		printf("Pogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}
	else if (datum.mjesec > 12 || datum.mjesec < 1)
	{
		printf("Pogresno ste unijeli mjesec, pokusajte ponovo!\n");
		return 0;
	}
	else if (datum.godina < 1)
	{
		printf("Pogresno ste unijeli godinu, pokusajte ponovo!\n");
		return 0;
	}
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
		//popraviti unos

		printf("Mjesec: ");
		scanf("%d", &datum_check.mjesec);
		//popraviti unos

		printf("Godina: ");
		scanf("%d", &datum_check.godina);
		//popraviti unos

	} while (!provjera_datuma(datum_check));
	itoa(datum_check.dan, datum, 10);
	strcat(datum, ".");
	strcat(datum, itoa(datum_check.mjesec, mjesec, 10));
	strcat(datum, ".");
	strcat(datum, itoa(datum_check.godina, godina, 10));
	strcat(datum, ".");
	return 1;
}

int provjera_kategorije(char** arr, char* korisnicki_unos, int n, short* flag)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(arr[i], korisnicki_unos) == 0)
		{
			*flag = 1;
			return 1;
		}
	}
	*flag = 0;
	return 0;
}

void pisi_dogadjaje_filter(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	int flag_petlje = 0;
	char c[200] = {};
	char uneseni_datum[12] = {};
	FILE* kategorije_dat = NULL;
	char unos[20] = {};//korisnikov unos kategorije
	do
	{
		printf("\nUnesite K -> Ako zelite da filtrirate dogadjaje po nekoj kategoriji\n\tD -> Ako zelite da provjerite sta se desava za odredjen dan\n");
		scanf("\n%[^\n]s", c);
		while ((c[0] != 'K' && c[0] != 'k' && c[0] != 'D' && c[0] != 'd') || c[1] != 0)
		{
			printf("Nepostojeca opcija! Izaberite ponovo po cemu zelite filtrirati: \n");
			scanf("\n%[^\n]s", c);
		}
		if (c[0] == 'K' || c[0] == 'k')
		{
			char* kategorija[20];
			int br_kategorija;
			char ch;
			short flag1 = -1;
			if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r")) != NULL)
			{
				fscanf(kategorije_dat, "%d", &br_kategorija);

				for (int i = 0; i <= br_kategorija; i++)
					kategorija[i] = (char*)calloc(br_kategorija, sizeof(char));

				int i = 0;
				while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
					++i;
				fclose(kategorije_dat);
				printf("\nUnesite neku od postojecih kategorija:\n");
				for (int i = 0; i < br_kategorija; i++)
					printf("\t%d.%s\n", i + 1, kategorija[i]);
				printf("\n");

				do
				{
					if (flag1 == 0)
						printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n");
					printf("\nUnesite kategoriju: ");
					scanf("\n%[^\n]s", unos);
					strlwr(unos);
				} while (!provjera_kategorije(kategorija, unos, br_kategorija, &flag1));
			}
			else 
			{
				printf("\Greska prilikom otvaranja datoteke kategorije.txt\n");
			}
			flag_petlje = 1;
		}
		else if (c[0] == 'D' || c[0] == 'd')
		{
			unos_datuma(uneseni_datum);
			flag_petlje = 1;
		}
	} while (!flag_petlje);

	printf("\n****************************************************************************************************************************************************************************\n");

	if (c[0] == 'D' || c[0] == 'd')
	{
		char flag_datum = 0;
		for (int i = 0; i < br_dogadjaja; i++)
			if (!strcmp(uneseni_datum, lista_dogadjaja[i].datum))
			{
				ispisi_dogadjaj(&lista_dogadjaja[i]);
				flag_datum = 1;
			}
		if (!flag_datum) printf("\tNema desavanja u gradu %s... :(\n",uneseni_datum);
	}
	else if (c[0] == 'K' || c[0] == 'k')
	{
		char flag_kategorije = 0;
		for (int i = 0; i < br_dogadjaja; i++)
			if (!strcmp(unos, lista_dogadjaja[i].kategorija))
			{
				ispisi_dogadjaj(&lista_dogadjaja[i]);
				flag_kategorije = 1;
			}
		if (!flag_kategorije) printf("\tNema desavanja u kategoriji %s\n",unos);
	}
	printf("\n****************************************************************************************************************************************************************************\n");
}
