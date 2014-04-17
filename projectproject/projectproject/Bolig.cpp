#include "bolig.h"

Bolig::Bolig() {

}

Bolig::Bolig(int i, int type) : Eiendom(i, type) {	
	byggeAar = les_tall("Byggeaar: ", 1000, 2020);
	bruttoAreal = les_tall("Bruttoareal: ", 0, 999999);
	boAreal = les_tall("Boareal: ", 0, 99999);
	antSoverom = les_tall("Antall soverom: ", 0, 99);
    int temp = les_tall("Salg = 0, Leie = 1, Begge = 2",0 , 2);
    oenske = (Onske)temp; 
}


Bolig::Bolig(ifstream* inn, int n, int type) : Eiendom(inn, n , type){
    int temp;
    byggeAar = les_tall(inn);
    bruttoAreal = les_tall(inn);
    boAreal = les_tall(inn);
    antSoverom = les_tall(inn);
    temp = les_tall(inn);
    oenske = (Onske)temp; 
            
}

void Bolig::display() {
	display_eiendom();
	cout << "\n\tByggeaar: " << byggeAar
		<< "\n\tBrutoareal: " << bruttoAreal << "\n\tBoareal: " << boAreal
		<< "\n\tAntall soverom: " << antSoverom;
}

int Bolig::get_soverom(){
    return antSoverom;
}

int Bolig::get_boareal(){
    return boAreal;
}

Onske Bolig::get_onske(){
    return oenske;
}
void Bolig::skriv_bolig_ukentlig(char* temp_filnavn){
    ofstream utfil(temp_filnavn, ios::app);
    
    utfil << "\nBrutto areal: " << bruttoAreal  << "\n"
            << "Bygge år: " << byggeAar << "\n"
            << "Boareal: " << boAreal << "\n"
            << "Antall soverom: " << antSoverom << "\n";
}
