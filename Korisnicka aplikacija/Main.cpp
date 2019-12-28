#include "KorisnickaAppHeader.h"
#pragma warning (disable: 4996)

int main()
{
	inicijalizuj_prozor();

	FILE* dat_dogadjaji = fopen("../config files/Dogadjaji/dogadjaji.txt","r");
	if (!dat_dogadjaji) { printf("Neuspjesno ucitavanje datoteke dogadjaji.txt..."); getchar();  exit(1); }
	
	int br_dogadjaja = ucitaj_br_dogadjaja(dat_dogadjaji);
	DOGADJAJ* lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja,sizeof(DOGADJAJ));
	
	ucitaj_dogadjaje_iz_datoteke(dat_dogadjaji, lista_dogadjaja);
	fclose(dat_dogadjaji);

	/*
	DOGADJAJ dog[2];

	strcpy(dog[0].datum,"23.10.1996");
	dog[0].id = 1011;
	strcpy(dog[0].kategorija, "film");
	dog[0].komentari = 1;
	dog[0].preporucen = 1;
	strcpy(dog[0].lokacija, "banja luka");
	strcpy(dog[0].naziv, "Film123");
	strcpy(dog[0].vrijeme, "20:00");
	dog[0].opis = 0;

	strcpy(dog[1].datum, "23.10.1996");
	dog[1].id = 1011;
	strcpy(dog[1].kategorija, "film");
	dog[1].komentari = 1;
	dog[1].preporucen = 1;
	strcpy(dog[1].lokacija, "banja luka");
	strcpy(dog[1].naziv, "Film123");
	strcpy(dog[1].vrijeme, "20:00");
	dog[1].opis = 1;


	preporuceni_dogadjaji(dog,2);
	*/

	glavni_meni_korisnicke_aplikacije();
	odabir_opcije_korisnika(lista_dogadjaja,br_dogadjaja);

	
	free(lista_dogadjaja);

	return 0;
}