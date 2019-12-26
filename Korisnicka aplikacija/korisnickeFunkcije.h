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
	char kategorija[30];
	char datum[12];
	char vrijeme[6];
	char komentari;
	char preporucen;
}DOGADJAJ;

FILE* ucitaj_iz_datoteke(DOGADJAJ*);
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

FILE* ucitaj_iz_datoteke(DOGADJAJ* lista_dogadjaja)
{
	return NULL;
}

void svi_dogadjaji(DOGADJAJ* niz_dogadjaja)
{

}

void preporuceni_dogadjaji(DOGADJAJ* niz_dogadjaja)
{


}
