#pragma once
#if !defined(__EIENDOM_H)
#define __EIENDOM_H
#include "Globalevariabler.h"



class Eiendom : public Num_element {
private:
    int datoInn; // Dato for naar oppdraget ble registrert.
    int oppdragsNr; // Oppdragsnummer.
    int intsaksb; // Nummer for intern saksbehandler.
    int bruksNr; // Bruksnummer.
    int pris; // Eiendomens/boligens pris.
    int arealTomt; // Areal pï¿½ tometen.
    char* kommune; // Kommunen tomen ligger i.
    char* postAdr; // Postadresse og std.
    char* gateAdr; // Gateadresse.
    char* eier; // Tomtens nï¿½vï¿½rende eier.
    char* beskrivelse; // En kort bekrivelse av tomten/boligen.
	EiendomsType eiendomsType;	// Bolig type (tomt, eneblog osv).

public:
    Eiendom(); // Default konstruktor
	Eiendom(int n, int type); // Konstruktor som tar oppdragsnummer som parameter.
	Eiendom(ifstream* innFil, int n, int type); // Konstuktor som brukes dersom det leses fra fil.
    virtual void display();
    void display_eiendom(); // Skriver ut informasjon om tomten.
    void skriv_til_fil();
    void skriv_ukentlig(char* filnavn);
    void add_hurtig(int kundeNr);
    void ny_sjekk(Element* tilsendt, int n);
	int get_eiendomsNr();
	int get_postAdr();
    int get_pris();
    int get_number();
    int get_areal();
    ~Eiendom(); // Destructor.
    EiendomsType get_eiendom();


};


#endif