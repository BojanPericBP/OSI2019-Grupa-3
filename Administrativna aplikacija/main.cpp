#include "AdministrativnaAppHeader.h"
#include "AdministrativneFunkcije.h"
#include<time.h>
#include <windows.h>
#pragma warning(disable : 4996)

int main()
{
	init_prozora();
	meni_logovanje_administratora();

	glavni_meni_administrativne_aplikacije();
	odabir_opcije_admina();

	return 0;
}