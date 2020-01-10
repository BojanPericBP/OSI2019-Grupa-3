#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "AdministrativnaAppHeader.h"




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
void unesi_komentar(int,char*);
void ispisi_komentar(int);
void prikazi_opis(DOGADJAJ*, int);
void zainteresovan_za_dogadjaj(DOGADJAJ*,int);
int provjera_kategorije(char**, char*, int, short*);
int unos_datuma(char*);
int provjera_datuma(DATUM);
int prestupna_godina(int);
void upisi_u_datoteku(DOGADJAJ*, int);
void zaglavlje_dogadjaja();
void unesi_username(char*);
int ucitaj_nickove(char**);
int pronadji_nick(char**, int, char*);

int pronadji_nick(char** username_arr, int duzina, char* trazeni_nick)
{
	for (int i = 0; i < duzina; i++)
		if (!strcmp(username_arr[i], trazeni_nick))
			return 1;
	return 0;
}

int ucitaj_nickove(char** username_arr)
{
	FILE* dat_komentari = fopen("../config files/Dogadjaji/komentari.txt", "r");
	if (!dat_komentari) { printf("Neuspjesno ucitavanje datoteke komentari.txt"); return 0; }
	else
	{
		char c = 0;
		int i = 0;
		int j = 0;
		while (c != EOF) // ide do kraja datoteke jer se moze vise puta pojaviti komentar za isti dogadjaj
		{
			if (i%20000==0 && i!=0)
			{
				username_arr = (char**)realloc(username_arr, i + 20000);
				for (int k = i; k < i + 20000; k++)
					username_arr[k] = (char*)calloc(21, sizeof(char));
			}

			for (int m = 0; m < 5; m++) //preskace ID i separator
				c = fgetc(dat_komentari);
			j = 0;
			while ((c = fgetc(dat_komentari)) != '|')
			{
				username_arr[i][j] = c;
				j++;
			}
			while ((c = fgetc(dat_komentari)) != 10 && c != EOF);
			i++;
		}
		fclose(dat_komentari);
		return i;
	}
}

void unesi_username(char* username)
{
	char** username_arr = (char**)calloc(20000, sizeof(char*));
	for (int i = 0; i < 20000; i++)
		username_arr[i] = (char*)calloc(21, sizeof(char));
	int duzina = ucitaj_nickove(username_arr);
	char temp_username[1000] = {};
	printf("\nUnesite korisnicko ime: \n");
	scanf("\n%[^\n]s",temp_username);
	while(strlen(temp_username) > 20 || pronadji_nick(username_arr,duzina,temp_username))
	{
		if(strlen(temp_username) > 20)printf("\nUnijeli ste predugo korisnicko ime. Unesite ponovo korisnicko ime:\n");
		else printf("\nUnijeli ste korisnicko ime koje vec postoji. Unesite ponovo korisnicko ime:\n");
		scanf("\n%[^\n]s", temp_username);
	}
	strcpy(username, temp_username);
}

int ucitaj_br_dogadjaja(FILE* dat_dogadjaji) //samo za datoteku dogadjaji.txt
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
		int j = 1; // 1 zato sto je u stringu "ostatak" prvi karakter separator |
		int t = 0;

		for (t = 0; ostatak[j] != '|'; j++, t++)
			lista_dogadjaja[i].naziv[t] = ostatak[j];
		lista_dogadjaja[i].naziv[t] = '\0'; j++;

		lista_dogadjaja[i].opis = ostatak[j];
		j += 2;
		for (t = 0; ostatak[j] != '|'; j++, t++)
			lista_dogadjaja[i].lokacija[t] = ostatak[j];
		lista_dogadjaja[i].lokacija[t] = '\0'; j++;

		for (t = 0; ostatak[j] != '|'; j++, t++)
			lista_dogadjaja[i].kategorija[t] = ostatak[j];
		lista_dogadjaja[i].kategorija[t] = '\0'; j++;

		for (t = 0; ostatak[j] != '|'; j++, t++)
			lista_dogadjaja[i].datum[t] = ostatak[j];
		lista_dogadjaja[i].datum[t] = '\0'; j++;

		for (t = 0; ostatak[j] != '|'; j++, t++)
			lista_dogadjaja[i].vrijeme[t] = ostatak[j];
		lista_dogadjaja[i].vrijeme[t] = '\0'; j++;

		lista_dogadjaja[i].komentari = ostatak[j++]; j++;
		lista_dogadjaja[i].preporucen = ostatak[j++];

		++i;
	}
}

