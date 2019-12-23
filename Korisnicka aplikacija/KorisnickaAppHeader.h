#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <iostream>
#include <Windows.h>

void inicijalizuj_prozor()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1055, 700, TRUE);
}

void glavni_meni_korisnicke_aplikacije()
{
	system("cls");
	system("color f0");
	printf("\n\n***************************************************************** DOBRODOSLI *****************************************************************\n\n");
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

	printf("\n****************************************************** PREGLED PREPORUCENIH DOGADJAJA ********************************************************\n");
	//ispis preporucenih dogadjaja
	printf("\n**********************************************************************************************************************************************\n\n");
}

void meni_svih_dogadjaja()
{
	system("cls");
	system("color 4f");

	printf("\n*********************************************************** PREGLED SVIH DOGADJAJA ***********************************************************\n");
	//funkcija za ispis svih dogadjaja
	printf("\n**********************************************************************************************************************************************\n\n");
}

void meni_kviza()
{
	system("cls");
	system("color 0b");
	printf("\n********************************************************* DOBRO DOSLI U KVIZ *****************************************************************\n");
	//igranje kviza
	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_rang_liste()
{
	system("cls");
	system("color 5f");

	printf("\n**************************************************************** RANG LISTA ******************************************************************\n");
	//prikaz rang liste
	printf("\n**********************************************************************************************************************************************\n\n");
	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_help()
{
	system("cls");
	system("color 70");

	printf("\n****************************************************************** POMOC *********************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"Za detaljne informacije pogledajte korisnicku dokumentaziju.\n");
	printf("\n**********************************************************************************************************************************************\n\n");

	printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
}

void meni_o_korisnickoj_aplikaciji()
{
	system("cls");
	system("color 0a");

	printf("\n*************************************************************** O aplikaciji *****************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"\nApliakciju su radili studenti Elektrotehnickog fakulteta Banjaluka :\n"
	"Jelena Jakovljevic (Jeca Pereca),\nKristina Krickovic (Kricka),\nSasa Stankovic (Sale),\n"
		"Bojan Janjic (Che),\nBojan Peric (Boki, Bole, Boss)\n");
	printf("\n**********************************************************************************************************************************************\n\n");
}

void odabir_opcije_korisnika()
{
	char a[50] = {};
	char c[50] = {};
	char flag = 0;
	FILE* fp=NULL;
	while (1)
	{
		scanf("\n%[^\n]s", a);
		while (a[1] != 0)
		{
			printf("\nNepostojeca opcija!\nUnesite ponovo: ");
			scanf("\n%[^\n]s", a);
		}
		switch (a[0])
		{
		case '7':
			exit(1);
			break;

		case '1':
			system("cls");
			meni_prikaz_preporucenih_dogadjaja();
			do {
				printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n");
				scanf("\n%s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
					exit(1);
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					printf("\n************Dodavanje komentara************\n\n");
					//funkcija za unos id-a
					//funkcija za trazenje dogadjaja po id-u
					//funkcija za unos komentara
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					printf("\n************Pregled komentara************\n\n");

					//funkcija za unos id-a
					//funkcija za trazenje dogadjaja po id-u
					//ispis rezultata
				}
			} while (!flag);
			break;

		case '2':
			system("cls");
			meni_svih_dogadjaja();
			do {
				printf("Unesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n");
				scanf("\n%s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
					exit(1);
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					printf("\n************Dodavanje komentara************\n\n");
					//funkcija za unos id-a
					//funkcija za trazenje dogadjaja po id-u
					//funkcija za unos komentara
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					printf("\n************Pregled komentara************\n\n");

					//funkcija za unos id-a
					//funkcija za trazenje dogadjaja po id-u
					//ispis rezultata
				}
			} while (!flag);
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
			do 
			{
				printf("Unesite D -> Pregled korisnicke dokumentacije\n\tM -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
				scanf("\n%s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'D' && c[0] != 'd') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
					flag = 1;
				}
				else if (c[0] == 'E' || c[0] == 'e')
					exit(1);
				else if (c[0] == 'D' || c[0] == 'd')
				{
					flag = 0;
					system("\"\"../config files/Korisnicka dokumentacija/Dokumentacija.docx\"\"");
				}
			} while (!flag);
			break;
		default:
			printf("Nepostojeca opcija!\n");
			break;
		}

	}
}