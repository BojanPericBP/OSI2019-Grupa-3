#include "AdministrativnaAppHeader.h"
#include "KorisnickaAppHeader.h"

#pragma warning (disable: 4996)

int main()
{
	system("color 57");
	inicijalizuj_prozor();
	printf("\n******************************************************************************** DOBRO DOSLI **********************************************************************************\n\n");

	char ch;

	printf("Unesite:\n\tA -> za pristup administrativnom dijelu aplikacije.\n\tK -> za pristup korisnickom dijelu aplikacije.\n\tE -> za izlazak iz programa.\n");

	printf("Unos: ");
	ch = _getch();
	char username[21] = {};
	printf("%c", ch);
	while (ch != 'a' && ch != 'A' && ch != 'k' && ch != 'K' && ch != 'e' && ch != 'E')
	{
		printf("\nPogresan unos, unesite ponovo: ");
		ch = _getch();
		printf("%c", ch);
	}

	if (ch == 'e' || ch == 'E')
		exit(1);
	else if (ch == 'k' || ch == 'K')
	{
		FILE* dat_dogadjaji = fopen("../config files/Dogadjaji/dogadjaji.txt", "r");
		if (!dat_dogadjaji) { printf("Neuspjesno ucitavanje datoteke dogadjaji.txt..."); getchar();  exit(1); }

		int br_dogadjaja = ucitaj_br_dogadjaja(dat_dogadjaji);
		DOGADJAJ* lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja, sizeof(DOGADJAJ));

		ucitaj_dogadjaje_iz_datoteke(dat_dogadjaji, lista_dogadjaja, br_dogadjaja);
		fclose(dat_dogadjaji);

		glavni_meni_korisnicke_aplikacije();
		odabir_opcije_korisnika(lista_dogadjaja, br_dogadjaja,username);
	}
	else if (ch == 'a' || ch == 'A')
	{
		char admin_username[21] = {}, admin_pass[21] = {};
		meni_logovanje_administratora(admin_username,admin_pass);

		glavni_meni_administrativne_aplikacije();
		odabir_opcije_admina(admin_username);
	}

	return 0;
}