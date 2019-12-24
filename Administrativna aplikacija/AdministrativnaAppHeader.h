#include <stdio.h>
#include <iostream>
#include <windows.h>

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
	printf("                     4: DODAVANJE KATEGORIJE\n");
	printf("                     5: UREDJIVANJE KVIZA\n");
	printf("     ____________________________________________________________________________________________________________________________________     \n\n");
	printf("                     6: IZLAZ\n");
	printf("\n**********************************************************************************************************************************************\n\n");
}

void meni_logovanje_administratora()
{
	//system("color f0");
	printf("\n*******************************************************************PRIJAVA********************************************************************\n");
	//funkcija za logovanje administratora u kojoj se nalazi funkcija za provjeru validnosti pristupnih podataka
	printf("Unesite:E->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}

void meni_dodavanje_dogadjaja()
{
	system("color 0a");
	printf("\n**************************************************************DODAVANJE DOGADJAJA*************************************************************\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}
void meni_uredjivanje_dogadjaja()
{
	system("color 0a");
	printf("\n*************************************************************UREDJIVANJE DOGADJAJA************************************************************\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("______________________________________________________________\n\n");
}

void meni_brisanje_dogadjaja()
{
	system("color 0a");
	printf("\n**************************************************************BRISANJE DOGADJAJA**************************************************************\n\n");
	printf("Unesite:\n\tM-> za povratak na glavni meni\n\tE->za izlazak iz programa\n");
	printf("   _________________________________________________________________________________________________________________________________________\n\n");
}

void meni_dodavanje_kategorije()
{
	system("color 0a");
	printf("\n*************************************************************DODAVANJE KATEGORIJE*************************************************************\n\n");
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

void odabir_opcije_admina()
{
	system("title STA SE RADI NA ESTRADI");
	char a[50];
	char c[50];
	//glavni_meni_administrativne_aplikacije();

	while (1)
	{
		
		scanf("\n%[^\n]s", a);
		while (a[1] != 0)
		{
			printf("Nepostojeca opcija!\nUnesite ponovo: ");
			scanf("\n%[^\n]s", a);
		}
		switch (a[0])
		{
		case '1':
			system("cls");
			meni_dodavanje_dogadjaja();
			
			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);

			break;
		case '2':
			system("cls");
			meni_dodavanje_dogadjaja();

			scanf("\n%[^\n]s", c);

			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);
			break;
		case '3':
			system("cls");
			meni_brisanje_dogadjaja();

			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);
			break;

		case '4':
			system("cls");
			meni_dodavanje_kategorije();
			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);
				break;
		case '5':
			system("cls");
			meni_uredjivanje_kviza();

			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_administrativne_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);
				break;
		case '6':
			exit(1);
			break;
		default:
			printf("Nepostojeca opcija!\n");
			}
	}
	printf("***************************************************************************\n");
}
