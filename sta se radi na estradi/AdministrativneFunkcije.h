#pragma once
#pragma warning(disable : 4996)
#define MAX 20

#include<conio.h>
#include <stdlib.h>
#include<string>
#include <iostream>
#include <time.h>
#include "strukture.h"
#include "korisnickeFunkcije.h"

int uredi_dogadjaj();
int unos_korisnickih_podataka_admina(char admin_username[], char admin_pass[]);
int logovanje_admina(char admin_username[], char admin_pass[]);
int dodaj_dogadjaj(char*);
int unos_datuma(char*);
int prestupna_godina(int godina);
int provjera_datuma(DATUM datum);
int unos_vremena(char []);
int provjera_vremena(VRIJEME);

int provjera_naziva(char*,const int);
int brisanje_dogadjaja();
DOGADJAJ* trazi_dogadjaj(int, DOGADJAJ*,int);
DOGADJAJ* ucitaj_dogadjaje(int*,int*);
void sleep(unsigned int secs);

int unos_korisnickih_podataka_admina(char admin_username[], char admin_pass[])
{
	FILE* pristupni_podaci;		//Datoteka u kojoj se nalaze pristupni podaci za logovanje administratora na sistem
	
	char usernamecheck[MAX], passwordcheck[MAX], ch;	//za smjestanje pristupnih podataka iz daoteke

	ADMIN admin;

	for ( int i = 0; i < MAX; i++)
		admin.password[i] = 0;

	printf("\nKorisnicko ime: "); scanf("\n%[^\n]s", admin.username);
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
			{
				strcpy(admin_pass, admin.password);
				strcpy(admin_username, admin.username);
				return 1;
			}
	}
	else
		printf("Greska prilikom otvaranja datoteke u kojj se nalaze pristupni podaci administratora!\n");
	fclose(pristupni_podaci);
	
	return 0;
}

int logovanje_admina(char admin_username[], char admin_pass[])
{
	char c[500];
	char ch;
	int br_pokusaja = 2;  //broji pokusaja da se unesu tacni podaci
	while (br_pokusaja && !unos_korisnickih_podataka_admina(admin_username,admin_pass))
	{
		--br_pokusaja;

		printf("\nPorgesno korisnicko ime ili lozinka!\nUnesite 'e' za izlaz iz programa ili unesite 'p' za ponovni unos podataka!\n");
		ch = _getch();
		while (ch != 'p' && ch != 'P' && ch != 'e' && ch != 'E')
		{
			printf("Nepostojeca opcija!\nUnesite 'e' ili 'p': ");
			ch = _getch();
		}

		if (ch == 'e' || ch == 'E')
			exit(1);

		else if ((ch == 'p' || ch == 'P') && br_pokusaja)
		{
			printf("\nUPOZORENJE!\nOSTALO VAM JE JOS %d POKUSAJA!\n", br_pokusaja);
			continue;
		}
		else if (br_pokusaja == 0)
		{
			printf("\nPogresno ste unijeli pristupne podatke 5 puta za redom, ne mozete se prijaviti!");
			do
			{
				printf("\nUnesite 'e' za izlazak: ");
				ch = _getch();
			} while (ch != 'e' && ch != 'E');

			exit(1);
		}
	}
	
}


