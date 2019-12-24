#include "AdministrativnaAppHeader.h"
#include "AdministrativneFunkcije.h"
#pragma warning(disable : 4996)
int main()
{
	char c[5];//smjestam opciju koju je korisnik izabrao, npr wxit ili try again i slicno
	
	meni_logovanje_administratora();
	logovanje_admina();

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1055, 700, TRUE);



	/*while (br_pokusaja && !unos_korisnickih_podataka_admina())
	{
		--br_pokusaja;

		printf("\nPorgesno korisnicko ime ili lozinka!\nUnesite 'e' za izlaz iz programa ili unesite 'p' za ponovni unos podataka!\n");
		scanf("\n%s", &c);

		while (c[1] != 0 || (c[0] != 'p' && c[0] != 'P' && c[0] != 'e' && c[0] != 'E'))
		{
			printf("Nepostojeca opcija!\nUnesite 'e' ili 'p': ");
			scanf("\n%s", &c);
		}
		if (c[0] == 'e' || c[0] == 'E')
			exit(1);
		else if (c[0] == 'p' || c[0] == 'P')
		{
			printf("\nUPOZORENJE!\nOSTALO VAM JE JOS %d POKUSAJA!\n", br_pokusaja);
			continue;
		}
	}
	if (br_pokusaja == 0)
	{
		printf("Vas nalog ce biti blokiran narednih sat vremena!");
		do
		{
			printf("Unesite 'e' za izlazak: ");
			scanf("%s", &c);
		} while (c[1] != 0 || (c[0] != 'e' && c[0] != 'E'));
	}*/

	glavni_meni_administrativne_aplikacije();
	odabir_opcije_admina();

	return 0;
}