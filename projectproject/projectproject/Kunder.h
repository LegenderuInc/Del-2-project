#pragma once
#if !defined(__KUNDER_H)
#define __KUNDER_H
#include"Globalevariabler.h"
#include"Kunde.h"

using namespace std;

class Kunder {
private:
	int forsteK;
    int sistI;
    List* kundelist;
public:
    Kunder();
    ~Kunder();
	void ny_kunde();
	void display();
    void skriv_til_fil();
    void les_fra_fil(ifstream* inn, int i);
    void skrivUkentlig();
    void slettKunde();
    void endreKunde();
    void finn_ny_foerste();
    List* return_list();
};

#endif