int dodaj_dogadjaj(char* username)
{
	int br_kategorija,id,br_dogadjaja,i;
	short flag1 = -1, flag2 = 0;
	char** kategorija;
	char datum[12] = "", vrijeme[6]= "", nova_kategorija[100],ch,naziv[100],mjesto[100],opis[1000];
	DOGADJAJ dogadjaj;
	VRIJEME vrijeme_provjera;//za provjeru da li je korisnik dobro unio vrijeme
	FILE* kategorije_dat,* dogadjaji_dat,* opis_dogadjaja_dat;
	
	if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "r+")) != NULL)//prepravio sam na r+
	{
		fscanf(dogadjaji_dat, "%d %d", &dogadjaj.id, &br_dogadjaja);
		dogadjaj.id++;
		br_dogadjaja++;

		if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r+")) != NULL)
		{
			fscanf(kategorije_dat, "%d", &br_kategorija);


			
			kategorija = (char**)calloc(br_kategorija, sizeof(char*));
			for (i = 0; i < br_kategorija; i++)
				kategorija[i] = (char*)calloc(20, sizeof(char));

			i = 0;
			while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
				++i;

			printf("\n\tUNOS KATEGORIJE\n________________________________________________________________\n");
			
			printf("\nPOSTOJECE KATEGORIJE:\n\n");
			for (i = 0; i < br_kategorija; i++)
				printf("\t%c %s\n", 254, kategorija[i]);
			printf("________________________________________________________________\n");

			printf("\nOdaberite:\n\tU->Unos postojece kategorije\n\tD->Dodavanje nove kategorije\n\n");
			
			do
				ch = _getch();
			while (ch != 'u' && ch != 'U' && ch != 'd' && ch != 'D');

			printf("___________________________________________________________________\n\n");
			printf("Ukucajte slovima naziv kategorije koju zelite unijeti!\n");
			printf("___________________________________________________________________\n\n");

			if (ch == 'u' || ch == 'U')
			{
				do
				{
					if (flag1 == 0)
						printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n\n");
					printf("Unesite kategoriju: ");
					scanf("\n%[^\n]s", dogadjaj.kategorija);
					strlwr(dogadjaj.kategorija);
				} while (!provjera_kategorije(kategorija, dogadjaj.kategorija, br_kategorija, &flag1));
				if (flag1)
					printf("Uspjesno ste unijeli kategoriju.\n");

			}
			else if (ch == 'd' || ch == 'D')
			{
				printf("Dodajte novu kategoriju: ");
				do
				{
					if (flag2)
					{
						printf("Kategorija vec postoji!\n");
						printf("Unesite ponovo kategoriju:\n");
					}
					scanf("\n%[^\n]s", nova_kategorija);
					strlwr(nova_kategorija);

				} while (provjera_naziva(nova_kategorija,20)==0 || provjera_kategorije(kategorija, nova_kategorija, br_kategorija, &flag2));

				fprintf(kategorije_dat, "%s\n", nova_kategorija);
				++br_kategorija;
				fseek(kategorije_dat, 0, SEEK_SET);
				fprintf(kategorije_dat, "%d", br_kategorija);
				strcpy(dogadjaj.kategorija, nova_kategorija);
				printf("Uspjesnos te unijeli kategoriju.\n\n");
			}
			fclose(kategorije_dat);

			printf("\nNAZIV DOGADJAJA:\n");
			do
			{
				printf("Unesite naziv dogadjaja: ");
				scanf("\n%[^\n]s", naziv);
			} while (provjera_naziva(naziv, 30) == 0);

			strcpy(dogadjaj.naziv, naziv);

			printf("\nMJESTO ODRZAVANJA DOGADJAJA:\n");
			do
			{
				printf("Unesite mjesto gdje se odrzava dogadjaj: ");
				scanf("\n%[^\n]s", mjesto);
			} while (provjera_naziva(mjesto, 50) == 0);
			strcpy(dogadjaj.lokacija, mjesto);
			
			printf("Unesite:\n\tK->za komentarisanje dogadjaja\n\tP->Da preskocite komentarisanje");
			do
				ch = _getch();
			while (ch != 'k' && ch != 'K' && ch != 'p' && ch != 'P');

			if (ch == 'K' || ch == 'k')
			{
				printf("\nDODAVANJE KOMENTARA");

				dogadjaj.komentari = '1';

				unesi_komentar(dogadjaj.id, username);
				printf("\nUspjesno ste unijeli komentar. \n");		
			}
			else if(ch == 'p' || ch == 'P')
				dogadjaj.komentari = '0';


			if ((opis_dogadjaja_dat = fopen("../config files/Dogadjaji/opis_dogadjaja.txt", "a")) == NULL)
			{
				printf("greska prilikom otvaranja konfiguracionog fajla!\nUnesite bilo koji znak za izlaz: ");
				ch = _getch();
				if (ch != 0)
					exit(1);
			}
			else
			{
				printf("\nOPIS DOGADJAJA:\n");
				printf("Unesite:\n\to->za unos opisa\n\tp->da preskocite ovaj korak\n");
				do
					ch = _getch();
				while (ch != 'o' && ch != 'O' && ch != 'p' && ch != 'P');

				if (ch == 'o' || ch == 'O')
				{
					printf("Opis: ");
					scanf("\n%[^\n]s", opis);
					fprintf(opis_dogadjaja_dat, "%d,%s\n", dogadjaj.id, opis);
					dogadjaj.opis = '1';
				}
				else if (ch == 'p' || ch == 'P')
					dogadjaj.opis = '0';

				do
				{
					printf("\nDa li zelite preporuciti ovaj dogadjaj drugim korisnicima?\nUnesite:\n\t1->DA\n\t0->NE\n");
					dogadjaj.preporucen = _getch();
					printf("%c", ch);
				} while (dogadjaj.preporucen != '1' && dogadjaj.preporucen != '0');
				

			}
			fclose(opis_dogadjaja_dat);

			printf("\nUNOS DATUMA:\n\n");
			unos_datuma(datum);
			strcpy(dogadjaj.datum, datum);
			printf("\nUNOS VREMENA:\n\n");
			unos_vremena(vrijeme);
			strcpy(dogadjaj.vrijeme, vrijeme);

			fseek(dogadjaji_dat, 0, SEEK_SET);
			fprintf(dogadjaji_dat, "%d %d", dogadjaj.id, br_dogadjaja);
			fseek(dogadjaji_dat, 0, SEEK_END);
			fprintf(dogadjaji_dat, "\n%d|%s|%c|%s|%s|%s|%s|%c|%c", dogadjaj.id, dogadjaj.naziv, dogadjaj.opis, dogadjaj.lokacija, dogadjaj.kategorija,
					dogadjaj.datum, dogadjaj.vrijeme, dogadjaj.komentari, dogadjaj.preporucen);
			for (i = 0; i < br_kategorija-1; i++)
				free(kategorija[i]);
			free(kategorija);
			fclose(dogadjaji_dat);
		}
		else
			printf("Greska u otvaranju datoteke kategorije.txt");
		
		fclose(dogadjaji_dat);
	}
	else
	printf("Greska prilikom otvaranja datoteke sa dogadjajima!\n");
	return 1;
}


