#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "korisnickeFunkcije.h"

void inicijalizuj_prozor()
{
	system("title STA SE RADI NA ESTRADI");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	r.left = 125;
	MoveWindow(console, r.left, r.top, 1270, 700, TRUE);
}

void glavni_meni_korisnicke_aplikacije()
{
	system("cls");
	system("color f0");
	printf("\n\n******************************************************************************** DOBRODOSLI ********************************************************************************\n\n");
	printf("                                                    Da biste odabrali zeljenu opciju unesite odgovarajuci broj!\n");
	printf("     __________________________________________________________________________________________________________________________________________________________________     \n\n");
	printf("                              1: PREPORUCENI DOGADJAJI\n");
	printf("                              2: PRIKAZ BUDUCIH DOGADJAJA\n");
	printf("                              3: PRIKAZ DANASNJIH DOGADJAJA\n");
	printf("                              4: PRIKAZ PROSLIH DOGADJAJA\n");
	printf("                              5: PRIKAZ SVIH DOGADJAJA\n");
	printf("                              6: ZAIGRAJTE KVIZ\n");
	printf("                              7: RANG LISTA KORISNIKA KOJI SU IGRALI KVIZ\n");
	printf("                              8: POMOC\n");
	printf("                              9: O APLIKACIJI\n");
	printf("     __________________________________________________________________________________________________________________________________________________________________     \n\n");
	printf("                              0: IZLAZ IZ PROGRAMA\n");
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_prikaz_preporucenih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n********************************************************************* PREGLED PREPORUCENIH DOGADJAJA ***********************************************************************\n\n");
	preporuceni_dogadjaji(lista_dogadjaja,br_dogadjaja);
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_svih_dogadjaja(DOGADJAJ* lista_dogadjaja,int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED SVIH DOGADJAJA **************************************************************************\n\n");
	svi_dogadjaji(lista_dogadjaja, br_dogadjaja);
	printf("\n****************************************************************************************************************************************************************************\n");
}

int meni_danasnjih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED DANASNJIH DOGADJAJA *********************************************************************\n\n");
	int flag=danasnji_dogadjaji(lista_dogadjaja, br_dogadjaja);
	printf("\n****************************************************************************************************************************************************************************\n");
	return flag;
}

