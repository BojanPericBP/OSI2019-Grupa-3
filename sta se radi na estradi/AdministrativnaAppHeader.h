#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include "AdministrativneFunkcije.h"
#include "KvizHeader.h"
#include "KorisnickaAppHeader.h"


void glavni_meni_administrativne_aplikacije()
{
	system("color 0a");
	system("cls");
	printf("\n********************************************************************************** DOBRO DOSLI ********************************************************************************\n\n");
	printf("                                         Da bi ste odabrali zeljenu opciju unesite odgovarajuci broj!");
	printf("\n     _______________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("                       1: DODAVANJE DOGADJAJA\n");
	printf("                       2: UREDJIVANJE DOGADJAJA\n");
	printf("                       3: BRISANJE DOGADJAJA\n");
	printf("                       4: BRISANJE KATEGORIJE\n");
	printf("                       5: UREDJIVANJE KVIZA\n");
	printf("                       6: PRIKAZ SVIH DOGADJAJA\n");
	printf("     ________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("                       7: POVRATAK NA GLAVNI MENI\n");
	printf("                       0: IZLAZ\n");
	printf("\n*******************************************************************************************************************************************************************************\n\n");
}

void meni_logovanje_administratora(char admin_username[], char admin_pass[])
{
	system("cls");
	printf("\n********************************************************************************** PRIJAVA ************************************************************************************\n");
	printf("Unesite:E-> Za izlazak iz programa\n");
	printf("   ___________________________________________________________________________________________________________________________________________________________________________\n\n");

	logovanje_admina(admin_username,admin_pass);
}

void meni_dodavanje_dogadjaja(char* username)
{
	system("color 0a");
	printf("\n**************************************************************************** DODAVANJE DOGADJAJA ****************************************************************************\n\n");
	dodaj_dogadjaj(username);
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM -> Za nazad\n\tE -> Za izlazak iz programa\n");
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
}
void meni_uredjivanje_dogadjaja()
{
	system("color 0a");
	printf("\n*************************************************************************** UREDJIVANJE DOGADJAJA ***************************************************************************\n\n");
	FILE* fp = fopen("../config files/Dogadjaji/dogadjaji.txt", "r");
	if (fp == NULL)
		exit(1);
	int br_dogadjaja = ucitaj_br_dogadjaja(fp);

	DOGADJAJ* lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja, sizeof(DOGADJAJ));
	ucitaj_dogadjaje_iz_datoteke(fp, lista_dogadjaja, br_dogadjaja);
	zaglavlje_dogadjaja();
	svi_dogadjaji(lista_dogadjaja, br_dogadjaja);
	free(lista_dogadjaja);
	fclose(fp);
	printf("\n\n*******************************************************************************************************************************************************************************\n");
	uredi_dogadjaj();
	printf("\n_____________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("\tUnesite:\n\t\tM-> Za nazad\n\t\tE-> Za izlazak iz programa\n");
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
}

void meni_brisanje_dogadjaja()
{
	system("color 4f");
	
	printf("\n***************************************************************************** BRISANJE DOGADJAJA ****************************************************************************\n\n");
	brisanje_dogadjaja();
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("\tUnesite:\n\t\tM-> Za nazad\n\t\tE-> Za izlazak iz programa\n");
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
}

void meni_brisanje_kategorije()
{
	system("color 0a");
	printf("\n**************************************************************************** BRISANJE KATEGORIJE ****************************************************************************\n\n");
	brisi_kategoriju();
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("\tUnesite:\n\t\tM-> Za nazad\n\t\tE->Za izlazak iz programa\n");
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");

}

void meni_uredjivanje_kviza()
{
	system("color 0a");
	printf("\n***************************************************************************** UREDJIVANJE KVIZA *****************************************************************************\n\n");
	uredjivanje_kviza();
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
	printf("Unesite:\n\tM-> Za nazad\n\tE-> Za izlazak iz programa\n");
	printf("_______________________________________________________________________________________________________________________________________________________________________________\n\n");
}

void odabir_opcije_admina(char* username)
{
	system("title STA SE RADI NA ESTRADI");
	
	char ch;
	int br_dogadjaja, flag = 0;
	DOGADJAJ* lista_dogadjaja;
	FILE* fp;
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
			meni_dodavanje_dogadjaja(username);
			
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


			fp = fopen("../config files/Dogadjaji/dogadjaji.txt", "r");
			if (fp == NULL)
				exit(1);
			br_dogadjaja = ucitaj_br_dogadjaja(fp);

			lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja, sizeof(DOGADJAJ));
			ucitaj_dogadjaje_iz_datoteke(fp, lista_dogadjaja, br_dogadjaja);
			zaglavlje_dogadjaja();
			meni_svih_dogadjaja(lista_dogadjaja, br_dogadjaja);


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
		case '6':
			system("cls");

			fp = fopen("../config files/Dogadjaji/dogadjaji.txt","r");
			if (fp == NULL)
				exit(1);
			br_dogadjaja = ucitaj_br_dogadjaja(fp);

			lista_dogadjaja = (DOGADJAJ*)calloc(br_dogadjaja,sizeof(DOGADJAJ));
			ucitaj_dogadjaje_iz_datoteke(fp, lista_dogadjaja, br_dogadjaja);
			zaglavlje_dogadjaja();
			meni_svih_dogadjaja(lista_dogadjaja,br_dogadjaja);

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
					glavni_meni_administrativne_aplikacije();
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
					char izbor;
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
						meni_svih_dogadjaja(lista_dogadjaja, br_dogadjaja);
					}
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
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
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
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
					else printf("\nNe postoji dogadjaj sa unesenim id-om.\n");
				}
				else if (ch == 'F' || ch == 'f')
				{
					flag = 0;
					printf("\nFILTRIRANJE DOGADJAJA");
					pisi_dogadjaje_filter(lista_dogadjaja, br_dogadjaja);
				}
			} while (!flag);
			break;
			case '7':
				system("cls");
				system("color 5f");
				glavni_meni();
				break;
		default:
			printf("Nepostojeca opcija!\n");
			}
	}
	printf("***************************************************************************\n");
}