int unos_vremena(char vrijeme[])
{
	VRIJEME time;
	char niz[1000] = {};
	char min[3];

	do
	{
		printf("U koliko sati: ");
		scanf("\n%[^\n]s", niz);

		while ((niz[1] != '\0' || niz[0] < 48 || niz[0]>57) && (niz[2] != '\0' || niz[0] < 48 || niz[0]>57 || niz[1] < 48 || niz[1]>57))
		{
			printf("Neispravan unos, unesite ponovo sate: ");
			scanf("\n%[^\n]s", niz);
		}

		if (niz[1] != '\0') time.sat = (niz[0] - '0') * 10 + niz[1] - '0';
		else { time.sat = niz[0] - '0'; }

		printf("U koliko minuta: ");
		scanf("\n%[^\n]s", niz);

		while ((niz[1] != '\0' || niz[0] < 48 || niz[0]>57) && (niz[2] != '\0' || niz[0] < 48 || niz[0]>57 || niz[1] < 48 || niz[1]>57))
		{
			printf("Neispravan unos, unesite ponovo minute: ");
			scanf("\n%[^\n]s", niz);
		}

		if (niz[1] != '\0') time.minute = (niz[0] - '0') * 10 + niz[1] - '0';
		else { time.minute = niz[0] - '0'; }

	} while (!provjera_vremena(time));

	if (time.sat > 9) 
		strcat(vrijeme, itoa(time.sat, min, 10));
	else
	{ 
		strcat(vrijeme, "0"); 
		strcat(vrijeme,
			itoa(time.sat, min, 10));
	}
	strcat(vrijeme, ":");

	if (time.minute > 9)
		strcat(vrijeme, itoa(time.minute, min, 10));
	else 
	{
		strcat(vrijeme, "0");
		strcat(vrijeme, itoa(time.minute, min, 10)); 
	}

	return 1;
}

