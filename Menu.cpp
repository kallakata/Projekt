#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <string.h>
#include "format.h"

#define _CRT_SECURE_NO_WARNINGS

void menu(void)
{
	int choice = 0; //Pomocna promenna pro vyber cinnosti
	printf_s("======================\n");
	printf_s("         MENU         \n");
	printf_s("======================\n");
	printf_s("Zadejte \"1\" pro vypis zaznamu\n");
	printf_s("Zadejte \"2\"  pro zapis noveho zaznamu\n");
	printf_s("Zadejte \"3\" pro konec programu\n");
	scanf_s("%d", &choice);

	switch (choice)
	{
		case 1:
			system("cls");
			vypis();
			break;
		case 2:
			system("cls");
			zapis();
			break;
		case 3:
			printf_s("Konec programu.\n");
			exit(0);
			break;
		default:
			printf_s("Spatny vyber\n");
			casovac(2500);
			system("cls"); //Vycisteni konzole
			menu();
	}
}

void vypis(void)
{
	int choice = 0;
	printf_s("======================\n");
	printf_s("    Vypis zaznamu     \n");
	printf_s("======================\n");
	printf_s("Zadejte \"1\" pro vyhledani auta dle jeho ID\n");
	printf_s("Zadejte \"2\"  pro vypis vsech zaznamu\n");
	printf_s("Zadejte \"3\" pro navrat do hlavniho menu\n");
	printf_s("Zadejte \"4\" pro konec programu\n");
	scanf_s("%d", &choice);
	char hledane_id[8];
	int p = 2; //pomocna promena
	int a = 0;
	switch (choice)
	{
	case 1:
	{
		printf_s("Zadejte ID automobilu: \n");
		scanf_s("%7c", &hledane_id, 8);
		a = vypis_id(hledane_id);
		casovac(2500);
		printf_s("Zadejte \"1\" pro delsi cas a \"0\" pro navrat do hlavniho menu\n");
		scanf_s("%d", &p);
		if (p == 1)
		{
			printf_s("Zadal jste delsi cas, mate 5 minut do navratu do hlavniho menu\n");
			casovac(300000);
			system("cls");
			menu();
		}
		else if (p == 0)
		{
			printf_s("Zadal jste navrat do hlavniho menu\n");
			casovac(2500);
			system("cls");
			menu();
		}
		else
		{
			printf_s("Spatny vyber, program se vypina\n");
			exit(0);
		}
		break;
	}
	case 2:
	{
		vypis_txt();
		casovac(2500);
		printf_s("Zadejte \"1\" pro delsi cas a \"0\" pro navrat do hlavniho menu\n");
		scanf_s("%d", &p);
		if (p == 1)
		{
			printf_s("Zadal jste delsi cas, mate 5 minut do navratu do hlavniho menu\n");
			casovac(300000);
			system("cls");
			menu();
		}
		else if (p == 0)
		{
			printf_s("Zadal jste navrat do hlavniho menu\n");
			casovac(2500);
			system("cls");
			menu();
		}
		else
		{
			printf_s("Spatny vyber, program se vypina\n");
			exit(0);
		}
		break;
	}
	case 3:
		printf_s("Zvolili jste navrat do hlavniho menu\n");
		casovac(2500);
		system("cls");
		menu();
		break;
	case 4:
		printf_s("Konec programu.\n");
		exit(0);
		break;
	default:
		printf_s("Spatny vyber\n");
		vypis();
	}

}

int vypis_id(char* id)
{
	FILE* cteni;

	errno_t err = fopen_s(&cteni, "databaze.txt", "r");
	if (err != 0 || cteni == 0) {
		fprintf(stderr, "Chyba pri otevirani souboru\n");
		return 1;
	}

	t_auto car;
	bool exist = false;
	//cteni vsech zaznamu
	while (fread_s(&car, sizeof(t_auto), sizeof(t_auto), 1, cteni)) {
		//pokud shoda
		if (!strcmp(car.id, id)) {
			//nalezeno
			exist = true;
			printf_s("%-8s, %-20s, %-9s, %-30s, %-.2ls, %-.2ls %-.2ls\n", car.id, car.znacka, car.typ_jizdy == 1 ? "Soukroma" : "Sluzebni", car.trasa, car.UjeteKm_zac, car.UjeteKm_kon, car.UjeteKm_kon);
			//ukonceni hledani
			break;
		}
	}
	if (!exist)
		printf("Zaznam s ID=%s nenalezen\n", id);

	fclose(cteni);
	return 0;
}

