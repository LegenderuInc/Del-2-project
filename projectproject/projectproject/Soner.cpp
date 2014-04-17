#include "Soner.h"
#include "Bokst.h"


Soner::Soner() {
siste = 0;
	for (int i = 0; i < 100; i++) {
		sonene[i] = NULL;
	}
}

Sone* Soner::return_sone(int n){
    Sone* temp_sone;
    if(n < 1 || n > 100){
        return NULL;
    }else{
        temp_sone = sonene[n];
        return temp_sone;
    }
}

void Soner::les_fra_fil(){
    char* temp_filnavn;
    for(int i = 1; i <= MAX_SONE; i++){
        lagNavn(temp_filnavn, sone, dta, i, 11); // Sjekk hvor stort dette blir..
		ifstream* innFil = new ifstream(temp_filnavn);
        
        if(innFil){
            cout << "\nLeser i fra fil: " << temp_filnavn << "\n";
            sonene[i] = new Sone(innFil);
        }
        cout << "\n 404 File not found.";
    }
    
}

void Soner::add_sone() {
	sonene[siste+1] = new Sone(siste + 1);
	siste += 1;
}


void Soner::nytt_oppdrag() {
	int soneNr = les_tall("\nHvilken sone: ", 1, 100);
	if (sonene[soneNr] != NULL) {
		cout << endl;
		sonene[soneNr]->add_oppdrag();
        sonene[soneNr]->sjekk_interesse(soneNr);
	}
	else {
		cout << endl;
		add_sone();
		sonene[siste]->add_oppdrag();
        sonene[siste]->sjekk_interesse(siste);
	}
}


void Soner::display_soneoppdrag(int n) {
	if (sonene[n] != NULL) {
		sonene[n]->display_list();
	}
	else {
		cout << "\n\nAngitt sone eksisterer ikke.\n";
	}
}

void Soner::display_oppdrag(int n) {
	for (int i = 1; i <= 100; i++) {
		if (sonene[i] != NULL && i < 2) {  // FIX Looper av en elle annen grunn en gang for mye. fixet me i < 2
			sonene[i]->display_oppdrag(n);
			
		}
	}
}

void Soner::slettEiendom(){
	int input;

	input = les_tall("\nOppgi oppdrags nummer paa eiendomen du onsker aa slette: ", 1, 100000);
	for(int i = 1; i <= MAX_SONE; i++){
		if(sonene[i] != NULL){
			if(sonene[i]->listCheck(input)){
				sonene[i]->fjernEiendom(input);
				cout << "\n Removal success!!";
				i = MAX_SONE;
			}
		}else {
			cout << "\nFant ingen soner";
		}
	} 
}