int provjera_vremena(VRIJEME time)
{
	if ((time.sat > 23 || time.sat < 0) || (time.minute > 60 || time.minute < 0))
	{
		printf("Pogresno ste unijeli vrijeme, pokusajte ponovo!\n");
		return 0;
	}
		
	else return 1;
}


int provjera_naziva(char* arr,const int a)
{
	if (strlen(arr) > a)
	{
		printf("Dozvoljeno je maksimalno %d karaktera, pokusajte ponovo!\n",a);
		return 0;
	}

	return 1;
}


DOGADJAJ* ucitaj_dogadjaje(int *id,int *br_dogadjaja)
{
	FILE* dogadjaji_dat;
	DOGADJAJ* lista_dogadjaja;
	int i = 0;
	if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "r+")) != NULL)
	{
		fscanf(dogadjaji_dat, "%d %d", id, br_dogadjaja);
		lista_dogadjaja = (DOGADJAJ*)malloc(*br_dogadjaja * sizeof(DOGADJAJ));

		
		char temp_arr[200] = {};
		int i = 0;
		while (fscanf(dogadjaji_dat, "\n%[^\n]s", temp_arr) != EOF)
		{
			char* ostatak;
			lista_dogadjaja[i].id = strtol(temp_arr, &ostatak, 10); //implicitno kastovanje iz long u int //mozda ce praviti problem
			int j = 1; // 1 zato sto je u stringu "ostatak" prvi karakter zapeta
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
		
		fclose(dogadjaji_dat);
		return lista_dogadjaja;
	}
	else
	{
		printf("Neuspjesno otvaranje datoteke dogadjaji prilikom ucitavanja dogadjaja!\n");
		return 0;
	}
}

DOGADJAJ* trazi_dogadjaj(int id,DOGADJAJ* dogadjaji,int br_dogadjaja)
{
	DOGADJAJ *temp;
	for (int i = 0; i < br_dogadjaja; i++)
	{
		if (id == dogadjaji[i].id)
		{
			temp = &dogadjaji[i];
			return temp;
		}
	}
		return NULL;

}