void zapis(void)
{

	printf_s("======================\n");
	printf_s("    Zapis zaznamu     \n");
	printf_s("======================\n");

	struct t_auto novy;

	printf_s("Zadejte ID automobilu: \n");
	scanf_s("%7s", novy.id, 8);

	printf_s("Zadejte znacku automobilu: \n");
	scanf_s("%19s", novy.znacka, (unsigned)_countof(novy.znacka));
	printf_s("Zadejte \"1\" zda se jedna o osobni nebo \"2\" zda se jedna o pracovni jizdu\n");
	scanf_s("%d", &novy.typ_jizdy);

	printf_s("Zadejte cil cesty. MAX 30 znaku.\n");
	scanf_s("%30s", novy.trasa, 31);

	printf_s("Zadejte ujete km na zacatku cesty: \n");
	scanf_s("%lf", &novy.UjeteKm_zac);

	printf_s("Zadejte ujete km na konci cesty: \n");
	scanf_s("%lf", &novy.UjeteKm_kon);

	novy.UjeteKm_cesta = (novy.UjeteKm_kon - novy.UjeteKm_zac);

	FILE *dalsi_zapis;
	fopen_s(&dalsi_zapis, "databaze.txt", "a");

	if (dalsi_zapis == NULL)
	{
		printf_s("Soubor se nepodarilo otevrit.\n");
	}
	else
	{
		int size = fwrite(&novy, sizeof(struct t_auto), 1, dalsi_zapis);
		if (size != 0)
			printf("Zapis se provedl v poradku.\n");
		else
			printf("Nastala chyba pri zapisu.\n");
	}

	fclose(dalsi_zapis);

	printf_s("Zadejte \"1\" pro dalsi zapis\n");
	printf_s("Zadejte \"2\" pro navrat do hlavniho menu\n");
	printf_s("Zadejte \"3\" pro konec programu\n");
	int choice;
	scanf_s("%d", &choice);	

	switch (choice)
	{
	case 1:
		system("cls");
		zapis();
		break;
	case 2:
		printf_s("Zvolili jste navrat do hlavniho menu\n");
		casovac(2500);
		system("cls");
		menu();
		break;
	case 3:
		printf_s("Konec programu.");
		exit(0);
		break;	
	default:
		printf_s("Spatny vyber");
		casovac(2500);
		system("cls");
		zapis();
		break;
	}

}

void vypis_txt(void) //tisk vsech zapisu
{
	FILE* cteni;

	errno_t err = fopen_s(&cteni, "databaze.txt", "r");
	if (err != 0 || cteni == 0) {
		fprintf(stderr, "Chyba pri otevirani souboru\n");
		return;
	}
	struct t_auto car;
	printf_s("SPZ     , Znacka              , Typ jizdy       , Trasa                              , Tachometr na zaèátku        , Tachometr na konci      , Ujete km        \n");

	while (fread_s(&car, sizeof(struct t_auto), sizeof(struct t_auto), 1, cteni)) {
	    printf_s("%8s, %19s, %9s, %30s, %lf, %lf %lf\n", car.id, car.znacka, car.typ_jizdy == 1 ? "Soukroma" : "Sluzebni", car.trasa, car.UjeteKm_zac, car.UjeteKm_kon, car.UjeteKm_cesta);
	}

	fclose(cteni);
}

void casovac(int millisec)
{

	int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
	int end = milliseconds_since + millisec;

	do {
		milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;

	} while (milliseconds_since <= end);
}


int proces(void)
{
	int volba;
	printf("Zmacknete\n1 pro registraci\n2 pro login\n");
	scanf_s("%d", &volba);
	int a = 0;
	switch (volba)
	{
	case 1:
		system("cls");
		registrace();
		break;
	case 2:
		system("cls");
		login();
		break;
	default:
		printf_s("Spatny vyber\n");
		casovac(2500);
		system("cls");
		a = proces();
	}
	return 0;
}

void login()
{
	char name[10], passw[33];
	bool exist = false;
	FILE* log;
	errno_t err = fopen_s(&log, "login.txt", "r");

	if (log == NULL)
	{
		fputs("Chyba souboru!\n", stderr);
		exit(1);
	}
	User user;


	printf("\nZadejte sve registracni udaje\n\n");
	printf("Uzivatelske jmeno: \n");
	scanf_s("%9s", &name, 10);
	printf("Heslo: \n");
	scanf_s("%32s", &passw, 33);

	while (fread_s(&user, sizeof(User), sizeof(User), 1, log))
	{
		printf("%s\n",user.uziv_jmeno);
		if (!strcmp(name, user.uziv_jmeno) && !strcmp(passw, user.heslo))
		{

			exist = true;
			printf("Uspesne prihlaseno\n");
			casovac(2500);
			break;
		}
	}
	fclose(log);

	if (!exist) {
			printf("Spatne uzivatelske jmeno, nebo heslo! Stisknete klavesu pro navrat do hlavniho menu\n");
			getchar();
			getchar();
			system("cls");
			int a = proces();
	}
	return;
}

void registrace(void)
{
	User l;
	FILE* log;

	fopen_s(&log, "login.txt", "w");
	if (log == NULL)
	{
		fputs("Chyba v souboru!\n", stderr);
		exit(1);
		system("cls");
	}


	printf("\nVitejte v elektronicke knize jizd! Zase sve udaje nize\n\n");
	printf("\nZadejte vase krestni jmeno: \n");
	scanf_s("%20s", l.jmeno, 21);
	printf("\nZadejte prijmeni: \n");
	scanf_s("%20s", l.prijmeni, 21);

	printf("Zadejte prosim prihlasovaci udaje, kterymi se budete do sve knihy prihlasovat.\nDurazne doporucujeme pouzit mala a velka pismena, znaky i cislice\n");

	printf("\nZadejte uzivatelske jmeno: \n");
	scanf_s("%9s", l.uziv_jmeno, 10);
	printf("\nZadejte heslo: \n");
	scanf_s("%32s", l.heslo, 33);


	fwrite(&l, sizeof(l), 1, log);
	fclose(log);

	printf("\nPotvrzovani prihlaseni...\n...\Vitejte, %s!\n\n", l.jmeno);
	printf("\nRegistrace uspesna!\n");
	printf("Zmacknete jakoukoliv klavesu..");
	getchar();
	getchar();
}