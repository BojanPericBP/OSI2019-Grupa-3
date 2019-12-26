#include "AdministrativnaAppHeader.h"
#pragma warning(disable : 4996)
int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console,r.left,r.top,1055, 700, TRUE);
	system("color a0");
	meni_logovanje_administratora();
	glavni_meni_administrativne_aplikacije();
	odabir_opcije_admina();
	return 0;
}