void zaglavlje_dogadjaja()
{
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf(" IB  | Naziv dogadjaja               | Opis      | Lokacija                                          | Kategorija           | Datum      | Vrijeme | Komentari    | Preporucen\n");
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void ispisi_dogadjaj(DOGADJAJ* lista_dogadjaja)
{
	printf("%5d  %-30s  %-10s  %-50s  %-20s  %12s  %-8s  %-13s  %s\n",lista_dogadjaja->id,lista_dogadjaja->naziv, lista_dogadjaja->opis=='1'?"ima opis":"bez opisa" ,lista_dogadjaja->lokacija,lista_dogadjaja->kategorija,lista_dogadjaja->datum,lista_dogadjaja->vrijeme,lista_dogadjaja->komentari=='1'?"Ima komentar":"Nema komentar",lista_dogadjaja->preporucen=='1'?" Da":"");
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

	if (t.wDay > 9) strcat(temp_date, itoa(t.wDay, buffer, 10));
	else { strcat(temp_date, "0"); strcat(temp_date, itoa(t.wDay, buffer, 10)); }
	strcat(temp_date, ".");

	if (t.wMonth > 9) strcat(temp_date, itoa(t.wMonth, buffer, 10));
	else { strcat(temp_date, "0"); strcat(temp_date, itoa(t.wMonth, buffer, 10)); }
	strcat(temp_date, ".");

	strcat(temp_date, itoa(t.wYear, buffer, 10));
	strcat(temp_date, ".");
	char flag = 0;
	for (int i = 0; i < br_dogadjaja; i++)
		if (!strcmp(temp_date, lista_dogadjaja[i].datum))
		{
			flag++;
			if (flag == 1) zaglavlje_dogadjaja();
			ispisi_dogadjaj(&lista_dogadjaja[i]);
		}
	if (!flag) printf("\n\tNema desavanja u gradu danas... :(\n");
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

	if (t.wDay > 9) strcat(temp_day, itoa(t.wDay, buffer, 10));
	else { strcat(temp_day, "0"); strcat(temp_day, itoa(t.wDay, buffer, 10)); }

	if(t.wMonth > 9) strcat(temp_month, itoa(t.wMonth, buffer, 10));
	else { strcat(temp_month, "0"); strcat(temp_month, itoa(t.wMonth, buffer, 10)); }

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
	if (t.wDay > 9) strcat(temp_day, itoa(t.wDay, buffer, 10));
	else { strcat(temp_day, "0"); strcat(temp_day, itoa(t.wDay, buffer, 10)); }

	if (t.wMonth > 9) strcat(temp_month, itoa(t.wMonth, buffer, 10));
	else { strcat(temp_month, "0"); strcat(temp_month, itoa(t.wMonth, buffer, 10)); }

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
	printf("\nUnesite identifikacioni broj dogadjaja:");
	scanf("\n%[^\n]s",niz);
	while (niz[4] != 0 || (niz[0]<48 || niz[0]>57) || (niz[1] < 48 || niz[1]>57) || (niz[2] < 48 || niz[2]>57) || (niz[3] < 48 || niz[3]>57))
	{
		printf("\nPogresan unos. Unesite ponovo identifikacioni broj:");
		scanf("\n%[^\n]s", niz);
	}
	int id=((niz[0]-48)*1000)+((niz[1]-48)*100)+((niz[2]-48)*10)+(niz[3]-48);
	return id;
}

void prikazi_opis(DOGADJAJ* lista_dogadjaja,int br_dogadjaja)
{
	FILE* dat_opis = NULL;
	int id = unesi_id();
	DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, id);
	if (!trazeni_dogadjaj) 
		printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
	else if ((trazeni_dogadjaj->opis - 48)==0) 
		printf("\nDogadjaj sa unesenim identifikacionim brojem nema opis.\n");
	else
	{
		if ((dat_opis = fopen("../config files/Dogadjaji/opis_dogadjaja.txt", "r")) != NULL)
		{
			char c = 0;
			int temp_id = 0;
			printf("\nNaziv dogadjaja:\n%s\n", trazeni_dogadjaj->naziv);
			printf("\nOpis dogadjaja: \n");
			int br_slova = 0;
			while (c != EOF)
			{
				temp_id = 0;
				for (int i = 3; i >= 0; i--)
				{
					c = fgetc(dat_opis);
					temp_id += ((c - 48) * (int)pow(10, i));
				}
				c = fgetc(dat_opis); //da preskoci zapetu
				br_slova = 0;
				while ((c = fgetc(dat_opis)) != 10 && c != EOF)
				{
					if (temp_id == id) 
					{
						br_slova++;
						if (br_slova <= 160 || (br_slova > 160 && c != 32))
							printf("%c", c);
						else 
						{
							printf("\n"); 
							br_slova = 0;
						}
					}
				}
				if (temp_id == id) printf("\n");
			}
			fclose(dat_opis);
		}
		else 
			printf("Neuspjesno otvaranje datoteke opis_dogadjaja.txt");
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
		int br_slova = 0;
		while (c != EOF) // ide do kraja datoteke jer se moze vise puta pojaviti komentar za isti dogadjaj
		{
			temp_id = 0;
			for (int i = 3; i >=0; i--)
			{
				c = fgetc(dat_komentari);
				temp_id += ((c - 48)* (int)pow(10,i));
			}
			if (temp_id == id) { flag = 1; printf("\n"); }
			c = fgetc(dat_komentari); //da preskoci separator
			while ((c = fgetc(dat_komentari)) != '|') if (temp_id == id) { printf("%c", c); }
			if (temp_id == id) printf(" kaze: ");
			//c = fgetc(dat_komentari); //da preskoci separator
			br_slova = 0;
			while ((c = fgetc(dat_komentari)) != 10 && c != EOF)
			{
				if (temp_id == id)
				{
					br_slova++;
					if (br_slova <= 160 || (br_slova > 160 && c != 32))
						printf("%c", c);
					else
					{
						printf("\n");
						br_slova = 0;
					}
				}
			}
			if(temp_id==id) printf("\n");
		}
		if (!flag) printf("\nNije pronadjen komentar za dogadjaj sa unesenim identifikacionim brojem\n");//ako u dogadjaji.txt pise da ima komentar, a u komentari.txt nema
		fclose(dat_komentari);
	}
}

