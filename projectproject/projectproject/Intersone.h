#pragma once
#if !defined(__INTERSONE_H)
#define __INTERSONE_H

#include "Globalevariabler.h"


using namespace std;

class InterSone : public Num_element {
private:
    int maxPris, minAreal, minRom;
    Boliginfo boliginfo;
    Onske oenske;
    EiendomsType type;

public:
    InterSone();
    InterSone(int n);
    InterSone(ifstream* inn, int i);
	InterSone(int sonenr, int pris, int areal, int sove, int valg, int onske, int eiendom);
    ~InterSone();
    void skriv_til_fil(ofstream & ut);
    Boliginfo sammenling(Element* tilsendt);
    int get_number();

};

#endif
