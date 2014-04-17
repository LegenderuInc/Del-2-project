#include"Kunde.h"

using namespace std;

Kunde::Kunde() {
    cout << "empty";
}

Kunde::Kunde(int nr) : Num_element(nr) {
    int temp_pris, temp_areal, temp_rom, temp_valg, temp_onske, temp_eiendom, temp_sone;
    InterSone* temp_class;
    intSone = new List(Sorted);

    navn = les_text("Navn");
    adresse = les_text("Adresse");
    poststed = les_text("Sted");
    mail = les_text("Mail");

    telefon = les_tall("Tlf", MIN_TLF, MAX_TLF);
    gateNr = les_tall("Gate nr", MIN_GATE, MAX_GATE);
    postKode = les_tall("Postadr", MIN_POST, MAX_POST);

    temp_sone = les_tall("\nOppgi hvilken sone kunden er intresert i: ", MIN_SONE, MAX_SONE);
    temp_pris = les_tall("Vennligst oppgi kundens maksimale prisnivaa", MIN_ALL, MAX_ALL);
    temp_areal = les_tall("\nKundens minimumskrav for areal: ", MIN_ALL, MAX_ALL);
    temp_rom = les_tall("\nKundens minimums krav for antall soverom: ", MIN_ALL, MAX_ALL);
    temp_valg = les_tall("\nHvilken maate onsker kunden aa motta info om nye boliger? \n Ukentlig = 0, Snarest = 1.", 0, 1);
    temp_onske = les_tall("\nHva onsker kunden aa? \n Kjope = 0, Leie = 1, Beggedeler = 2", 0, 2);
    temp_eiendom = les_tall("\nHvilken type eiendom\bolig er kunden intresert i? \nTomt = 0, Enebolig = 1, Rekkehus = 2, Leilighet = 3, Hytte = 4", 0, 4);

    while (temp_sone) {
        if (intSone->in_list(temp_sone)) {
            cout << "\nDenne sonen er allerede lagt inn i interesse listen.";
        } else {
            temp_class = new InterSone(temp_sone, temp_pris, temp_areal, temp_rom, temp_valg, temp_onske, temp_eiendom);
            intSone -> add(temp_class);
        }
        temp_sone = les_tall("\nSkriv inn Sone nr. kunden er intresert i 1-100, \nSkriv inn 0 for aa slutte.", 0, MAX_SONE);
    }
}

Kunde::Kunde(ifstream * infil, int nr) : Num_element(nr) {
    int antSoner, soneNumb;

    navn = les_text(infil);
    adresse = les_text(infil);
    poststed = les_text(infil);
    mail = les_text(infil);

    *infil >> telefon;
    *infil >> gateNr;
    *infil >> postKode;
    *infil >> antSoner;

    for (int i = 1; i <= antSoner; i++) {
        InterSone* temp;
        *infil >> soneNumb;
        temp = new InterSone(infil, soneNumb);
        intSone->add(temp);
        delete temp;
    }

}

void Kunde::skriv_til_fil() {
    InterSone* temp;
    lagNavn(filnavn, "K", ".DTA", number, 7);

    ofstream utfil(filnavn);

    utfil << number << "\n"
            << navn << "\n"
            << adresse << "\n"
            << poststed << "\n"
            << mail << "\n"
            << telefon << "\n"
            << gateNr << "\n"
            << postKode << "\n";

    int antSoner = intSone->no_of_elements();
    utfil << antSoner << "\n";
    for (int i = 1; i <= antSoner; i++) {
        temp = (InterSone*) intSone->remove_no(i);
        temp->skriv_til_fil(utfil);
        intSone->add(temp);
    }


}

void Kunde::display() {
    display_kunde();
}

void Kunde::display_kunde() {
    cout << "\nKundens navn: " << navn
            << "\nKundens filnavn:" << filnavn
            << "\nTelefon: " << telefon
            << "\nAdresse: " << adresse << " " << gateNr
            << "\n \t" << postKode << " " << poststed
            << "\nEpost adresse: " << mail;
    intSone->display_list();
}

Kunde::~Kunde() {

}

