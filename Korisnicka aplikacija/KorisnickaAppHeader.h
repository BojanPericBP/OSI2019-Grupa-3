#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <iostream>

void glavni_meni_korisnicke_aplikacije()
{
	system("cls");
	system("color f0");
	printf("\n\n******************************************************************DOBRODOSLI******************************************************************\n\n");
	printf("                                          Da biste odabrali zeljenu opciju unesite odgovarajuci broj!\n");
	printf("     ____________________________________________________________________________________________________________________________________     \n\n");
	printf("                     1: PREPORUCENI DOGADJAJI\n");
	printf("                     2: PRIKAZ SVIH DOGADJAJA\n");
	printf("                     3: ZAIGRAJTE KVIZ\n");
	printf("                     4: RANG LISTA KORISNIKA KOJI SU IGRALI KVIZ\n");
	printf("                     5: POMOC\n");
	printf("                     6: O APLIKACIJI\n");
	printf("                     7: IZLAZ IZ PROGRAMA\n");
	printf("\n**********************************************************************************************************************************************\n");
}

void meni_prikaz_preporucenih_dogadjaja()
{
	system("cls");
	system("color 0e");

	printf("\n*******************************************************PREGLED PREPORUCENIH DOGADJAJA*********************************************************\n");

	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n");
}

void meni_svih_dogadjaja()
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************PREGLED SVIH DOGADJAJA************************************************************\n");
	//funkcija za ispis svih dogadjaja
	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n");
}

void meni_kviza()
{
	system("cls");
	system("color 0b");
	printf("\n**********************************************************DOBRO DOSLI U KVIZ******************************************************************\n");

	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_rang_liste()
{
	system("cls");
	system("color 5f");

	printf("\n*****************************************************************RANG LISTA*******************************************************************\n");

	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_help()
{
	system("cls");
	system("color 70");

	printf("\n********************************************************************POMOC*********************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"Za detaljne informacije pogledajte korisnicku dokumentaziju.\n");
	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_o_korisnickoj_aplikaciji()
{
	system("cls");
	system("color 0a");

	printf("\n*****************************************************************O aplikaciji*****************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"\nApliakciju su radili studenti Elektrotehnickog fakulteta Banjaluka :\n"
	"Jelena Jakovljevic (Jeca Pereca),\nKristina Krickovic (Kricka),\nSasa Stankovic (Sale),\n"
		"Bojan Janjic (Che),\nBojan Peric (Boki, Bole, Boss)\n");
	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite D -> Pregled korisnicke dokumentacije\n\tM -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void odabir_opcije_korisnika()
{
	char a[50] = {};
	char c[50] = {};
	while (1)
	{
		scanf("%s", a);
		while (a[1] != 0)
		{
			printf("Nepostojeca opcija!\nUnesite ponovo: ");
			scanf("%s", a);
		}
		switch (a[0])
		{
		case '7':
			exit(1);
			break;
		case '1':
			system("cls");
			meni_prikaz_preporucenih_dogadjaja();
			
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
				}
			else if (c[0] == 'E' || c[0] == 'e')
					exit(1);
			else if (c[0] == 'K' || c[0] == 'k')
			{
				printf("\nUnesite ib (identifikacioni broj) dogadjaja za koji zelite pogledati komentare: ");
				char ib[50] = {};
				scanf(" %s", ib);
				//pretraga
				int search = 0;  //rezultat pretrage
				if (!search)
				{
					printf("Dogadjaj sa trazenim ib-om ne postoji.\n\nUnesite P -> za ponovno unosenje ib-a\n\tM -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
				}
				else
				{
					//prikaz komentara
				}
			}
			else if (c[0] == 'P' || c[0] == 'p')
			{
				//funkcija za prikaz komentara
			}
			break;
		case '2':
			system("cls");
			meni_svih_dogadjaja();
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0]!='p') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);
			else if (c[0] == 'K' || c[0] == 'k')
			{
				printf("\nUnesite ib (identifikacioni broj) dogadjaja za koji zelite pogledati komentare: ");
				//pronaci dogadjaj i ispisati njegove komentare
			}
			else if (c[0] == 'P' || c[0] == 'p')
			{
				//funkcija za prikaz komentara
			}
			break;
		case '3':
			system("cls");

			meni_kviza();
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("\nNepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);

			break;
		case '4':
			system("cls");

			meni_rang_liste();
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);

			break;
		case '5':
			system("cls");
			meni_help();
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);

			break;
		case '6':
			system("cls");
			meni_o_korisnickoj_aplikaciji();
			scanf("\n%s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
				exit(1);

			break;
		default:
			printf("Nepostojeca opcija!\n");
			break;
		}

	}
}