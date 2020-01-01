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
	char naziv[31], opis, lokacija[51], kategorija[20], datum[12], vrijeme[6], komentari, preporucen;
}DOGADJAJ;

int uredi_dogadjaj();
int unos_korisnickih_podataka_admina();
int logovanje_admina();
int dodaj_dogadjaj();
int unos_datuma(char*);
int prestupna_godina(int godina);
int provjera_datuma(DATUM datum);
int unos_vremena(char []);
int provjera_vremena(VRIJEME);
int provjera_kategorije(char**,char*,int,short*);
int provjera_nove_kategorije(char*);
int provjera_naziva(char*,const int);
DOGADJAJ* trazi_dogadjaj(int, DOGADJAJ*,int);
DOGADJAJ* ucitaj_dogadjaje(int*,int*);
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
	int br_kategorija,id,br_dogadjaja;
	short flag1 = -1, flag2 = 0;
	char** kategorija;
	char datum[12] = "", vrijeme[6], nova_kategorija[100],ch,naziv[100],mjesto[100],opis[1000];
	DOGADJAJ dogadjaj;
	VRIJEME vrijeme_provjera;//za provjeru da li je korisnik dobro unio vrijeme
	FILE* kategorije_dat,* dogadjaji_dat,* opis_dogadjaja_dat;
	//char* kategorija[20];	//moram dealocirati nekada negdje
	
	if ((dogadjaji_dat = fopen("../config files/Dogadjaji/dogadjaji.txt", "r+")) != NULL)//prepravio sam na r+
	{
		fscanf(dogadjaji_dat, "%d %d", &dogadjaj.id, &br_dogadjaja);
		dogadjaj.id++;
		br_dogadjaja++;

		if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "r+")) != NULL)
		{
			fscanf(kategorije_dat, "%d", &br_kategorija);


			
			kategorija = (char**)calloc(br_kategorija, sizeof(char*));
			for (int i = 0; i < br_kategorija; i++)
				kategorija[i] = (char*)calloc(20, sizeof(char));

			int i = 0;
			while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
				++i;

			printf("\n\tUNOS KATEGORIJE\n\n");
			printf("Odaberite:\n\tU->Unos postojecu kategoriju\n\tD->Dodavanje nove kategorije\n\n");
			printf("\n\tPOSTOJECE KATEGORIJE:\n\n");
			for (int i = 0; i < br_kategorija; i++)
				printf("\t%d.%s\n", i + 1, kategorija[i]);
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
					scanf("\n%[^\n]s", dogadjaj.kategorija);
					strlwr(dogadjaj.kategorija);
				} while (!provjera_kategorije(kategorija, dogadjaj.kategorija, br_kategorija, &flag1));
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

				} while (!provjera_nove_kategorije(nova_kategorija) || provjera_kategorije(kategorija, nova_kategorija, br_kategorija, &flag2));

				fprintf(kategorije_dat, "%s\n", nova_kategorija);
				++br_kategorija;
				fseek(kategorije_dat, 0, SEEK_SET);
				fprintf(kategorije_dat, "%d", br_kategorija);
				strcpy(dogadjaj.kategorija, nova_kategorija);
				printf("Uspjesnos te unijeli kategoriju.\n\n");
			}
			fclose(kategorije_dat);

			printf("NAZIV DOGADJAJA:\n");
			do
			{
				printf("Unesite naziv dogadjaja: ");
				scanf("\n%[^\n]s", naziv);
			} while (provjera_naziva(naziv, 31) == 0);

			strcpy(dogadjaj.naziv, naziv);

			do
			{
				printf("Unesite mjesto gdje se odrzava dogadjaj: ");
				scanf("\n%[^\n]s", mjesto);
			} while (provjera_naziva(mjesto, 51) == 0);
			strcpy(dogadjaj.lokacija, mjesto);
			

			dogadjaj.komentari = 0;


			if ((opis_dogadjaja_dat = fopen("../config files/Dogadjaji/opis_dogadjaja.txt", "a")) == NULL)
			{
				printf("greska prilikom otvaranja konfiguracionog fajla!\nUnesite bilo koji znak za izlaz: ");
				ch = _getch();
				if (ch != 0)
					exit(1);
			}
			else
			{
				printf("UNOS DOGADJAJA:\n");
				printf("Unesite:\n\to->za unos opisa\n\tp->da preskocite ovaj korak\n");
				do
					ch = _getch();
				while (ch != 'o' && ch != 'O' && ch != 'p' && ch != 'P');

				if (ch == 'o' || ch == 'O')
				{
					scanf("\n%[^\n]s", opis);
					fprintf(opis_dogadjaja_dat, "%d,%s\n", dogadjaj.id, opis);
					dogadjaj.opis = 1;
				}
				else if (ch == 'p' || ch == 'P')
					dogadjaj.opis = 0;

				do
				{
					printf("da li zelite preporuciti ovaj dogadjaj drugim korisnicima?\nunesite:\n\t1->DA\n\t0->NE\n");
					dogadjaj.preporucen = _getch();
				} while (dogadjaj.preporucen != '1' && dogadjaj.preporucen != '0');
				

			}
			fclose(opis_dogadjaja_dat);

			printf("UNOS DATUMA:\n\n");
			unos_datuma(datum);
			strcpy(dogadjaj.datum, datum);
			unos_vremena(vrijeme);
			strcpy(dogadjaj.vrijeme, vrijeme);

			fseek(dogadjaji_dat, 0, SEEK_SET);
			fprintf(dogadjaji_dat, "%d %d\n", dogadjaj.id, br_dogadjaja);
			fseek(dogadjaji_dat, 0, SEEK_END);
			fprintf(dogadjaji_dat, "%d,%s,%d,%s,%s,%s,%s,%d,%c\n", dogadjaj.id, dogadjaj.naziv, dogadjaj.opis, dogadjaj.lokacija, dogadjaj.kategorija,
				dogadjaj.datum, dogadjaj.vrijeme, dogadjaj.komentari,dogadjaj.preporucen);
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

