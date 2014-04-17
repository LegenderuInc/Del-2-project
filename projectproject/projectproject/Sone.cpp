#include "Sone.h"
#include "Globalevariabler.h"
#include "Bokst.h"

Sone::Sone(int siste) {

    beskrivelse = les_text("Gi en kort beskrivelse av sonen: ");
    eiendomene = new List(Sorted);
    char* filNavn = new char[50];
    lagNavn(filNavn, "SONE", ".DTA", siste, 3);
    ofstream *utFil = new ofstream(filNavn);
    *utFil << beskrivelse << endl;
}

Sone::Sone(ifstream* inn) {
    eiendomene = new List(Sorted);
    Eiendom* temp_eiendom;
    Bolig* temp_bolig;
    int temp_oppdrag, antEiendomer, temp_type;
    char* filnavn;
    
	beskrivelse = les_text(inn);
    antEiendomer = les_tall(inn);
    for (int i = 1; i <= antEiendomer; i++){
        temp_oppdrag = les_tall(inn);
        temp_type = les_tall(inn);
        lagNavn(filnavn, e, dta, temp_oppdrag, 7);
		ifstream* innFil = new ifstream(filnavn);
        if(temp_type == 0 && innFil->is_open()){
        temp_eiendom = new Eiendom(innFil, temp_oppdrag, temp_type);
        eiendomene->add(temp_eiendom);
        delete temp_eiendom;
        }else if(innFil){
            temp_bolig = new Bolig(innFil, temp_oppdrag, temp_type);
            eiendomene->add(temp_bolig);
            delete temp_bolig;
        }
        innFil->close();
    }
 }

void Sone::skriv_til_fil(ofstream * ut) {
    Eiendom* temp;
    *ut //<< number << "\n"
            << beskrivelse << "\n";

    int antEiendom = eiendomene->no_of_elements();
    *ut << antEiendom << "\n";

    for (int i = 1; i <= antEiendom; i++) {
        temp = (Eiendom*) eiendomene->remove_no(i);
        *ut << temp->get_number() << "\n";
        *ut << temp->get_eiendom() << "\n"; 
        temp->skriv_til_fil();
        eiendomene->add(temp);
    }
}

void Sone::add_oppdrag() {
    EiendomsType eiendomsType = les_eiendomstype();

    if (eiendomsType == tomt) {
        Eiendom* temp;
		temp = new Eiendom(23000, eiendomsType); //FIX sitebrukt + 1
        eiendomene->add(temp);
    } else {
        Bolig* temp;
		temp = new Bolig(23000, eiendomsType); //FIX sistebrukt + 1
        eiendomene->add(temp);
    }
}

void Sone::display_list() {
	eiendomene->display_list();
}

void Sone::display_oppdrag(int n) {
	if (eiendomene->in_list(n)) {
		eiendomene->display_element(n);
	}
	// FIX
}



bool Sone::listCheck(int n){
	return(eiendomene->in_list(n));
}

void Sone::fjernEiendom(int n){
	Eiendom* temp;
	temp = (Eiendom*) eiendomene->remove_no(n);
	delete temp;
}

void Sone::sjekk_interesse(int n){
    Eiendom* temp_eiendom;
        
    temp_eiendom = (Eiendom*) eiendomene->remove_no(eiendomene->no_of_elements());
    temp_eiendom->ny_sjekk(temp_eiendom, n);
    eiendomene->add(temp_eiendom);
}

List* Sone::get_list(){
    return eiendomene;
}