void Kunde::sjekk_interesser() {
    InterSone* temp_interesse;
    Sone* temp_sone = NULL;
    List* temp_eiendomlist = new List(Sorted);
    Eiendom* temp_eiendom;

    for (int i = 1; i <= intSone->no_of_elements(); i++) {
        temp_interesse = (InterSone*) intSone->remove_no(i);
        temp_sone = mSoner.return_sone(temp_interesse->get_number());

        if (temp_sone) {
            temp_eiendomlist = temp_sone->get_list();
            for (int l = 1; l <= temp_eiendomlist->no_of_elements(); l++) {
                temp_eiendom = (Eiendom*) temp_eiendomlist->remove_no(l);
                if (temp_interesse->sammenling(temp_eiendom) == Ukentlig/* && skrivRaport == true*/) { // , 
                    //trenger ett parameter til for å sørge for at add_ukentlig ikke blir skrevet før den er lagdt inn, eller må vi lage en ny nesten identisk fuksjon.
                    add_ukentlig(temp_eiendom);
                } else if (temp_interesse->sammenling(temp_eiendom) == Snarest/* && skrivRaport == false*/) {
                    add_hurtig(temp_eiendom->get_number());
                } else {
                    cout << "\nSer ut til at dette er ikke interesang for kunden";
                }
            }
        }

    }
}

void Kunde::sjekk_interesser(Element* tilsendt, int n) {
    InterSone* temp_interesse;
    Eiendom* temp_eiendom = (Eiendom*) tilsendt;

    if (intSone->in_list(n)) {
        temp_interesse = (InterSone*) intSone->remove(n);
        if (temp_interesse->sammenling(temp_eiendom) == Snarest) {
            add_hurtig(temp_eiendom->get_number()); //Byttett slik at funksjonen ligger i Kunde Scope
        }
    }

}

void Kunde::add_ukentlig(Element* temp_element) {
    char* temp_filnavn = new char[STRLEN];
    Eiendom* temp_eiendom;
    Bolig* temp_bolig;
    lagNavn(temp_filnavn, "K", ".INF", number, 7);
    ifstream filsjekk(temp_filnavn);
    temp_eiendom = (Eiendom*) temp_element;


    if (filsjekk.is_open()) {
        ofstream utfil(temp_filnavn);
        utfil << navn << "\n"
                << "Telefon: \t" << telefon << "\n"
                << "Adresse: \t" << adresse << " " << gateNr << "\n"
                << "\t\t" << poststed << " " << postKode << "\n"
                << "E-mail: \t" << mail << "\n"
                << "\n\n Følgende eiendomer burde intresere dem. \n";
    }
    ofstream utfil(temp_filnavn);
    if (temp_eiendom->get_type() == tomt) {
        temp_eiendom->skriv_ukentlig(temp_filnavn);
    } else {
        temp_bolig = (Bolig*) temp_eiendom;
        temp_bolig->skriv_ukentlig(temp_filnavn);
        temp_bolig->skriv_bolig_ukentlig(temp_filnavn);
    }
    utfil << "\n----------------------------------------------------------";

}

void Kunde::endre_interesse() {
    InterSone* temp_inter;
    int temp_sone;

    cout << "\nDisplayer tilgjenelige interessesoner...";
    intSone->display_list();

    temp_sone = les_tall("\nHvilken sone ønsker de å endre?, 0 for å avslutte", MIN_SONE, MAX_SONE);

    while (temp_sone != 0) {
        if (intSone->in_list(temp_sone)) {
            temp_inter = (InterSone*) intSone->remove(temp_sone);
            delete temp_inter;
            intSone->add(new InterSone(temp_sone));
        } else {
            temp_sone("\nDen sonen du øsnker å endre finner ikke, hvilken sone ønsker de å denre (1-100), 0 for å avslutte");
        }
    }
}

bool Kunde::finn_navn(char* temp_navn) {
    if (strcmp(navn, temp_navn)) {
        return true;
    } else {
        return false;
    }
}

void Kunde::add_hurtig(int n){
    char* filnavn = new char [STRLEN];
    
    lagNavn(filnavn, e, dta, n, 7);
    fstream utfil(filnavn, ios::app);
    
    utfil << "\n--------------\n" << navn << "\n" << adresse << " " << gateNr 
            << "\n" << poststed << " " << postKode << "\n";
}