int uredi_dogadjaj()
{
	int br_dogadjaja,id,id_back;
	char ch;
	char mjesto[100] = "";
	char naziv[200] = "";
	char datum[12] = "";
	char vrijeme[6] = "";
	DOGADJAJ* dogadjaji = ucitaj_dogadjaje(&id_back,&br_dogadjaja);
	DOGADJAJ* dogadjaj_check ,*pom;
	FILE* dogadjaji_dat;

	do
	{
		//printf("Unesite identifikacioni broj dogadjaja koji zelite da uredite: ");
		id = unesi_id();
	} while ((dogadjaj_check = trazi_dogadjaj(id, dogadjaji, br_dogadjaja)) == NULL);

	if (dogadjaji == NULL)
		printf("Ne postoji dogadjaj sa identifikacionim brojem %d!", id);

	printf("Unesite broj odgovarajuceg polja koji zelite da promjenite:\n ");
	printf("\n\t1->Naziv\n\t2->Lokacija\n\t3->Opis\n\t4->Kategorija\n\t5->Datum\n\t6->Vrijeme\n\t7->Preporucen dogadjaj ili ne\n\t0->Sacuvaj izmjene\n");
	
	do
	{
		do
		{
			printf("\nOdabir opcije [1-7]: ");
			ch = _getch();
			printf("%c", ch);
		} while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' && ch != '6' && ch != '7' && ch != '0');

		switch (ch)
		{
		case '1':
			
			do
			{
				printf("\nUnesite novi naziv dogadjaja: ");
				scanf("\n%[^\n]s", naziv);
			} while (provjera_naziva(naziv, 31) == 0);
			strcpy(dogadjaj_check->naziv, naziv);
			break;
		case '2':
			do
			{
				printf("\nUnesite mjesto gdje se odrzava dogadjaj: ");
				scanf("\n%[^\n]s", mjesto);
			} while (provjera_naziva(mjesto, 51) == 0);
			strcpy(dogadjaj_check->lokacija, mjesto);
			break;
		case '3':

			printf("\nDa li zelite da obrisete opis? [d,n]: ");
			ch = _getch();
			printf("%c\n", ch);
			while (ch != 'd' && ch != 'D' && ch != 'n' && ch != 'N')
			{
				printf("\nPogresan unos, unesite ponovo d ili n: ");

				ch = _getch();
				printf("%c\n", ch);
				
			}
			if (ch == 'd' || ch == 'D')
			{
				dogadjaj_check->opis = '0';
			}

			break;
		case '4':
			FILE * kategorije_dat;
			if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r+")) != NULL)
			{
				short flag1 = -1, flag2 = 0;
				int br_kategorija;
				char* kategorija[20], nova_kategorija[100];

				fscanf(kategorije_dat, "%d", &br_kategorija);

				for (int i = 0; i <= br_kategorija; i++)
					kategorija[i] = (char*)calloc(br_kategorija, sizeof(char));

				int i = 0;
				while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
					++i;

				fscanf(kategorije_dat, "%d", &br_kategorija);
				printf("\n\tUNOS KATEGORIJE\n\n");
				printf("Odaberite:\n\tU->Unos postojecu kategoriju\n\tD->Dodavanje nove kategorije\n\n");
				printf("\n\tPOSTOJECE KATEGORIJE:\n\n");
				for (int i = 0; i < br_kategorija; i++)
					printf("\t%c %s\n", 254, kategorija[i]);
				printf("\n");

				do
					ch = _getch();
				while (ch != 'u' && ch != 'U' && ch != 'd' && ch != 'D');

				if (ch == 'u' || ch == 'U')
				{
					do
					{
						if (flag1 == 0)
							printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n");
						printf("Unesite kategoriju: ");
						scanf("\n%[^\n]s", dogadjaj_check->kategorija);
						strlwr(dogadjaj_check->kategorija);
					} while (!provjera_kategorije(kategorija, dogadjaj_check->kategorija, br_kategorija, &flag1));

					if (flag1)
						printf("Uspjesnos te unijeli kategoriju.\n");

				}
				else if (ch == 'd' || ch == 'D')
				{
					printf("Dodajte novu kategoriju: ");
					do
					{
						if (flag2)
						{
							printf("Kategorija vec postoji!\n");
							printf("Unesite ponovo kategoriju:\n");
						}
						scanf("\n%[^\n]s", nova_kategorija);
						strlwr(nova_kategorija);

					} while (provjera_naziva(nova_kategorija,20)==0 || provjera_kategorije(kategorija, nova_kategorija, br_kategorija, &flag2));
					
					fprintf(kategorije_dat, "%s\n", nova_kategorija);
					++br_kategorija;
					fseek(kategorije_dat, 0, SEEK_SET);
					fprintf(kategorije_dat, "%d", br_kategorija);
				}
				
				fclose(kategorije_dat);
			}
			else
				printf("Greska prilikom otvaranja datotege za kategorije!\n\nUnesite bilo sta za izlaz iz programa: ");

			break;
		case '5':
			printf("\n");
			
			unos_datuma(datum);
			strcpy(dogadjaj_check->datum, datum);
			break;
		case '6':
			printf("\n");
			unos_vremena(vrijeme);
			strcpy(dogadjaj_check->vrijeme, vrijeme);
			break;
		case '7':
			do
			{
				printf("\nDa li zelite preporuciti ovaj dogadjaj drugim korisnicima?\nunesite:\n\t1->DA\n\t0->NE\n");
				dogadjaj_check->preporucen = _getch();
			} while (dogadjaj_check->preporucen != '1' && dogadjaj_check->preporucen != '0');
			break;
		}
	} while (ch != '0');

	int i = 0;
	if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "w")) != NULL)
	{
		fprintf(dogadjaji_dat, "%d %d\n", id_back, br_dogadjaja);
		while (i<br_dogadjaja)
		{
			fprintf(dogadjaji_dat, "%d|%s|%c|%s|%s|%s|%s|%c|%c\n", dogadjaji[i].id, dogadjaji[i].naziv, dogadjaji[i].opis, dogadjaji[i].lokacija, dogadjaji[i].kategorija,
				dogadjaji[i].datum, dogadjaji[i].vrijeme, dogadjaji[i].komentari, dogadjaji[i].preporucen);
			i++;
		}
		fclose(dogadjaji_dat);
	}
	else
		printf("greska prilikom otvaranja datoteke dogadjajji prilikom cuvanja rezultata!\nUnesite bilos ta za izlaz: ");

	free(dogadjaji);
	return 1;
}