int unos_datuma(char* datum1)
{
	DATUM datum_check;
	char datum[500];
	char mjesec[3], godina[5];
	do
	{
		
		printf("Dan (01): ");
		scanf("\n%[^\n]s", datum);
		while ((datum[1] != '\0' || datum[0] < 48 || datum[0] > 57) && (datum[2] != '\0' || datum[0]<48 || datum[0] > 57 || datum[1] < 48 || datum[1] > 57))
		{
			printf("Neispravan unos, unesite dan ponovo: ");
			scanf("\n%[^\n]s", datum);
		}
		datum_check.dan = (datum[0] - '0') * 10 + datum[1] - '0';
		
		printf("Mjesec: ");
		scanf("\n%[^\n]s", datum);
		while ((datum[1] != '\0' || datum[0] < 48 || datum[0] > 57) && (datum[2] != '\0' || datum[0] < 48 || datum[0] > 57 || datum[1] < 48 || datum[1] > 57))
		{
			printf("Neispravan unos, unesite mjesec ponovo: ");
			scanf("\n%[^\n]s", datum);
		}
		datum_check.mjesec = (datum[0] - '0') * 10 + datum[1] - '0';
		printf("Godina: ");
		scanf("\n%[^\n]s", datum);
		while (datum[4] != '\0' || datum[0] < 48 || datum[0]>57 || datum[1] < 48 || datum[1]>57 || datum[2] < 48 || datum[2]>57 || datum[3] < 48 || datum[3]>57)
		{
			printf("Niste unijeli 4 ciffre unesie ponovo: ");
			scanf("\n%[^\n]s", datum);
		}
		datum_check.godina = (datum[0] - '0') * 1000 + (datum[1] - '0') * 100 + (datum[2] - '0') * 10 + datum[3] - '0';

	} while (!provjera_datuma(datum_check));
	itoa(datum_check.dan, datum1,10);
	strcat(datum1, ".");
	strcat(datum1, itoa(datum_check.mjesec, mjesec, 10));
	strcat(datum1, ".");
	strcat(datum1, itoa(datum_check.godina, godina, 10));
	strcat(datum1, ".");
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
	 {
		 printf("Pogresno ste unijeli dan, pokusajte ponovo!\n");
		 return 0;
	 }
	
	else if ((datum.mjesec == 4 || datum.mjesec == 6 || datum.mjesec == 9 || datum.mjesec == 11) && (datum.dan > 30 || datum.dan < 1))
	{
		printf("\nnPogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && prestupna_godina(datum.godina)) && (datum.dan > 29 || datum.dan <1))
	{
		printf("\nPogresno ste unijeli dan, pokusajte ponovo!\n");
		return 0;
	}
	else if ((datum.mjesec == 2 && !prestupna_godina(datum.godina)) && (datum.dan > 28 || datum.dan < 1))
	{
		printf("\nPogresno ste unijelidatum, pokusajte ponovo!\n");
		return 0;
	}
	 else if (datum.mjesec > 12 || datum.mjesec < 1)
	 {
		 printf("\nPogresno ste unijelidatum, pokusajte ponovo!\n");
		 return 0;
	 }
	 else if (datum.godina < 2019)
	 {
		 printf("Godina ne moze unijeti dogadjaj koji se desio prije 2019. godine, pokusajte ponovo!\n");
		 return 0;
	 }
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
		scanf("%d", &time.minute);
	} while (!provjera_vremena(time));
	char min[3];
	itoa(time.sat, vrijeme, 10);
	strcat(vrijeme, ":");
	strcat(vrijeme, itoa(time.minute, min, 10));
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

int provjera_kategorije(char** arr,char* korisnicki_unos,int n,short* flag)
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

int provjera_nove_kategorije(char* kategorija)
{
	int i;
	for ( i = 0; i < strlen(kategorija); i++);
	if (i > 20)
	{
		printf("Kategorija mora imati manje od 20 karaktera!\nUnesite ponovo: ");
		return 0;
	}
	return 1;
}

int provjera_naziva(char* arr,const int a)
{
	int i;
	for (i = 0; i < strlen(arr); i++);
	if (i > a)
	{
		printf("Dozvoljeno je maksimalno 30 karaktera, pokusajte ponovo!\n");
		return 0;
	}

	return 1;
}

int unesi_id()
{
	char  niz[500] = {};
	printf("\nUnesite id dogadjaja:");
	scanf("\n%[^\n]s", niz);
	while (niz[4] != 0 || (niz[0] < 48 || niz[0]>57) || (niz[1] < 48 || niz[1]>57) || (niz[2] < 48 || niz[2]>57) || (niz[3] < 48 || niz[3]>57))
	{
		printf("\nPogresan unos. Unesite ponovo:");
		scanf("\n%[^\n]s", niz);
	}
	int id = ((niz[0] - 48) * 1000) + ((niz[1] - 48) * 100) + ((niz[2] - 48) * 10) + (niz[3] - 48);
	return id;
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

		//-------------------------
		char temp_arr[200] = {};
		int i = 0;
		while (fscanf(dogadjaji_dat, "\n%[^\n]s", temp_arr) != EOF)
		{
			char* ostatak;
			lista_dogadjaja[i].id = strtol(temp_arr, &ostatak, 10); //implicitno kastovanje iz long u int //mozda ce praviti problem
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
	DOGADJAJ* dogadjaji = ucitaj_dogadjaje(&id_back,&br_dogadjaja);
	DOGADJAJ* dogadjaj_check ,*pom;
	FILE* dogadjaji_dat;

	do
	{
		printf("Unesite identifikacioni broj dogadjaja koji zelite da uredite: ");
		id = unesi_id();
	} while ((dogadjaj_check = trazi_dogadjaj(id, dogadjaji, br_dogadjaja)) == NULL);

	if (dogadjaji == NULL)
	{
		printf("Ne postoji dogadjaj sa identifikacionim brojem %d!", id);
		//bilo sta za exit
	}
	printf("Unesite broj odgovarajuceg polja koji zelite da promjenite:\n ");
	printf("\n\t1->Naziv\n\t2->Lokacija\n\t3->opis\n\t4->Kategorija\n\t5->Datum\n\t6->Vrijeme\n\t7->Preporucen dogadjaj ili ne\n\t0->Sacuvaj i izadji\n");
	
	do
	{
		do
		{
			printf("Unos: ");
			ch = _getch();
		} while (ch != '1' && ch != '2' && ch != '3' && ch != '4' && ch != '5' && ch != '6' && ch != '7' && ch != '0');

		switch (ch)
		{
		case '1':
			char naziv[200];
			//strcpy(dogadjaj_check->naziv, "");
			do
			{
				printf("\nUnesite novi naziv dogadjaja: ");
				scanf("\n%[^\n]s", naziv);
			} while (provjera_naziva(naziv, 31) == 0);
			strcpy(dogadjaj_check->naziv, naziv);
			break;
		case '2':
			char mjesto[100];
			do
			{
				printf("Unesite mjesto gdje se odrzava dogadjaj: ");
				scanf("\n%[^\n]s", mjesto);
			} while (provjera_naziva(mjesto, 51) == 0);
			strcpy(dogadjaj_check->lokacija, mjesto);
			break;
		case '3':

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
					printf("\t%d.%s\n", i + 1, kategorija[i]);
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

					} while (!provjera_nove_kategorije(nova_kategorija) || provjera_kategorije(kategorija, nova_kategorija, br_kategorija, &flag2));
					
					fprintf(kategorije_dat, "%s\n", nova_kategorija);
					++br_kategorija;
					fseek(kategorije_dat, 0, SEEK_SET);
					fprintf(kategorije_dat, "%d", br_kategorija);
				}
				fclose(kategorije_dat);
			}
			else
			{
				printf("Greska prilikom otvaranja datotege za kategorije!\n\nUnesite bilo sta za izlaz iz programa: ");
				//bilos ta za izlaz iz programa
			}
			break;
		case '5':
			char datum[12];
			unos_datuma(datum);
			strcpy(dogadjaj_check->datum, datum);
			break;
		case '6':
			char vrijeme[6];
			unos_vremena(vrijeme);
			strcpy(dogadjaj_check->vrijeme, vrijeme);
			break;
		case '7':
			do
			{
				printf("da li zelite preporuciti ovaj dogadjaj drugim korisnicima?\nunesite:\n\t1->DA\n\t0->NE\n");
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
			fprintf(dogadjaji_dat, "%d,%s,%c,%s,%s,%s,%s,%c,%c\n", dogadjaji[i].id, dogadjaji[i].naziv, dogadjaji[i].opis, dogadjaji[i].lokacija, dogadjaji[i].kategorija,
				dogadjaji[i].datum, dogadjaji[i].vrijeme, dogadjaji[i].komentari, dogadjaji[i].preporucen);
			i++;
		}
		fclose(dogadjaji_dat);
	}
	else {
		printf("greska prilikom otvaranja datoteke dogadjajji prilikom cuvanja rezultata!\nUnesite bilos ta za izlaz: ");
		//bio sta za izlaz
	}
	return 1;
}

int brisi_kategoriju()
{
	FILE* kategorije_dat;
	char** kategorija;
	int br_kategorija;
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

		int i = 0;
		while (fscanf(kategorije_dat, "\n%[^\n]s", kategorija[i]) != EOF)
			++i;


		printf("\n\tUNOS KATEGORIJE\n\n");
		printf("Odaberite:\n\tU->Unos kategorije koju zelite obrisati.\n\tE->Izalz iz programa\n\tM->Povratak na glavni meni\n\n");
		printf("\nPOSTOJECE KATEGORIJE:\n\n");
		for (int i = 0; i < br_kategorija; i++)
			printf("\t%d.%s\n", i + 1, kategorija[i]);
		printf("\n");
		printf("Unos:");
		do
		{
			ch = _getch();
			printf("%c\n", ch);
		}
	
		while (ch != 'u' && ch != 'U' && ch != 'e' && ch != 'E' && ch != 'm' && ch != 'M');

		if (ch == 'u' || ch == 'U')
		{
			do
			{
				if (flag1 == 0)
					printf("Kategorija koju ste unijeli ne postoji, pokusajte ponovo!\n");
				printf("Unesite kategoriju: ");
				scanf("\n%[^\n]s", buff_kategorija);
				strlwr(buff_kategorija);
			} while (!provjera_kategorije(kategorija, buff_kategorija, br_kategorija, &flag1));


			for (int i = 0; i < br_kategorija; i++)
			{
				if (strcmp(buff_kategorija, dogadjaj[i].kategorija) == 0)
				{
					printf("Nije moguce obrisati kategoriju jer postoje neki dogadjaji sa ovom kategorijom!\n");
					flag_brisi = 1;
					break;
				}
			}

			for (int i = 0; i < br_kategorija; i++)
			{
				if ((strcmp(kategorija[i], buff_kategorija) == 0) && flag_brisi == 0)
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
			fclose(kategorije_dat);
		}

		if ((kategorije_dat = fopen("../config files/Dogadjaji/kategorije.txt", "w+")) != NULL)
		{
			fprintf(kategorije_dat, "%d\n", br_kategorija);
			for (int i = 0; i <= br_kategorija; i++)
				if (kategorija[i] != NULL)
				{
					fprintf(kategorije_dat, "%s\n", kategorija[i]);
				}
			fclose(kategorije_dat);
		}
		else return 0;
	}
	else
	{
		printf("Greska prilikom otvaranja datoteke, unesite bilos ta za izlazak!");
		//bilo sta za izlaz
	}
	return 1;
}

void sleep(unsigned int* secs)
{
	unsigned int retTime = time(0) + *secs;  
	while (time(0) < retTime);
}

