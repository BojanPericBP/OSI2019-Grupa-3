#pragma once
#define MAX 20

typedef struct admin {
	char password[MAX], username[MAX];	//cuvanje korisnickog unosa
	short flag;//ako je korisnik 5 puta unio pogreesne pristupne podatke da se onemoguci ponovno unosenje neko vrijeme
}ADMIN;

typedef struct vrijeme {
	int sat, minute;
}VRIJEME;

typedef struct datum
{
	int dan, mjesec, godina;
}DATUM;

typedef struct zainteres
{
	int id, br;
}ZAINTERESOVAN;

typedef struct dogadjaj
{
	int id;
	char naziv[31];
	char opis;
	char lokacija[51];
	char kategorija[21];
	char datum[12];
	char vrijeme[6];
	char komentari;
	char preporucen;
}DOGADJAJ;

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