int brisi_kategoriju()
{
	FILE* kategorije_dat;
	char** kategorija;
	int br_kategorija,i;
	char ch,buff_kategorija[500];
	short flag1 = -1, flag_brisi = 0;
	DOGADJAJ* dogadjaj;
	int br_dogadjaja,id;

	dogadjaj = ucitaj_dogadjaje(&id, &br_dogadjaja);
	if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r")) != NULL)
	{
		fscanf(kategorije_dat, "%d", &br_kategorija);
		kategorija = (char**)calloc(br_kategorija, sizeof(char*));
		for (int i = 0; i < br_kategorija; i++)
			kategorija[i] = (char*)calloc(20, sizeof(char));

		i = 0;
		while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
			++i;

		printf("\nPOSTOJECE KATEGORIJE:\n\n");
		for (i = 0; i < br_kategorija; i++)
			printf("\t%c %s\n", 254, kategorija[i]);
		printf("\n");
		printf("Odaberite:\n\tU->Unos kategorije koju zelite obrisati.\n\tO->Ukoliko zelite odustati od brisanja kategorije\n\n");
		printf("Unos:");
		do
		{
			ch = _getch();
			printf("%c\n", ch);
		}

		while (ch != 'u' && ch != 'U' && ch != 'o' && ch != 'O');

		if (ch == 'o' || ch == 'O')
		{
			fclose(kategorije_dat);
			return 1;
		}

		else if (ch == 'e' || ch == 'E')
		{
			fclose(kategorije_dat);
			exit(1);

		}

		else if (ch == 'u' || ch == 'U')
		{
			do
			{
				if (flag1 == 0)
					printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n");
				printf("Unesite kategoriju: ");
				scanf("\n%[^\n]s", buff_kategorija);
				strlwr(buff_kategorija);
			} while (!provjera_kategorije(kategorija, buff_kategorija, br_kategorija, &flag1));


			for (i = 0; i < br_dogadjaja; i++)
			{
				if (strcmp(buff_kategorija, dogadjaj[i].kategorija) == 0)
				{
					printf("Nije moguce obrisati kategoriju jer postoje neki dogadjaji sa ovom kategorijom!\n");
					flag_brisi = 1;
					break;
				}
			}
			if (flag_brisi == 0)
			{

				for (i = 0; i < br_kategorija; i++)
				{
					if (strcmp(kategorija[i], buff_kategorija) == 0)
					{

						free(kategorija[i]);
						kategorija[i] = NULL;
						br_kategorija--;
						flag_brisi = 0;
						fseek(kategorije_dat, 0, SEEK_SET);
						fprintf(kategorije_dat, "%d\n", br_kategorija);
						printf("Uspjesno ste brisali kategoriju.\n");
						break;
					}
				}
			}
		
			fclose(kategorije_dat);
		}

		if (flag_brisi == 0)
		{
			if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "w+")) != NULL)
			{
				fprintf(kategorije_dat, "%d\n", br_kategorija);
				for (i = 0; i <= br_kategorija; i++)
					if (kategorija[i] != NULL)
					{
						fprintf(kategorije_dat, "%s\n", kategorija[i]);
					}
				for (i = 0; i < br_kategorija; i++)
					if (kategorija[i] != 0)
					{
						free(kategorija[i]);
					}
				free(kategorija);
				fclose(kategorije_dat);
			}
		}

	}
	else
		printf("Greska prilikom otvaranja datoteke, unesite bilos ta za izlazak!");

	
	return 1;
}

