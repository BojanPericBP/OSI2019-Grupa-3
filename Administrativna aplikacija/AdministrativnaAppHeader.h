#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "AdministrativneFunkcije.h"

#pragma once
#pragma warning(disable:4996)

void glavni_meni_administrativne_aplikacije()
{
	system("color 0a");
	system("cls");
	printf("\n*******************************************************************DOBRO DOSLI****************************************************************\n\n");
	printf("                                         Da bi ste odabrali zeljenu opciju unesite odgovarajuci broj!");
	printf("\n     ____________________________________________________________________________________________________________________________________     \n\n");
	printf("                     1: DODAVANJE DOGADJAJA\n");
	printf("                     2: UREDJIVANJE DOGADJAJA\n");
	printf("                     3: BRISANJE DOGADJAJA\n");
	printf("                     4: BRISANJE KATEGORIJE\n");
	printf("                     5: UREDJIVANJE KVIZA\n");
	printf("     ____________________________________________________________________________________________________________________________________     \n\n");
	printf("                     0: IZLAZ\n");
	printf("\n**********************************************************************************************************************************************\n\n");
}

void meni_logovanje_administratora()
{
	//system("color f0");
	printf("\n*******************************************************************PRIJAVA********************************************************************\n");
	//funkcija za logovanje administratora u kojoj se nalazi funkcija za provjeru validnosti pristupnih podataka
	printf("Unesite:E->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");

	logovanje_admina();
}

void meni_dodavanje_dogadjaja()
{
	system("color 0a");
	printf("\n**************************************************************DODAVANJE DOGADJAJA*************************************************************\n\n");
	dodaj_dogadjaj();
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}
void meni_uredjivanje_dogadjaja()
{
	system("color 0a");
	printf("\n*************************************************************UREDJIVANJE DOGADJAJA************************************************************\n\n");
	uredi_dogadjaj();
	printf("\n   _________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}

void meni_brisanje_dogadjaja()
{
	system("color 0a");
	
	printf("\n**************************************************************BRISANJE DOGADJAJA**************************************************************\n\n");
	brisanje_dogadjaja();
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}

void meni_brisanje_kategorije()
{
	system("color 0a");
	printf("\n*************************************************************BRISANJE KATEGORIJE*************************************************************\n\n");
	brisi_kategoriju();
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");

}

void meni_uredjivanje_kviza()
{
	system("color 0a");
	printf("\n**************************************************************UREDJIVANJE KVIZA**************************************************************\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}


void init_prozora()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1291, 806, TRUE);
	system("title STA SE RADI NA ESTRADI");

	HMENU hmenu = GetSystemMenu(console, FALSE);
	EnableMenuItem(hmenu, SC_CLOSE,MF_GRAYED);
}
void odabir_opcije_admina()
{
	system("title STA SE RADI NA ESTRADI");
	
	char ch;

	while (1)
	{
		
		
		ch = _getch();
		
		switch (ch)
		{
		case '0':
			exit(1);
			break;
		case '1':
			system("cls");
			meni_dodavanje_dogadjaja();
			
			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
				exit(1);

			break;
		case '2':
			system("cls");
			meni_uredjivanje_dogadjaja();

			ch = _getch();

			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
				exit(1);
			break;
		case '3':
			system("cls");
			meni_brisanje_dogadjaja();

			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
				exit(1);
			break;

		case '4':
			system("cls");
			meni_brisanje_kategorije();
			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
				exit(1);
				break;

		case '5':
		
			system("cls");
			meni_uredjivanje_kviza();

			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
				exit(1);
			break;
		
		default:
			printf("Nepostojeca opcija!\n");
			}
	}
	printf("***************************************************************************\n");
}
