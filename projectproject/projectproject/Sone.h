#pragma once
#if !defined(__SONE_H)
#define __SONE_H
#include "Globalevariabler.h"
#include "Eiendom.h"
#include "Bolig.h"


class Sone {
private:
    char* beskrivelse;
	List* eiendomene;
    
public:
	Sone(int siste);
	Sone(ifstream* inn);
	void skriv_til_fil(ofstream* ut);
	void add_oppdrag();
	void display_list();
	void display_oppdrag(int n);
	void fjernEiendom(int n);
    void sjekk_interesse(int n);
	bool listCheck(int n);
    List* get_list();
};

#endif