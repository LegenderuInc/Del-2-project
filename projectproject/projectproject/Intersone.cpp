#include "Intersone.h"
#include "Bolig.h"

using namespace std;

InterSone::InterSone() {

}

InterSone::InterSone(int n) : Num_element(n){
    int temp;
    maxPris = les_tall("\nMaxpris for en eiendom?", MIN_ALL, MAX_ALL);
    minAreal = les_tall("\nMinimums areal for en eiendom?", MIN_ALL, MAX_ALL);
    minRom = les_tall("\nMinst ønsker soverom for et bolig?", MIN_ALL, MAX_ALL);
    temp = les_tall("\nKjøpe = 0, Leie = 1, Begge = 2", 0, 2);
    oenske = (Onske)temp;
    temp = les_tall("\nTomt = 0, Einebolig = 1, Rekkehus = 2, Leilighet = 3, Hytte = 4", 0, 4);
    type = (EiendomsType) temp;
    temp = les_tall("\nUkebilag = 0, Snarest = 1", 0, 1);
}

InterSone::InterSone(int sonenr, int pris, int areal, int sove, int valg, int onske, int eiendom) : Num_element(sonenr) {
    maxPris = pris;
    minAreal = areal;
    minRom = sove;
    boliginfo = (Boliginfo) valg;
    oenske = (Onske) onske;
    type = (EiendomsType) eiendom;
}

InterSone::InterSone(ifstream * inn, int i) : Num_element(i) {
    int temp;
    *inn >> temp;
    boliginfo = (Boliginfo) temp;
    *inn >> temp;
    oenske = (Onske) temp;
    *inn >> temp;
    type = (EiendomsType) temp;
    *inn >> maxPris;
    *inn >> minAreal;
    *inn >> minRom;
}

InterSone::~InterSone() {

}

void InterSone::skriv_til_fil(ofstream & ut) {
    ut << number << "\n"
            << boliginfo << "\n"
            << oenske << "\n"
            << type << "\n"
            << maxPris << "\n"
            << minAreal << "\n"
            << minRom << "\n";
}

int InterSone::get_number() {
    return number;
}

Boliginfo InterSone::sammenling(Element* tilsendt) {
    Eiendom* temp_eiendom;
    Bolig* temp_bolig;
  
    temp_eiendom = (Eiendom*) tilsendt;
    if (temp_eiendom->get_eiendom() == type) {
        if (temp_eiendom->get_eiendom() == tomt) {
            cout << "\n Test, tomt";
            if (maxPris < temp_eiendom->get_pris()) {
                if (minAreal > temp_eiendom->get_areal()) {
                    return boliginfo;
                }
            }
        } else if (temp_eiendom ->get_eiendom() != tomt) {
            temp_bolig = (Bolig*) temp_eiendom;
            if (maxPris > temp_bolig->get_pris()) {
                if (minAreal < temp_bolig->get_boareal()) {
                    if (minRom < temp_bolig->get_soverom()) {
                        if (temp_bolig->get_onske() == oenske || temp_bolig->get_onske() == begge || oenske == begge) {
                            return boliginfo;
                        }
                    }
                }
            }
        } else {
			return boliginfo;
        }
    }
}
	

