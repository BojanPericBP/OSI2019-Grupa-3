#pragma once
#pragma warning(warning : disable 4996)
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

int unos_korisnickih_podataka_admina();
int logovanje_admina();
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

void sleep(unsigned int* secs)
{
	unsigned int retTime = time(0) + *secs;  
	while (time(0) < retTime);
	*secs = *secs - 1;
}

