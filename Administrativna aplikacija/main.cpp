#include "AdministrativnaAppHeader.h"
#include "AdministrativneFunkcije.h"
#include<time.h>
#include <windows.h>
#pragma warning(disable : 4996)

DWORD WINAPI CreateMessageBox(void*) { //threaded so we can still work with it
	MessageBox(nullptr, "Message", "Title", MB_OKCANCEL);
	return 0;
}

int main()
{

	init_prozora();
	meni_logovanje_administratora();

	glavni_meni_administrativne_aplikacije();
	odabir_opcije_admina();

	return 0;
}