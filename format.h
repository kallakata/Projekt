
#ifndef _FORMAT_H
#define _FORMAT_H

enum TypJizdy { osobni = 1, pracovni};

//struct t_auto* prvni = NULL;  //globální ukazatel na první auto

struct t_auto
{
	char id[8]; //Identifikator auta - SPZ
	char znacka[20]; //Znacka auta (Subaru, Skoda, Audi ...)
	enum TypJizdy typ_jizdy; //Pracovni nebo osobni jizda
	char trasa[31]; //Cil cesty
	double UjeteKm_zac; //Kompletní ujete km na tachometru na zacatku cesty
	double UjeteKm_kon; //Kompletní ujete km na tachometru na konci cesty
	double UjeteKm_cesta;
	//struct t_auto* dalsi; //Ukazatel kvùli vazbì

};

typedef struct login
{
	char jmeno[21];
	char prijmeni[21];
	char uziv_jmeno[10];
	char heslo[33];
} User;

void menu(void);
void vypis(void);

void zapis(void);
void login(void);
void registrace(void);
void vypis_txt(void);
void casovac(int millisec);
int proces();
int vypis_id(char* id);


#endif
