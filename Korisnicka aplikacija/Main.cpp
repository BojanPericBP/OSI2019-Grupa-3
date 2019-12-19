#include "KorisnickaAppHeader.h"
#include <Windows.h>
#pragma warning (disable: 4996)

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1055, 700, TRUE);

	system("title STA SE RADI NA ESTRADI");
	glavni_meni_korisnicke_aplikacije();
	odabir_opcije_korisnika();

	scanf("%d");
	return 0;
}