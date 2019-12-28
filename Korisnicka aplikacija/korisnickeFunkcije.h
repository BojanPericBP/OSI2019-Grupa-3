#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dogadjaj
{
	int id;
	char naziv[100];
	char opis;
	char lokacija[100];
	char kategorija[20];
	char datum[12];
	char vrijeme[6];
	char komentari;
	char preporucen;
}DOGADJAJ;

int ucitaj_br_dogadjaja(FILE*);
void ucitaj_dogadjaje_iz_datoteke(FILE*,DOGADJAJ*);

void ispisi_dogadjaj(DOGADJAJ*); //pomocna funkcija, koja ispisuje samo 1 dogadjaj
void svi_dogadjaji(DOGADJAJ*);
void preporuceni_dogadjaji(DOGADJAJ*);
void danasnji_dogadjaji(DOGADJAJ*);
void prosli_dogadjaji(DOGADJAJ*);
void buduci_dogadjaji(DOGADJAJ*);


int unesi_id();
DOGADJAJ* trazi_dogadjaj_id(int);
void pisi_dogadjaje_filter(DOGADJAJ*, char*);
char* unesi_komentar();
void ispisi_komentar(int);
void prikazi_opis(int);

int ucitaj_br_dogadjaja(FILE* dat_dogadjaji)
{
	//ucita samo prvi red iz datoteke i vrati kao int
}

void ucitaj_dogadjaje_iz_datoteke(FILE* dat_dogadjaji, DOGADJAJ* lista_dogadjaja)
{
	//niz vec alociran, samo ucitava red po red i smijesta u niz
}

void svi_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	int br_dogadjaja = sizeof(lista_dogadjaja) / sizeof(DOGADJAJ);
	//ispisuje cijelu listu dogadjaja
}

void preporuceni_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	int br_dogadjaja = sizeof(lista_dogadjaja) / sizeof(DOGADJAJ);
	//prolazi listom dogadjaja i ispisuje one koji imaju preporucen==1
}

void buduci_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	int br_dogadjaja = sizeof(lista_dogadjaja) / sizeof(DOGADJAJ);
	//generise danasnji datum
	//prolazi listom i poredi datume dogadjaja iz liste sa danasnjim
	//ispise ako su veci od danasnjeg
}

void prosli_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	int br_dogadjaja = sizeof(lista_dogadjaja) / sizeof(DOGADJAJ);

}
void buduci_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	int br_dogadjaja = sizeof(lista_dogadjaja) / sizeof(DOGADJAJ);

}
