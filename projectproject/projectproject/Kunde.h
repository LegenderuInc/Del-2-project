#pragma once
#if !defined(__KUNDE_H)
#define __KUNDE_H

#include "Globalevariabler.h"
#include "Intersone.h"
#include "Sone.h"
#include "const.h"

using namespace std;

class Kunde : public Num_element {
private:
    int telefon;
    int postKode;
    int gateNr;
    char* filnavn;
    char* navn;
    char* adresse;
    char* poststed;
    char* mail;
    List* intSone;
public:
    Kunde();
    Kunde(int nr);
    Kunde(ifstream * infil, int nr);
    ~Kunde();
    void skriv_til_fil();
    virtual void display();
	void display_kunde();
    void add_hurtig(int n);
    void endre_interesse();
    void sjekk_interesser();
    void sjekk_interesser(Element* tilsendt, int n);
    void add_ukentlig(Element* element);
    bool finn_navn(char* temp_navn);
 
    
};
#endif