void unesi_komentar(int id, char* username)
{
	FILE* dat_komentari = fopen("../config files/Dogadjaji/komentari.txt", "a+");
	if (!dat_komentari) { printf("Neuspjesno ucitavanje datoteke komentari.txt"); return; }
	else
	{
		char kom[1000] = {};
		printf("\nUnesite komentar: ");
		scanf("\n%[^\n]s", kom);
		fprintf(dat_komentari, "\n%d|%s|%s", id, username,kom);
		fclose(dat_komentari);
	}
}

void zainteresovan_za_dogadjaj(DOGADJAJ* trazeni_dogadjaj,int id)
{
	FILE* dat_zainteresovani = fopen("../config files/Dogadjaji/zainteresovani_za_dogadjaj.txt", "r");
	if (!dat_zainteresovani) { printf("Neuspjesno ucitavanje datoteke zainteresovani_za_dogadjaj.txt"); return; }
	else
	{
		int br_dogadjaja=0;
		fscanf(dat_zainteresovani, "%d", &br_dogadjaja);
		int br_dogadjaja_backup = br_dogadjaja;
		ZAINTERESOVAN* niz = (ZAINTERESOVAN*)calloc(br_dogadjaja+1, sizeof(DOGADJAJ));

		// ucitavanje iz datoteke u memoriju
		for (int i = 0; i < br_dogadjaja; i++)
			fscanf(dat_zainteresovani, "%d %d", &niz[i].id, &niz[i].br);
		fclose(dat_zainteresovani); dat_zainteresovani = NULL;

		//pretraga u nizu
		char flag = 0;
		int i = 0; //brojac
		for (; i < br_dogadjaja && !flag; i++)
			if (niz[i].id == id) flag = 1;

		if (!flag) //ako ne nadje
		{
			br_dogadjaja++; //nema ga u nizu, pa se ukupan broj uvecava za 1
			niz[br_dogadjaja - 1].id = id;
			niz[br_dogadjaja - 1].br++;

		}
		else //ako nadje
			niz[i - 1].br++;
	
		printf("\nUspjesno ste potvrdili zainteresovanost za dogadjaj %s\n", trazeni_dogadjaj->naziv);
		//ispis
		if (i == (br_dogadjaja - 1)&&br_dogadjaja!=br_dogadjaja_backup)
		{
			if (niz[br_dogadjaja - 1].br == 1 || (niz[br_dogadjaja - 1].br % 10 ==1 && niz[br_dogadjaja - 1].br > 14))
				printf("\nUkupno je %d osoba zainteresovana za ovaj dogadjaj.\n", niz[br_dogadjaja - 1].br);
			else if(niz[br_dogadjaja - 1].br < 5 || (niz[br_dogadjaja - 1].br % 10 < 5 && niz[br_dogadjaja - 1].br % 10 > 0 && niz[br_dogadjaja - 1].br > 14))
				printf("\nUkupno su %d osobe zainteresovane za ovaj dogadjaj.\n", niz[br_dogadjaja - 1].br);
			else
				printf("\nUkupno je %d osoba zainteresovanih za ovaj dogadjaj.\n", niz[br_dogadjaja - 1].br);
		}
		else
		{
			if (niz[i - 1].br == 1 || (niz[i - 1].br % 10 == 1 && niz[i - 1].br > 14))
				printf("\nUkupno je %d osoba zainteresovana za ovaj dogadjaj.\n", niz[i - 1].br);
			else if (niz[i - 1].br < 5 || (niz[i - 1].br%10<5 && niz[i - 1].br % 10 > 0 && niz[i - 1].br>14))
				printf("\nUkupno su %d osobe zainteresovane za ovaj dogadjaj.\n", niz[i - 1].br);
			else
				printf("\nUkupno je %d osoba zainteresovanih za ovaj dogadjaj.\n", niz[i - 1].br);
		}
		
		//vracanje niza u datoteku
		dat_zainteresovani = fopen("../config files/Dogadjaji/zainteresovani_za_dogadjaj.txt", "w");
		fprintf(dat_zainteresovani, "%d", br_dogadjaja);
		for (int j = 0; j < br_dogadjaja; j++)
			fprintf(dat_zainteresovani, "\n%d %d", niz[j].id, niz[j].br);
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
		printf("\nUnijeli ste nepostojeci datum, unesite ponovo cijeli datum!\n\n");
		return 0;
	}

	else if ((datum.mjesec == 4 || datum.mjesec == 6 || datum.mjesec == 9 || datum.mjesec == 11) && (datum.dan > 30 || datum.dan < 1))
	{
		printf("\nUnijeli ste nepostojeci datum, unesite ponovo cijeli datum!\n\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && prestupna_godina(datum.godina)) && (datum.dan > 29 || datum.dan < 1))
	{
		printf("\nnijeli ste nepostojeci datum, unesite ponovo cijeli datum!\n\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && !prestupna_godina(datum.godina)) && (datum.dan > 28 || datum.dan < 1))
	{
		printf("\nUnijeli ste nepostojeci datum, unesite ponovo cijeli datum!\n\n");
		return 0;
	}
	else if (datum.mjesec > 12 || datum.mjesec < 1)
	{
		printf("\nUnijeli ste nepostojeci datum, unesite ponovo cijeli datum!\n\n");
		return 0;
	}
	else if (datum.godina < 2018)
	{
		printf("\nNema dogadjaja koji se desio prije 2018 godine, unesite ponovo cijeli datum!\n\n");
		return 0;
	}
	return 1;
}

int unos_datuma(char* datum)
{
	DATUM datum_check;
	char mjesec[3], godina[5];//bufferi za funkciju strcat
	char niz[1000] = {};
	do
	{
		printf("Dan: ");
		scanf("\n%[^\n]s", niz);
		while ((niz[1] != '\0' || niz[0] < 48 || niz[0]>57) && (niz[2]!='\0' || niz[0] < 48 || niz[0]>57 || niz[1] < 48 || niz[1]>57))
		{
			printf("Neispravan unos, unesite ponovo dan: ");
			scanf("\n%[^\n]s", niz);
		}
		if(niz[1]!='\0') datum_check.dan = (niz[0] - '0') * 10 + niz[1] - '0';
		else { datum_check.dan = niz[0] - '0'; }

		printf("Mjesec: ");
		scanf("\n%[^\n]s", niz);
		while ((niz[1] != '\0' || niz[0] < 48 || niz[0]>57) && (niz[2] != '\0' || niz[0] < 48 || niz[0]>57 || niz[1] < 48 || niz[1]>57))
		{
			printf("Neispravan unos, unesite ponovo mjesec: ");
			scanf("\n%[^\n]s", niz);
		}
		if (niz[1] != '\0') datum_check.mjesec = (niz[0] - '0') * 10 + niz[1] - '0';
		else datum_check.mjesec = niz[0] - '0';

		printf("Godina: ");
		scanf("\n%[^\n]s", niz);
		while (niz[4] != '\0' || niz[0] < 48 || niz[0]>57 || niz[1] < 48 || niz[1]>57 || niz[2] < 48 || niz[2]>57 || niz[3] < 48 || niz[3]>57)
		{
			printf("Niste unijeli sve cetiri cifre za godinu, unesite ponovo godinu: ");
			scanf("\n%[^\n]s", niz);
		}
		datum_check.godina = (niz[0] - '0') * 1000 + (niz[1] - '0') * 100 + (niz[2] - '0') * 10 + niz[3] - '0';
	} while (!provjera_datuma(datum_check));

	char buffer[5];

	if (datum_check.dan > 9) strcat(datum, itoa(datum_check.dan, buffer, 10));
	else { strcat(datum, "0"); strcat(datum, itoa(datum_check.dan, buffer, 10)); }
	strcat(datum, ".");

	if (datum_check.mjesec > 9) strcat(datum, itoa(datum_check.mjesec, buffer, 10));
	else { strcat(datum, "0"); strcat(datum, itoa(datum_check.mjesec, buffer, 10)); }
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
	char ch = 0;
	char uneseni_datum[12] = {};
	FILE* kategorije_dat = NULL;
	char unos[1000] = {};//korisnikov unos kategorije
	do
	{
		printf("\nUnesite K -> Ako zelite da filtrirate dogadjaje po nekoj kategoriji\n\tD -> Ako zelite da provjerite sta se desava za odredjen dan\n");
		ch = _getch();
		while (ch != 'K' && ch != 'k' && ch != 'D' && ch != 'd')
		{
			if (ch != 13) printf("Nepostojeca opcija! Izaberite ponovo po cemu zelite filtrirati: \n");
			ch = _getch();
		}
		if (ch == 'K' || ch == 'k')
		{
			char** kategorija;
			int br_kategorija;
			char ch;
			short flag1 = -1;
			if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r")) != NULL)
			{
				fscanf(kategorije_dat, "%d", &br_kategorija);

				kategorija = (char**)calloc(br_kategorija, sizeof(char*));
				for (int i = 0; i < br_kategorija; i++)
					kategorija[i] = (char*)calloc(21, sizeof(char));

				int i = 0;
				while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
					++i;
				fclose(kategorije_dat);
				printf("\nFILTRIRANJE PO KATEGORIJI");
				printf("\nUnesite neku od postojecih kategorija:\n");
				for (int i = 0; i < br_kategorija; i++)
					printf("\t%c %s\n", 254,kategorija[i]);
				printf("\n");

				do
				{
					if (flag1 == 0)
						printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n");
					printf("\nUnesite kategoriju: ");
					scanf("\n%[^\n]s", unos);
					strlwr(unos);
				} while (!provjera_kategorije(kategorija, unos, br_kategorija, &flag1));
				for (int i = 0; i < br_kategorija; i++)
					free(kategorija[i]);
				free(kategorija);
			}
			else 
			{
				printf("\nGreska prilikom otvaranja datoteke kategorije.txt\n");
			}
			flag_petlje = 1;
		}
		else if (ch == 'D' || ch == 'd')
		{
			printf("\nFILTRIRANJE PO DATUMU\n");
			unos_datuma(uneseni_datum);
			flag_petlje = 1;
		}
	} while (!flag_petlje);

	printf("\n*******************************************************************************************************************************************************************************\n");

	if (ch == 'D' || ch == 'd')
	{
		char flag_datum = 0;
		for (int i = 0; i < br_dogadjaja; i++)
			if (!strcmp(uneseni_datum, lista_dogadjaja[i].datum))
			{
				flag_datum++;
				if (flag_datum == 1) zaglavlje_dogadjaja();
				ispisi_dogadjaj(&lista_dogadjaja[i]);
			}
		if (!flag_datum) printf("\tNema desavanja u gradu %s.. :(\n",uneseni_datum);
	}
	else if (ch == 'K' || ch == 'k')
	{
		char flag_kategorije = 0;
		for (int i = 0; i < br_dogadjaja; i++)
			if (!strcmp(unos, lista_dogadjaja[i].kategorija))
			{
				flag_kategorije++;
				if (flag_kategorije == 1) zaglavlje_dogadjaja;
				ispisi_dogadjaj(&lista_dogadjaja[i]);
			}
		if (!flag_kategorije) printf("\tNema dogadjaja u kategoriji %s\n",unos);
	}
}

void upisi_u_datoteku(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	FILE* dat_dogadjaji = fopen("../config files/Dogadjaji/dogadjaji.txt", "w");
	fprintf(dat_dogadjaji, "%d %d", lista_dogadjaja[br_dogadjaja - 1].id, br_dogadjaja);
	for (int i = 0; i < br_dogadjaja; i++)
	{
		fprintf(dat_dogadjaji, "\n%d|%s|%c|%s|%s|%s|%s|%c|%c", lista_dogadjaja[i].id, lista_dogadjaja[i].naziv, lista_dogadjaja[i].opis, lista_dogadjaja[i].lokacija, lista_dogadjaja[i].kategorija,
			lista_dogadjaja[i].datum, lista_dogadjaja[i].vrijeme, lista_dogadjaja[i].komentari, lista_dogadjaja[i].preporucen);
	}
	fclose(dat_dogadjaji);
}
