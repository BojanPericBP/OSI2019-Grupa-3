#include "KorisnickaAppHeader.h"
#pragma warning (disable: 4996)

int main()
{
	inicijalizuj_prozor();
	DOGADJAJ lista_dogadjaja[3]; //prepraviti da ucita broj dogadjaja iz datoteke
	FILE* dat_dogadjaji = ucitaj_iz_datoteke(lista_dogadjaja);
	//if (!dat_dogadjaji){ printf("Neuspjesno ucitavanje datoteke dogadjaji.txt..."); getchar();  exit(1); }
	//else fclose(dat_dogadjaji);


	glavni_meni_korisnicke_aplikacije();
	odabir_opcije_korisnika();


	getchar();
	return 0;
}