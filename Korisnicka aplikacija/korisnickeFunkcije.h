#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

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

typedef struct zainteresovan
{
	int id, br;
}ZAINTERESOVAN;

int ucitaj_br_dogadjaja(FILE*);
void ucitaj_dogadjaje_iz_datoteke(FILE*,DOGADJAJ*,int);
void ispisi_dogadjaj(DOGADJAJ*); //pomocna funkcija, koja ispisuje samo 1 dogadjaj
void svi_dogadjaji(DOGADJAJ*,int);
void preporuceni_dogadjaji(DOGADJAJ*,int);
void danasnji_dogadjaji(DOGADJAJ*,int);
void prosli_dogadjaji(DOGADJAJ*,int);
void buduci_dogadjaji(DOGADJAJ*,int);


int unesi_id();
DOGADJAJ* trazi_dogadjaj_id(DOGADJAJ*,int,int);
void pisi_dogadjaje_filter(DOGADJAJ*, char*);
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

void danasnji_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja) 
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
		

		ZAINTERESOVAN* niz = (ZAINTERESOVAN*)calloc(4, sizeof(ZAINTERESOVAN));

		// ucitavanje iz datoteke u memoriju
		for (int i = 0; i < br_dogadjaja; i++)
			fscanf(dat_zainteresovani, "%d %d", &niz[0].id, &niz[0].br);
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
