#pragma once
#pragma warning (disable: 4996)
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include "KvizHeader.h"
#include "korisnickeFunkcije.h"
#include "AdministrativnaAppHeader.h"

void glavni_meni_korisnicke_aplikacije();
void odabir_opcije_korisnika(DOGADJAJ*, int, char*);
void meni_logovanje_administratora(char*, char*);
void glavni_meni_administrativne_aplikacije();
void odabir_opcije_admina(char*);

void glavni_meni()
{
	printf("\n******************************************************************************** DOBRO DOSLI **********************************************************************************\n\n");

	char ch;

	printf("Unesite:\n\tA -> za pristup administrativnom dijelu aplikacije.\n\tK -> za pristup korisnickom dijelu aplikacije.\n\tE -> za izlazak iz programa.\n");

	printf("Unos: ");
	ch = _getch();
	char username[21] = {};
	printf("%c", ch);
	while (ch != 'a' && ch != 'A' && ch != 'k' && ch != 'K' && ch != 'e' && ch != 'E')
	{
		printf("\nPogresan unos, unesite ponovo: ");
		ch = _getch();
		printf("%c", ch);
	}

	if (ch == 'e' || ch == 'E')
		exit(1);
	else if (ch == 'k' || ch == 'K')
	{
		FILE* dat_dogadjaji = fopen("../config files/Dogadjaji/dogadjaji.txt", "r");
		if (!dat_dogadjaji) { printf("Neuspjesno ucitavanje datoteke dogadjaji.txt..."); getchar();  exit(1); }

		int br_dogadjaja = ucitaj_br_dogadjaja(dat_dogadjaji);
		DOGADJAJ* lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja, sizeof(DOGADJAJ));

		ucitaj_dogadjaje_iz_datoteke(dat_dogadjaji, lista_dogadjaja, br_dogadjaja);
		fclose(dat_dogadjaji);

		glavni_meni_korisnicke_aplikacije();
		odabir_opcije_korisnika(lista_dogadjaja, br_dogadjaja, username);
	}
	else if (ch == 'a' || ch == 'A')
	{
		char admin_username[21] = {}, admin_pass[21] = {};
		meni_logovanje_administratora(admin_username, admin_pass);

		glavni_meni_administrativne_aplikacije();
		odabir_opcije_admina(admin_username);
	}
}

void inicijalizuj_prozor()
{
	system("title STA SE RADI NA ESTRADI");
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	r.left = 125; r.top = 17;
	MoveWindow(console, r.left, r.top, 1291, 806, TRUE);
	HMENU hmeni = GetSystemMenu(console, FALSE);
	EnableMenuItem(hmeni, SC_CLOSE, MF_GRAYED);
}

void glavni_meni_korisnicke_aplikacije()
{
	system("cls");
	system("color f0");
	printf("\n\n******************************************************************************** DOBRODOSLI ***********************************************************************************\n\n");
	printf("                                                    Da biste odabrali zeljenu opciju unesite odgovarajuci broj!\n");
	printf("     _____________________________________________________________________________________________________________________________________________________________________     \n\n");
	printf("                              1: PREPORUCENI DOGADJAJI\n");
	printf("                              2: PRIKAZ BUDUCIH DOGADJAJA\n");
	printf("                              3: PRIKAZ DANASNJIH DOGADJAJA\n");
	printf("                              4: PRIKAZ PROSLIH DOGADJAJA\n");
	printf("                              5: PRIKAZ SVIH DOGADJAJA\n");
	printf("                              6: ZAIGRAJTE KVIZ\n");
	printf("                              7: RANG LISTA KORISNIKA KOJI SU IGRALI KVIZ\n");
	printf("                              8: POMOC\n");
	printf("                              9: O APLIKACIJI\n");
	printf("     _____________________________________________________________________________________________________________________________________________________________________     \n\n");
	printf("                              0: POVRATAK NA GLAVNI MENI\n");
	printf("\n*******************************************************************************************************************************************************************************\n");
}