void meni_prosli_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED PROSLIH DOGADJAJA ***********************************************************************\n\n");
	prosli_dogadjaji(lista_dogadjaja,br_dogadjaja);
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_buducih_dogadjaja(DOGADJAJ* lista_dogadjaja,int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED BUDUCIH DOGADJAJA ***********************************************************************\n\n");
	buduci_dogadjaji(lista_dogadjaja,br_dogadjaja);
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_kviza()
{
	system("cls");
	system("color 0b");
	printf("\n************************************************************************ DOBRO DOSLI U KVIZ ********************************************************************************\n\n");
	//igranje kviza
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_rang_liste()
{
	system("cls");
	system("color 5f");

	printf("\n******************************************************************************* RANG LISTA *********************************************************************************\n\n");
	//prikaz rang liste
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_help()
{
	system("cls");
	system("color 70");

	printf("\n********************************************************************************* POMOC ************************************************************************************\n\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"Za detaljne informacije pogledajte korisnicku dokumentaziju.\n");
	printf("\n****************************************************************************************************************************************************************************\n");
}

void meni_o_korisnickoj_aplikaciji()
{
	system("cls");
	system("color 0a");

	printf("\n************************************************************************ O aplikaciji **************************************************************************************\n\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjai odrzavaju u nekom gradu, datum i mjesto dorzavanja dogadjaja,\nkao i komentare drugih korisnika o predstojecim dogadjajima.\n"
		"\nApliakciju su radili studenti Elektrotehnickog fakulteta Banjaluka :\n"
		"Jelena Jakovljevic (Jeca Pereca),\nKristina Krickovic (Kricka),\nSasa Stankovic (Sale),\n"
		"Bojan Janjic (Che),\nBojan Peric (Boki, Bole, Boss)\n");
	printf("\n****************************************************************************************************************************************************************************\n");
}

void odabir_opcije_korisnika(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	char a[1000] = {};
	char c[1000] = {};
	char flag = 0,flag_danasnji=0;
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
		case '0':
			free(lista_dogadjaja);
			exit(1);
			break;

		case '1':
			system("cls");
			meni_prikaz_preporucenih_dogadjaja(lista_dogadjaja,br_dogadjaja);
			do {
				printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p' && c[0] != 'O' && c[0] != 'o' && c[0] != 'Z' && c[0] != 'z') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) unesi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					int temp_id=unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja,br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) ispisi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'O' || c[0] == 'o') // O -> Pregled opisa nekog dogadjaja
				{
					flag = 0;
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (c[0] == 'Z' || c[0] == 'z') // Z -> zainteresovan za dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
			} while (!flag);
			break;

		case '5':
			system("cls");
			meni_svih_dogadjaja(lista_dogadjaja,br_dogadjaja);
			do {
				printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n\tF -> Ako zelite da sortirate listu po nekom filtru\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p' && c[0] != 'O' && c[0] != 'o' && c[0] != 'Z' && c[0] != 'z' && c[0] != 'F' && c[0] != 'f') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) unesi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) ispisi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'O' || c[0] == 'o') // O -> Pregled opisa nekog dogadjaja
				{
					flag = 0;
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (c[0] == 'Z' || c[0] == 'z') // Z -> zainteresovan za dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'F' || c[0] == 'f') // F -> filtriranje
				{
					flag = 0;
					pisi_dogadjaje_filter(lista_dogadjaja,br_dogadjaja);
				}
			} while (!flag);
			break;

		case '6':
			system("cls");

			meni_kviza();
			printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("\nNepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
			{
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '7':
			system("cls");

			meni_rang_liste();
			printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
			{
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '9':
			system("cls");
			meni_o_korisnickoj_aplikaciji();
			printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
			scanf("\n%[^\n]s", c);
			while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
			{
				printf("Nepostojeca opcija! Izaberite ponovo: \n");
				scanf("\n%[^\n]s", c);
			}
			if (c[0] == 'M' || c[0] == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (c[0] == 'E' || c[0] == 'e')
			{
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '8':
			system("cls");
			meni_help();
			do
			{
				printf("\nUnesite D -> Pregled korisnicke dokumentacije\n\tM -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'D' && c[0] != 'd') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
					flag = 1;
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
				else if (c[0] == 'D' || c[0] == 'd')
				{
					flag = 0;
					system("\"\"../config files/Korisnicka dokumentacija/Dokumentacija.docx\"\"");
				}
			} while (!flag);
			break;
		case '3':
			system("cls");
			flag_danasnji=meni_danasnjih_dogadjaja(lista_dogadjaja, br_dogadjaja);
			if (flag_danasnji)
			{
				do {
					printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
					scanf("\n%[^\n]s", c);
					while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p' && c[0] != 'O' && c[0] != 'o' && c[0] != 'Z' && c[0] != 'z') || c[1] != 0)
					{
						printf("Nepostojeca opcija! Izaberite ponovo: \n");
						scanf("\n%[^\n]s", c);
					}
					if (c[0] == 'M' || c[0] == 'm')
					{
						system("cls");
						flag = 1;
						glavni_meni_korisnicke_aplikacije();
					}
					else if (c[0] == 'E' || c[0] == 'e')
					{
						free(lista_dogadjaja);
						exit(1);
					}
					else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
					{
						flag = 0;
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj) unesi_komentar(temp_id);
						else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
					}
					else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
					{
						flag = 0;
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj) ispisi_komentar(temp_id);
						else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
					}
					else if (c[0] == 'O' || c[0] == 'o') // O -> Pregled opisa nekog dogadjaja
					{
						flag = 0;
						prikazi_opis(lista_dogadjaja, br_dogadjaja);
					}
					else if (c[0] == 'Z' || c[0] == 'z') // Z -> zainteresovan za dogadjaj
					{
						flag = 0;
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(temp_id);
						else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
					}
				} while (!flag);
			}
			else
			{
				printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e') || c[1] != 0)
				{
					printf("\nNepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
			}
			break;
		case '4':
			system("cls");
			meni_prosli_dogadjaja(lista_dogadjaja, br_dogadjaja);
			do {
				printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p' && c[0] != 'O' && c[0] != 'o' && c[0] != 'Z' && c[0] != 'z') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) unesi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) ispisi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'O' || c[0] == 'o') // O -> Pregled opisa nekog dogadjaja
				{
					flag = 0;
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (c[0] == 'Z' || c[0] == 'z') // Z -> zainteresovan za dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
			} while (!flag);
			break;
		case '2':
			system("cls");
			meni_buducih_dogadjaja(lista_dogadjaja,br_dogadjaja);
			do
			{
				printf("\nUnesite M -> Nazad na pocetni meni\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				scanf("\n%[^\n]s", c);
				while ((c[0] != 'M' && c[0] != 'm' && c[0] != 'E' && c[0] != 'e' && c[0] != 'K' && c[0] != 'k' && c[0] != 'P' && c[0] != 'p' && c[0] != 'O' && c[0] != 'o' && c[0] != 'Z' && c[0] != 'z') || c[1] != 0)
				{
					printf("Nepostojeca opcija! Izaberite ponovo: \n");
					scanf("\n%[^\n]s", c);
				}
				if (c[0] == 'M' || c[0] == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (c[0] == 'E' || c[0] == 'e')
				{
					free(lista_dogadjaja);
					exit(1);
				}
				else if (c[0] == 'K' || c[0] == 'k') // K -> Dodavanje komentara za neki dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) unesi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'P' || c[0] == 'p') // P -> Pregled komentara nekog dogadjaja
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) ispisi_komentar(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (c[0] == 'O' || c[0] == 'o') // O -> Pregled opisa nekog dogadjaja
				{
					flag = 0;
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (c[0] == 'Z' || c[0] == 'z') // Z -> zainteresovan za dogadjaj
				{
					flag = 0;
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
			} while (!flag);
			break;
		default:
			printf("\nNepostojeca opcija!\n");
			break;
		}

	}
}