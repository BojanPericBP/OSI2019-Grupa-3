#include "AdministrativnaAppHeader.h"
#include "AdministrativneFunkcije.h"
#include<time.h>
#include <Windows.h>
#pragma warning(disable : 4996)
int main()
{
	char c[5];//smjestam opciju koju je korisnik izabrao, npr exit ili try again i slicno
	
	dodaj_dogadjaj();
	meni_logovanje_administratora();
	//logovanje_admina();

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1055, 700, TRUE);
	system("title STA SE RADI NA ESTRADI");


	glavni_meni_administrativne_aplikacije();
	odabir_opcije_admina();

	return 0;
}