void meni_prikaz_preporucenih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n********************************************************************* PREGLED PREPORUCENIH DOGADJAJA **************************************************************************\n");
	zaglavlje_dogadjaja();
	preporuceni_dogadjaji(lista_dogadjaja, br_dogadjaja);
}

void meni_svih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED SVIH DOGADJAJA *****************************************************************************\n");
	zaglavlje_dogadjaja();
	svi_dogadjaji(lista_dogadjaja, br_dogadjaja);
}

int meni_danasnjih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED DANASNJIH DOGADJAJA ************************************************************************\n");
	int flag = danasnji_dogadjaji(lista_dogadjaja, br_dogadjaja);

	return flag;
}

void meni_prosli_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED PROSLIH DOGADJAJA **************************************************************************\n");
	zaglavlje_dogadjaja();
	prosli_dogadjaji(lista_dogadjaja, br_dogadjaja);

}

void meni_buducih_dogadjaja(DOGADJAJ* lista_dogadjaja, int br_dogadjaja)
{
	system("cls");
	system("color 4f");

	printf("\n************************************************************************** PREGLED BUDUCIH DOGADJAJA **************************************************************************\n");
	zaglavlje_dogadjaja();
	buduci_dogadjaji(lista_dogadjaja, br_dogadjaja);
}

void meni_kviza()
{
	system("cls");
	system("color 0b");
	printf("\n************************************************************************ DOBRO DOSLI U KVIZ ***********************************************************************************\n\n");
	igraj_kviz();
	printf("\n\n*******************************************************************************************************************************************************************************\n");
}

void meni_rang_liste()
{
	system("cls");
	system("color 5f");

	printf("\n******************************************************************************* RANG LISTA ************************************************************************************\n\n");
	prikazi_rang_listu();
	printf("\n\n*******************************************************************************************************************************************************************************\n");
}

void meni_help()
{
	system("cls");
	system("color 70");

	printf("\n********************************************************************************* POMOC ***************************************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjaji odrzavaju u nekom gradu, da sazna datum i mjesto odrzavanja dogadjaja, kao i da pogleda komentare drugih korisnika \no nekom dogadjaju.\n"
		"Za detaljne informacije pogledajte korisnicku dokumentaciju.\n");
	printf("\n*******************************************************************************************************************************************************************************\n");
}

void meni_o_korisnickoj_aplikaciji()
{
	system("cls");
	system("color 0a");

	printf("\n************************************************************************ O aplikaciji *****************************************************************************************\n");
	printf("\nAplikacija 'Sta se radi na estradi' je aplikacija koja omogucava pracenje dogadjaja u nekom gradu.\nOmogucava korisniku da pregleda koji se sve dogadjaji odrzavaju u nekom gradu, te datum i mjesto odrzavanja dogadjaja, kao i da pogleda komentare drugih korisnika o \nnekom dogadjaju.\n"
		"\nAplikaciju su radili studenti Elektrotehnickog fakulteta u Banjaluci :\n"
		"Jelena Jakovljevic (Jeca Pereca),\nKristina Krickovic (Kricka),\nSasa Stankovic (Sale),\n"
		"Bojan Janjic (Che),\nBojan Peric (Boki, Bole, Boss)\n");
	printf("\n*******************************************************************************************************************************************************************************\n");
}

