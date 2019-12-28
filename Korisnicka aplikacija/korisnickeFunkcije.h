#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dogadjaj
{
	int id;
	char naziv[31];
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
void svi_dogadjaji(DOGADJAJ*,int);
void preporuceni_dogadjaji(DOGADJAJ*,int);
void danasnji_dogadjaji(DOGADJAJ*,int);
void prosli_dogadjaji(DOGADJAJ*,int);
void buduci_dogadjaji(DOGADJAJ*,int);


int unesi_id();
DOGADJAJ* trazi_dogadjaj_id(int);
void pisi_dogadjaje_filter(DOGADJAJ*, char*);
char* unesi_komentar();
void ispisi_komentar(int);
void prikazi_opis(int);

int ucitaj_br_dogadjaja(FILE* dat_dogadjaji)
{
	int id, br;
	fscanf(dat_dogadjaji, "%d %d", &id, &br);
	return br;
}

void ucitaj_dogadjaje_iz_datoteke(FILE* dat_dogadjaji, DOGADJAJ* lista_dogadjaja)
{
	//niz vec alociran, samo ucitava red po red i smijesta u niz
}

void ispisi_dogadjaj(DOGADJAJ* lista_dogadjaja)
{
	printf("%5d  %-30s  %s  %s  %-20s  %s  %s  %s  %s\n",lista_dogadjaja->id,lista_dogadjaja->naziv, lista_dogadjaja->opis==1?"ima opis":"nema opisa" ,lista_dogadjaja->lokacija,lista_dogadjaja->kategorija,lista_dogadjaja->datum,lista_dogadjaja->vrijeme,lista_dogadjaja->komentari==1?"Ima komentar":"NEma komentar",lista_dogadjaja->preporucen==1?"Preporucen":"Nije preporucen");
}

void svi_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	for (int i = 0; i < br_dogadjaja; i++)
		ispisi_dogadjaj(&lista_dogadjaja[i]);
}

void preporuceni_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	for (int i = 0; i < br_dogadjaja; i++)
		if(lista_dogadjaja[i].preporucen)
			ispisi_dogadjaj(&lista_dogadjaja[i]);
}

void buduci_dogadjaji(DOGADJAJ* lista_dogadjaja)
{
	//generise danasnji datum
	//prolazi listom i poredi datume dogadjaja iz liste sa danasnjim
	//ispise ako su veci od danasnjeg
}

void prosli_dogadjaji(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{


}
