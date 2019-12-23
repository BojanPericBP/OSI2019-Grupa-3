#include "KorisnickaAppHeader.h"
#pragma warning (disable: 4996)

int main()
{
	inicijalizuj_prozor();
	system("title STA SE RADI NA ESTRADI");

	glavni_meni_korisnicke_aplikacije();
	odabir_opcije_korisnika();

	getchar();
	return 0;
}