int brisanje_dogadjaja()
{
	char id;
	int br_dogadjaja,id_dogadjaja;
	DOGADJAJ* lista_dogadjaja, *temp;
	FILE* dogadjaji_dat;

	if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "r")) != NULL)
	{
		fscanf(dogadjaji_dat, "%d %d", &id_dogadjaja, &	br_dogadjaja);
		lista_dogadjaja = (DOGADJAJ*)malloc(br_dogadjaja * sizeof(DOGADJAJ));
		
		char temp_arr[200] = {};
		int i = 0;
		while (fscanf(dogadjaji_dat, "\n%[^\n]s", temp_arr) != EOF)
		{
		
			char* ostatak;
			lista_dogadjaja[i].id = strtol(temp_arr, &ostatak, 10); //implicitno kastovanje iz long u int //mozda ce praviti problem
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
		fclose(dogadjaji_dat);
		char id_key[200] = {};
		int id_temp;
		printf("Unesite identifikacioni broj dogadjaja koji zelite da obrisete: ");
		scanf("\n%[^\n]s", id_key);
		id_temp = atoi(id_key);
		temp = trazi_dogadjaj(id_temp, lista_dogadjaja, br_dogadjaja);
		while ((temp = trazi_dogadjaj(id_temp, lista_dogadjaja, br_dogadjaja)) == NULL)
		{
			printf("Ne postoji dogadjaj sa identifikacionim brojem koji ste unijeli.\nUnesite ponovo identifikacioni broj: ");
			scanf("\n%[^\n]s", id_key);
			id_temp = atoi(id_key);
		}

		if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "w")) != NULL)
		{
			fprintf(dogadjaji_dat, "%d %d", id_dogadjaja, br_dogadjaja - 1);

			for (int i = 0; i < br_dogadjaja; i++)
			{
				if (id_temp != lista_dogadjaja[i].id)
					fprintf(dogadjaji_dat, "\n%d|%s|%c|%s|%s|%s|%s|%c|%c\n", lista_dogadjaja[i].id, lista_dogadjaja[i].naziv, lista_dogadjaja[i].opis, lista_dogadjaja[i].lokacija, lista_dogadjaja[i].kategorija,
						lista_dogadjaja[i].datum, lista_dogadjaja[i].vrijeme, lista_dogadjaja[i].komentari, lista_dogadjaja[i].preporucen);
			}
		}
		free(lista_dogadjaja);
		fclose(dogadjaji_dat);
		printf("\nUspjesnos te izbrisali dogadjaj!\n\n");
	}
	else
		printf("greska prilikom otvaradnja datoteke dogadjaji prilikom brisanja dogadjaja\n");

	return 0;
}

void sleep(unsigned int* secs)
{
	unsigned int retTime = time(0) + *secs;  
	while (time(0) < retTime);
}

