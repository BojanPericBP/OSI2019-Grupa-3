#pragma once
#pragma warning(disable:4996)
#pragma comment( lib, "winmm.lib" )
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

typedef struct kviz {
	int rb;
	char* pitanje;
	char* svi_odgovori[3];
	char odgovor;
}KVIZ;

void igraj_kviz();
int provjera_niza(int*, int,const int);
void random_pitanja(int*);
int odgovor_korisnika(char, char);


void igraj_kviz()
{
	FILE* fp;
	
	if ((fp = fopen("pitanja i odgovori.txt", "r")) != NULL)
	{
		PlaySound("ulazukviz.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);
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
				printf("%c\n", ch);

				while (ch != 'a' && ch != 'b' && ch != 'c')
				{
					printf("Pogresan unos pokusajte ponovo: ");
					ch = _getch();
					printf("%c\n", ch);
				};
				if (odgovor_korisnika(obj.odgovor, ch))
					br_bodova++;
				system("color 0b");
				
				i++;
			}
			
		}
		printf("Osvojili ste %d bodova!\n\n", br_bodova);
		printf("Da li zelite da sacuvate vas rezultat?[d/n]: ");
		ch = _getch();
		printf("%c", ch);
		while (ch != 'd' && ch != 'D' && ch != 'n' && ch != 'N')
		{
			printf("'\nogresan unos!\nUnesite ponovo: ");
			ch = _getch();
			printf("%c", ch);
		}
		//if (ch == 'y' || ch == 'Y')
		//sacuvaj_rezultat(br_bodova);

		printf("\nDa li zelite da pogeldate rang listu?[d/n]: ");
		ch = _getch();
		printf("%c", ch);
		while (ch != 'D' && ch != 'd' && ch != 'n' && ch != 'N')
		{
			printf("\nPogresan unos!\nUnesite ponovo: ");
			ch = _getch();
			printf("%c", ch);
		}
		if (ch == 'D' || ch == 'd')
		{
			//prikazi_rang_listu();
		}
		
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
		PlaySound("tacanodgovor.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);

		return 1;
	}
	else
	{
		system("color 0c");
		printf("NETACAN ODGOVOR!\n");
		PlaySound("pogresanodgovor.wav", NULL, SND_SYNC | SND_LOOP | SND_FILENAME);

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

int cmpfunc(const void* a, const void* b) {
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
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", niz[i]);
	}
}