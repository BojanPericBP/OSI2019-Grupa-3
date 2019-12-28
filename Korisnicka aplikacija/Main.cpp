#include "KorisnickaAppHeader.h"
#pragma warning (disable: 4996)

int main()
{
	inicijalizuj_prozor();

	FILE* dat_dogadjaji = fopen("../config files/Dogadjaji/dogadjaji.txt","r");
	if (!dat_dogadjaji) { printf("Neuspjesno ucitavanje datoteke dogadjaji.txt..."); getchar();  exit(1); }
	
	int br_dogadjaja = ucitaj_br_dogadjaja(dat_dogadjaji);
	DOGADJAJ* lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja,sizeof(DOGADJAJ));
	
	ucitaj_dogadjaje_iz_datoteke(dat_dogadjaji, lista_dogadjaja, br_dogadjaja);
	fclose(dat_dogadjaji);

	glavni_meni_korisnicke_aplikacije();
	odabir_opcije_korisnika(lista_dogadjaja,br_dogadjaja);

	free(lista_dogadjaja);

	return 0;
}
/*
Projekat TODO :

Funkcionalnosti:
komentari
pretraga po filtru
zainteresovan za dogadjaj


Finese:
pozvati funkcije gdje su komentari u switchu
pozvati ih u meniju, gdje su komentari
koristiti _getch();
*/