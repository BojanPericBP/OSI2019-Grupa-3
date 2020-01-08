#pragma once
#pragma warning(disable:4996)
#pragma comment( lib, "winmm.lib" )
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

typedef struct kviz {
	int rb;
	char* pitanje;
	char* svi_odgovori[3];
	char odgovor;
}KVIZ;

typedef struct igrac
{
	int br_bod;
	char nick[31];
}IGRAC;

void sacuvaj_rezultat(int);
void prikazi_rang_listu();
void igraj_kviz();
int provjera_niza(int*, int,const int);
void random_pitanja(int*);
int odgovor_korisnika(char, char);


void igraj_kviz()
{
	FILE* fp;
	
	if ((fp = fopen("../config files/Kviz/pitanja i odgovori.txt", "r")) != NULL)
	{
		PlaySoundA("ulazukviz.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
		int br_pitanja,arr[10],br_bodova = 0; 
		KVIZ obj;
		char* odgovori[3],ch;

		for (int i = 0; i < 3; i++)
			odgovori[i] = (char*)malloc(40*sizeof(char));

		obj.pitanje = (char*)malloc(200 * sizeof(char));
		obj.svi_odgovori[0] = (char*)malloc(40 * sizeof(char));
		obj.svi_odgovori[1] = (char*)malloc(40 * sizeof(char));
		obj.svi_odgovori[2] = (char*)malloc(40 * sizeof(char));
		
		fscanf(fp, "%d", &br_pitanja);
		random_pitanja(arr);
		int god;
		int i = 0;
		while (i<10)
		{
			fscanf(fp, "%d %[^\n]s", &obj.rb, obj.pitanje);
			fscanf(fp, "\n%c", &obj.odgovor);
			fscanf(fp, "\n%[^\n]s", obj.svi_odgovori[0]);
			fscanf(fp, "\n%[^\n]s", obj.svi_odgovori[1]);
			fscanf(fp, "\n%[^\n]s", obj.svi_odgovori[2]);

			if (provjera_niza(arr, obj.rb,30)==0)
			{
				printf("\n%d. %s\n%s\n%s\n%s\n\n ", i + 1, obj.pitanje, obj.svi_odgovori[0], obj.svi_odgovori[1], obj.svi_odgovori[2]);
				
				printf("Unos: ");
				ch = _getch();
				if (ch != 13 && ch != 32) printf("%c\n", ch);

				while (ch != 'a' && ch != 'b' && ch != 'c')
				{
					if (ch != 13 && ch != 32) printf("Pogresan unos pokusajte ponovo: ");
					ch = _getch();
					if (ch != 13 && ch != 32) printf("%c\n", ch);
				};
				if (odgovor_korisnika(obj.odgovor, ch))
					br_bodova++;
				system("color 0b");
				
				i++;
			}
			
		}
		fclose(fp);
		printf("\nOsvojili ste %d bodova!\n\n", br_bodova);
		printf("Da li zelite da sacuvate vas rezultat?[d/n]: ");
		ch = _getch();
		if (ch != 13 && ch != 32) printf("%c", ch);
		while (ch != 'd' && ch != 'D' && ch != 'n' && ch != 'N')
		{
			if (ch != 13 && ch != 32) printf("\nPogresan unos!\nUnesite ponovo: ");
			ch = _getch();
			if (ch != 13 && ch != 32) printf("%c", ch);
		}
		if (ch == 'D' || ch == 'd')
			sacuvaj_rezultat(br_bodova);

		printf("\nDa li zelite da pogledate rang listu?[d/n]: ");
		ch = _getch();
		if (ch != 13 && ch != 32) printf("%c", ch);
		while (ch != 'D' && ch != 'd' && ch != 'n' && ch != 'N')
		{
			if (ch != 13 && ch != 32) printf("\nPogresan unos!\nUnesite ponovo: ");
			ch = _getch();
			if (ch != 13 && ch != 32) printf("%c", ch);
		}
		if (ch == 'D' || ch == 'd')
			prikazi_rang_listu();
		
	}
	else
		printf("Greska prilikom otvaranja datoteke sa pitanjima!");
}

int odgovor_korisnika(char tacan_odgovor, char odgovor)
{
	if (tacan_odgovor == odgovor)
	{
		system("color 0a");
		printf("TACAN ODGOVOR!\n");
		PlaySoundA("tacanodgovor.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);

		return 1;
	}
	else
	{
		system("color 0c");
		printf("NETACAN ODGOVOR!\n");
		PlaySoundA("pogresanodgovor.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);

		return 0;
	}
	
}

int provjera_niza(int* arr,int br,int n)
{
	for ( int i = 0; i < n; i++)
		if (arr[i] == br)
			return 0;

	return 1;
}

int cmpfunc(const void* a, const void* b) 
{
	return (*(int*)a - *(int*)b);
}
void random_pitanja(int* niz)
{
	int i=0 , n;
	
	for (int i = 0; i < 10; i++)
		niz[i] = 0;

	srand(time(NULL));

	while (i<10)
	{
		n = rand() % 30;
		if (provjera_niza(niz, n,10))
			niz[i++] = n;
	}
	qsort(niz, 10, sizeof(int),cmpfunc);
}

void prikazi_rang_listu()
{
	FILE* rang_lista_dat = fopen("../config files/Kviz/rang_lista.txt", "r");
	if (!rang_lista_dat)
	{
		printf("Neuspjesno otvaranje datoteke rang_lista.txt");
		return;
	}
	else
	{
		printf("\n -----------------------------------------------------");
		printf("\n | Rb. | Br bodova | Korisnicko ime                  |");
		printf("\n -----------------------------------------------------");
		int br_igraca = 0;
		fscanf(rang_lista_dat, "%d", &br_igraca);
		int temp_bodovi = 0;
		char temp_korisnik[32] = {};
		for (int i = 0; i < br_igraca; i++)
		{
			fscanf(rang_lista_dat, "%d \n%[^\n]s", &temp_bodovi, temp_korisnik);
			printf("\n | %2d. | %9d |  %-30s |", i + 1, temp_bodovi, temp_korisnik);
		}
		printf("\n -----------------------------------------------------\n\n");
	}
	fclose(rang_lista_dat);
}

int trazi(char* nick, IGRAC* niz_igraca, int br_igraca)
{
	for (int i = 0; i < br_igraca; i++)
		if (!strcmp(niz_igraca[i].nick, nick))
			return 1;
	return 0;
}

void sacuvaj_rezultat(int br_bodova)
{
	printf("\nUnesite korisnicko ime: ");
	char* nick = (char*)calloc(1000, sizeof(char));
	scanf("\n%[^\n]s", nick);
	while (strlen(nick) > 30)
	{
		printf("\nPredug unos. Unesite ponovo korisnicko ime: ");
		scanf("\n%[^\n]s", nick);
	}
	char uneseni_nick[30] = {};
	strcpy(uneseni_nick, nick);
	free(nick);

	FILE* rang_lista_dat = fopen("../config files/Kviz/rang_lista.txt", "r");
	if (!rang_lista_dat)
		printf("Neuspjesno otvaranje datoteke rang_lista.txt");
	else
	{
		int br_igraca = 0;
		fscanf(rang_lista_dat, "%d", &br_igraca);
		IGRAC* niz_igraca = (IGRAC*)calloc(br_igraca + 1, sizeof(IGRAC));
		char temp_korisnik[32] = {};
		int temp_bodovi = 0;
		int i = 0;
		char flag_postoji = 0;
		while (fscanf(rang_lista_dat, "%d \n%[^\n]s", &temp_bodovi, temp_korisnik) != EOF)
		{
			niz_igraca[i].br_bod = temp_bodovi;
			strcpy(niz_igraca[i].nick, temp_korisnik);
			if (!strcmp(temp_korisnik, uneseni_nick)) flag_postoji = 1;
			++i;
		}
		fclose(rang_lista_dat); rang_lista_dat = NULL;
		char uneseni_nick2[30] = {};
		if (flag_postoji)
		{
			printf("\nKorisnicko ime vec postoji.Unesite ponovo: ");
			nick = (char*)calloc(1000, sizeof(char));
			scanf("\n%[^\n]s", nick);
			while (strlen(nick) > 30 || (trazi(nick, niz_igraca, br_igraca) == 1))
			{
				if(strlen(nick)>30 )printf("\nPredug unos. Unesite ponovo korisnicko ime: ");
				else if(trazi(nick, niz_igraca, br_igraca) == 1)  printf("\nKorisnicko ime vec postoji. Unesite ponovo:  ");
				scanf("\n%[^\n]s", nick);
			}
			strcpy(uneseni_nick2, nick);
			free(nick);
		}
		br_igraca++;
		niz_igraca[br_igraca - 1].br_bod = br_bodova;
		if (flag_postoji) strcpy(niz_igraca[br_igraca - 1].nick, uneseni_nick2);
		else strcpy(niz_igraca[br_igraca - 1].nick, uneseni_nick);
		qsort(niz_igraca, br_igraca, sizeof(IGRAC), cmpfunc);

		rang_lista_dat = fopen("../config files/Kviz/rang_lista.txt", "w");
		fprintf(rang_lista_dat, "%d", br_igraca);
		for (int i = 0; i < br_igraca; i++)
			fprintf(rang_lista_dat, "\n%d %s", niz_igraca[i].br_bod, niz_igraca[i].nick);
		fclose(rang_lista_dat); rang_lista_dat = NULL;
		free(niz_igraca);
	}
}