void odabir_opcije_korisnika(DOGADJAJ* lista_dogadjaja, int br_dogadjaja,char* username)
{
	int ch = 0, izbor = 0;
	char flag = 0, flag_danasnji = 0;
	while (1)
	{
		ch = _getch();

		switch (ch)
		{
		case '0':
			upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
			free(lista_dogadjaja);
			system("cls");
			system("color 5f");
			glavni_meni();
			break;

		case '1':
			system("cls");
			meni_prikaz_preporucenih_dogadjaja(lista_dogadjaja, br_dogadjaja);
			do {
				printf("\n*******************************************************************************************************************************************************************************\n");
				printf("\nUnesite M ->Nazad\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'K' && ch != 'k' && ch != 'P' && ch != 'p' && ch != 'O' && ch != 'o' && ch != 'Z' && ch != 'z')
				{
					if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
				else if (ch == 'K' || ch == 'k')
				{
					flag = 0;
					printf("\nDODAVANJE KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj)
					{
						trazeni_dogadjaj->komentari = '1';
						if (!strcmp(username, ""))
							unesi_username(username);
						unesi_komentar(temp_id,username);
						printf("\nUspjesno ste unijeli komentar. \n");
						printf("\nUnesite G -> Da pogledate sve komentare ovog dogadjaja\n\tN -> Da nastavite dalje\n");
						izbor = _getch();
						while (izbor != 'G' && izbor != 'g' && izbor != 'N' && izbor != 'n')
						{
							if (izbor != 13 && izbor != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
							izbor = _getch();
						}
						if (izbor == 'G' || izbor == 'g')
						{
							printf("\nSvi komentari dogadjaja %s: \n\n", trazeni_dogadjaj->naziv);
							ispisi_komentar(temp_id);
							printf("\nUnesite -> N za nastavak\n");
							izbor = _getch();
							while (izbor != 'N' && izbor != 'n')
							{
								if (izbor != 13 && izbor != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
								izbor = _getch();
							}
						}
						system("cls");
						meni_prikaz_preporucenih_dogadjaja(lista_dogadjaja, br_dogadjaja);
					}
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'P' || ch == 'p')
				{
					flag = 0;
					printf("\nPREGLED KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '1')
					{
						printf("\nKomentari za dogadjaj: %s\n\n", trazeni_dogadjaj->naziv);
						ispisi_komentar(temp_id);
					}
					else if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '0') printf("\nIzabrani dogadjaj nema komentara.\n");
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'O' || ch == 'o')
				{
					flag = 0;
					printf("\nPREGLED OPISA DOGADJAJA");
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (ch == 'Z' || ch == 'z')
				{
					flag = 0;
					printf("\nZAINTERESOVAN/NA SAM ZA DOGADJAJ");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(trazeni_dogadjaj, temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
			} while (!flag);
			break;

		case '5':
			system("cls");
			meni_svih_dogadjaja(lista_dogadjaja, br_dogadjaja);
			do {
				printf("\n*******************************************************************************************************************************************************************************\n");
				printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n\tF -> Ako zelite da sortirate listu po nekom filtru\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'K' && ch != 'k' && ch != 'P' && ch != 'p' && ch != 'O' && ch != 'o' && ch != 'Z' && ch != 'z' && ch != 'F' && ch != 'f')
				{
					if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
				else if (ch == 'K' || ch == 'k')
				{
					flag = 0;
					printf("\nDODAVANJE KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj)
					{
						trazeni_dogadjaj->komentari = '1';
						if (!strcmp(username, ""))
							unesi_username(username);
						unesi_komentar(temp_id,username);
						printf("\nUspjesno ste unijeli komentar. \n");
						printf("\nUnesite G -> Da pogledate sve komentare ovog dogadjaja\n\tN -> Da nastavite dalje\n");
						izbor = _getch();
						while (izbor != 'G' && izbor != 'g' && izbor != 'N' && izbor != 'n')
						{
							if (izbor != 13 && izbor != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
							izbor = _getch();
						}
						if (izbor == 'G' || izbor == 'g')
						{
							printf("\nSvi komentari dogadjaja %s: \n\n", trazeni_dogadjaj->naziv);
							ispisi_komentar(temp_id);
							printf("\nUnesite N -> za nastavak\n");
							izbor = _getch();
							while (izbor != 'N' && izbor != 'n')
							{
								if (izbor != 13 && izbor != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
								izbor = _getch();
							}
						}
						system("cls");
						meni_svih_dogadjaja(lista_dogadjaja, br_dogadjaja);
					}
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'P' || ch == 'p')
				{
					flag = 0;
					printf("\nPREGLED KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '1')
					{
						printf("\nKomentari za dogadjaj %s:\n\n", trazeni_dogadjaj->naziv);
						ispisi_komentar(temp_id);
					}
					else if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '0') printf("\nIzabrani dogadjaj nema komentara.\n");
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'O' || ch == 'o')
				{
					flag = 0;
					printf("\nPREGLED OPISA DOGADJAJA");
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (ch == 'Z' || ch == 'z')
				{
					flag = 0;
					printf("\nZAINTERESOVAN/NA SAM ZA DOGADJAJ");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(trazeni_dogadjaj, temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'F' || ch == 'f')
				{
					flag = 0;
					printf("\nFILTRIRANJE DOGADJAJA");
					pisi_dogadjaje_filter(lista_dogadjaja, br_dogadjaja);
				}
			} while (!flag);
			break;

		case '6':
			system("cls");

			meni_kviza();
			printf("\nUnesite M ->Nazad\n\tE -> Izlaz iz programa\n");
			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
			{
				upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '7':
			system("cls");

			meni_rang_liste();
			printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n");
			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
			{
				upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '9':
			system("cls");
			meni_o_korisnickoj_aplikaciji();
			printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n");
			ch = _getch();
			while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
			{
				if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
				ch = _getch();
			}
			if (ch == 'M' || ch == 'm')
			{
				system("cls");
				glavni_meni_korisnicke_aplikacije();
			}
			else if (ch == 'E' || ch == 'e')
			{
				upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
				free(lista_dogadjaja);
				exit(1);
			}

			break;
		case '8':
			system("cls");
			meni_help();
			do
			{
				printf("\nUnesite D -> Pregled korisnicke dokumentacije\n\tM -> Nazad\n\tE -> Izlaz iz programa\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'D' && ch != 'd')
				{
					if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
					flag = 1;
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
				else if (ch == 'D' || ch == 'd')
				{
					flag = 0;
					system("\"\"../config files/Korisnicka dokumentacija/Dokumentacija.docx\"\"");
				}
			} while (!flag);
			break;
		case '3':
			system("cls");
			flag_danasnji = meni_danasnjih_dogadjaja(lista_dogadjaja, br_dogadjaja);
			if (flag_danasnji)
			{
				do {
					printf("\n*******************************************************************************************************************************************************************************\n");
					printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
					ch = _getch();
					while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'K' && ch != 'k' && ch != 'P' && ch != 'p' && ch != 'O' && ch != 'o' && ch != 'Z' && ch != 'z')
					{
						if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
						ch = _getch();
					}
					if (ch == 'M' || ch == 'm')
					{
						system("cls");
						flag = 1;
						glavni_meni_korisnicke_aplikacije();
					}
					else if (ch == 'E' || ch == 'e')
					{
						upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
						free(lista_dogadjaja);
						exit(1);
					}
					else if (ch == 'K' || ch == 'k')
					{
						flag = 0;
						printf("\nDODAVANJE KOMENTARA");
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj)
						{
							trazeni_dogadjaj->komentari = '1';
							if (!strcmp(username, ""))
								unesi_username(username);
							unesi_komentar(temp_id,username);
							printf("\nUspjesno ste unijeli komentar. \n");
							printf("\nUnesite G -> Da pogledate sve komentare ovog dogadjaja\n\tN -> Da nastavite dalje\n");
							izbor = _getch();
							while (izbor != 'G' && izbor != 'g' && izbor != 'N' && izbor != 'n')
							{
								if (izbor != 13 && izbor != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
								izbor = _getch();
							}
							if (izbor == 'G' || izbor == 'g')
							{
								printf("\nSvi komentari dogadjaja %s: \n\n", trazeni_dogadjaj->naziv);
								ispisi_komentar(temp_id);
								printf("\nUnesite -> N za nastavak\n");
								izbor = _getch();
								while (izbor != 'N' && izbor != 'n')
								{
									if (izbor != 13 && izbor != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
									izbor = _getch();
								}
							}
							system("cls");
							meni_danasnjih_dogadjaja(lista_dogadjaja, br_dogadjaja);
						}
						else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
					}
					else if (ch == 'P' || ch == 'p')
					{
						flag = 0;
						printf("\nPREGLED KOMENTARA");
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '1')
						{
							printf("\nKomentari za dogadjaj %s:\n\n", trazeni_dogadjaj->naziv);
							ispisi_komentar(temp_id);
						}
						else if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '0') printf("\nIzabrani dogadjaj nema komentara.\n");
						else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
					}
					else if (ch == 'O' || ch == 'o')
					{
						flag = 0;
						printf("\nPREGLED OPISA DOGADJAJA");
						prikazi_opis(lista_dogadjaja, br_dogadjaja);
					}
					else if (ch == 'Z' || ch == 'z')
					{
						flag = 0;
						printf("\nZAINTERESOVAN/NA SAM ZA DOGADJAJ");
						int temp_id = unesi_id();
						DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
						if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(trazeni_dogadjaj, temp_id);
						else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
					}
				} while (!flag);
			}
			else
			{
				printf("\n*******************************************************************************************************************************************************************************\n");
				printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e')
				{
					if (ch != 13 && ch != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					glavni_meni_korisnicke_aplikacije();
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
			}
			break;
		case '4':
			system("cls");
			meni_prosli_dogadjaja(lista_dogadjaja, br_dogadjaja);
			do {
				printf("\n*******************************************************************************************************************************************************************************\n");
				printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'K' && ch != 'k' && ch != 'P' && ch != 'p' && ch != 'O' && ch != 'o' && ch != 'Z' && ch != 'z')
				{
					if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
				else if (ch == 'K' || ch == 'k')
				{
					flag = 0;
					printf("\nDODAVANJE KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj)
					{
						trazeni_dogadjaj->komentari = '1';
						if (!strcmp(username, ""))
							unesi_username(username);
						unesi_komentar(temp_id,username);
						printf("\nUspjesno ste unijeli komentar. \n");
						printf("\nUnesite G -> Da pogledate sve komentare ovog dogadjaja\n\tN -> Da nastavite dalje\n");
						izbor = _getch();
						while (izbor != 'G' && izbor != 'g' && izbor != 'N' && izbor != 'n')
						{
							if (izbor != 13 && izbor != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
							izbor = _getch();
						}
						if (izbor == 'G' || izbor == 'g')
						{
							printf("\nSvi komentari dogadjaja %s: \n\n", trazeni_dogadjaj->naziv);
							ispisi_komentar(temp_id);
							printf("\nUnesite -> N za nastavak\n");
							izbor = _getch();
							while (izbor != 'N' && izbor != 'n')
							{
								if (izbor != 13 && izbor != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
								izbor = _getch();
							}
						}
						system("cls");
						meni_prosli_dogadjaja(lista_dogadjaja, br_dogadjaja);
					}
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'P' || ch == 'p')
				{
					flag = 0;
					printf("\nPREGLED KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '1')
					{
						printf("\nKomentari za dogadjaj %s:\n\n", trazeni_dogadjaj->naziv);
						ispisi_komentar(temp_id);
					}
					else if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '0') printf("\nIzabrani dogadjaj nema komentara.\n");
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'O' || ch == 'o')
				{
					flag = 0;
					printf("\nPREGLED OPISA DOGADJAJA");
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (ch == 'Z' || ch == 'z')
				{
					flag = 0;
					printf("\nZAINTERESOVAN/NA SAM ZA DOGADJAJ");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(trazeni_dogadjaj, temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
			} while (!flag);
			break;
		case '2':
			system("cls");
			meni_buducih_dogadjaja(lista_dogadjaja, br_dogadjaja);
			do
			{
				printf("\n*******************************************************************************************************************************************************************************\n");
				printf("\nUnesite M -> Nazad\n\tE -> Izlaz iz programa\n\tK -> Dodavanje komentara za neki dogadjaj\n\tP -> Pregled komentara nekog dogadjaja\n\tO -> Pogledaj opis dogadjaja\n\tZ -> Da oznacite da ste zainteresovani za neki dogadjaj\n");
				ch = _getch();
				while (ch != 'M' && ch != 'm' && ch != 'E' && ch != 'e' && ch != 'K' && ch != 'k' && ch != 'P' && ch != 'p' && ch != 'O' && ch != 'o' && ch != 'Z' && ch != 'z')
				{
					if (ch != 13 && ch != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
					ch = _getch();
				}
				if (ch == 'M' || ch == 'm')
				{
					system("cls");
					flag = 1;
					glavni_meni_korisnicke_aplikacije();
				}
				else if (ch == 'E' || ch == 'e')
				{
					upisi_u_datoteku(lista_dogadjaja, br_dogadjaja);
					free(lista_dogadjaja);
					exit(1);
				}
				else if (ch == 'K' || ch == 'k')
				{
					flag = 0;
					printf("\nDODAVANJE KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj)
					{
						trazeni_dogadjaj->komentari = '1';
						if (!strcmp(username, ""))
							unesi_username(username);
						unesi_komentar(temp_id, username);
						printf("\nUspjesno ste unijeli komentar. \n");
						printf("\nUnesite G -> Da pogledate sve komentare ovog dogadjaja\n\tN -> Da nastavite dalje\n");
						izbor = _getch();
						while (izbor != 'G' && izbor != 'g' && izbor != 'N' && izbor != 'n')
						{
							if (izbor != 13 && izbor != 32) printf("\nNepostojeca opcija! Izaberite ponovo: \n");
							izbor = _getch();
						}
						if (izbor == 'G' || izbor == 'g')
						{
							printf("\nSvi komentari dogadjaja %s: \n", trazeni_dogadjaj->naziv);
							ispisi_komentar(temp_id);
							printf("\nUnesite -> N za nastavak\n");
							izbor = _getch();
							while (izbor != 'N' && izbor != 'n')
							{
								if (izbor != 13 && izbor != 32) printf("Nepostojeca opcija! Izaberite ponovo: \n");
								izbor = _getch();
							}
						}
						system("cls");
						meni_buducih_dogadjaja(lista_dogadjaja, br_dogadjaja);
					}
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'P' || ch == 'p')
				{
					flag = 0;
					printf("\nPREGLED KOMENTARA");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '1')
					{
						printf("\nKomentari za dogadjaj %s:\n\n", trazeni_dogadjaj->naziv);
						ispisi_komentar(temp_id);
					}
					else if (trazeni_dogadjaj && trazeni_dogadjaj->komentari == '0') printf("\nIzabrani dogadjaj nema komentara.\n");
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
				else if (ch == 'O' || ch == 'o')
				{
					flag = 0;
					printf("\nPREGLED OPISA DOGADJAJA");
					prikazi_opis(lista_dogadjaja, br_dogadjaja);
				}
				else if (ch == 'Z' || ch == 'z')
				{
					flag = 0;
					printf("\nZAINTERESOVAN/NA SAM ZA DOGADJAJ");
					int temp_id = unesi_id();
					DOGADJAJ* trazeni_dogadjaj = trazi_dogadjaj_id(lista_dogadjaja, br_dogadjaja, temp_id);
					if (trazeni_dogadjaj) zainteresovan_za_dogadjaj(trazeni_dogadjaj, temp_id);
					else printf("\nNe postoji dogadjaj sa unesenim identifikacionim brojem.\n");
				}
			} while (!flag);
			break;
		default:
			if (ch != 13 && ch != 32) printf("Nepostojeca opcija!\n");
			break;
		}
	}
}