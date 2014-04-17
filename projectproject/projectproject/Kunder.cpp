#include "Kunder.h"
#include "Bokst.h"

using namespace std;

Kunder::Kunder() {
    char* temp_filnavn;
	int uselessJunk;
    kundelist = new List(Sorted);

	 ifstream sistefil("SISTE.DTA");

	 sistefil >> uselessJunk >> forsteK >> sistI;
	 
    for (int i = forsteK; i <= sistI; i++) {
        temp_filnavn = new char[50];
        lagNavn(temp_filnavn, "K", ".DTA", i, 7);

		ifstream* innfil = new ifstream(temp_filnavn);

        if (innfil) {
            Kunde * temp;
            temp = new Kunde(innfil, i);
            kundelist->add(temp);
        } else {
            cout << "\nDance";
        }
    }
}

Kunder::~Kunder(){

}

void Kunder::ny_kunde(){
	Kunde * temp;
	temp = new Kunde(++sistI);
	//Sammenlign funksjon kalles her.
	kundelist->add(temp);
}

void Kunder::skrivUkentlig(){
    Kunde * temp;
    for(int i = 1; i <= sistI; i++){
        temp = (Kunde*) kundelist->remove_no(i);        
        temp->sjekk_interesser();
        kundelist->add(temp);
    }
}


void Kunder::skriv_til_fil() {
    int listLen = 0;
	Kunde* temp; 
	
	ofstream utfil("SISTE.DTA", ios::app);

	utfil	<< forsteK << '\n' 
			<< sistI << '\n';

	if (!(kundelist->is_empty())){
		listLen = kundelist->no_of_elements();
		for(int i = 1; i <= listLen; i++){
			temp = (Kunde*) kundelist->remove_no(i);
			temp->skriv_til_fil();
			kundelist->add(temp);
		}
	}else {
		cout << "\nSer ut til at denne listen er tom :(";
	}

}

List* Kunder::return_list(){
    return kundelist;
}

void Kunder::display(){
    Kunde* temp_kunde;
    int valg1, temp_nr;
    char* temp_navn,
    
    valg = les_tall("\nVil du s�ke p� Navn = 0, eller Kundenummer = 1: ", 0, 1);
    
    if(valg1 = 0){
        temp_navn = les_text("\nHvilket navn �nsker du � s�ke etter?: ");
        for(int i = 1; i <= kundelist->no_of_elements(); i++){
            temp_kunde = (Kunde*) kundelist->remove_no(i);
            if(temp_kunde->finn_navn(temp_navn)){
                cout << "\n Kunde funnet, displayer...\n";
                temp_kunde->display();
            }
            kundelist->add(temp_kunde);
            delete temp_kunde;
        }
    }else{
        temp_nr = les_tall("\nHvilket kundenummer �nsker de � lete etter?: ", MIN_KUNDE, MAX_KUNDE);
        if(kundelist->in_list(temp_nr)){
            cout << "\nKunde Funnet displayer";
            temp_kunde = (Kunde*) kundelist->remove(temp_nr);
            temp_kunde->display();
            kundelist->add(temp_kunde);
            delete temp_kunde;
        }else{
            cout << "\nFant ingen kunder med det kunde nummeret, retunerer tilbake til menyen...";
        }
    }
}

void Kunder::slettKunde(){ // Ikkeferdig, hoilder p� � fikse siste.dta sjekk.
    Kunde* temp_kunde;
    int temp_nr;
    char valg;
	char* temp_inf = new char[STRLEN];
	char* temp_dta = new char[STRLEN];
    
    cout << "\nStarter fase 1 av sletting......";
    
    temp_nr = les_tall("\nHvilket kunde �nsker de � slette? Kunde nummer: ", MIN_KUNDE, MAX_KUNDE);
    if(kundelist->in_list(temp_nr)){
        temp_kunde = (Kunde*) kundelist->remove(temp_nr);
        cout << "Kunde funnet, displayer kundeinfo...\n";
        temp_kunde->display();
        cout << "\n****** �NSKER DU � SLETTE DENNE KUNDEN (Y/N) ? *******";
        valg = lesK();
        if(valg == 'Y' || valg == 'y'){
            lagNavn(temp_inf, k, inf, temp_nr, 7);
            ifstream infFil(temp_inf);
            if(infFil){
                cout << "\nRemoving " << temp_inf << " ....";
                remove(temp_inf);
            }
            lagNavn(temp_dta, k, dta, temp_nr, 7); // var 9
            ifstream dtaFil(temp_dta);
            if(dtaFil){
                cout << "\nRemoving " << temp_dta << " .....";
                remove(temp_dta);
            }
            if(temp_nr == forsteK){
                    finn_ny_første();
            }
            delete temp_kunde;
        }else{
            cout << "\n***Kunde med oppdrags nr " << temp_nr << " blir ikke slettet***";
            kundelist->add(temp_kunde);
        } 
               
        
    }
}

void Kunder::endreKunde(){
    Kunde* temp_kunde = NULL;
    int temp_kundenr;
    char valg;
    
    temp_kundenr = les_tall("\n Kundenummer: ", forsteK, sistI);
    
    if(!kundelist->is.empty()){
        temp_kunde = (Kunde*) kundelist->remove(temp_kundenr);
        if(temp_kunde){
            cout << "\nHva ønsker du å endre på? (K)unden eller (I)nteresseeoner?";
            valg = lesK();
            
            switch(valg){
                case 'K': 
                    delete temp_kunde;
                    kundelist->add(new Kunde(temp_kundenr));
                    break;
                case 'I':
                    temp_kunde->endre_interesse();
                    kundelist->add(temp_kunde);
                    break;
                default: cout << "\nDu har tastet in ugyldig kommando";
            }
        }else{
            cout << "\nFant ingen kunder med kundenummeret du tastet inn.";
        }
    }else{
        cout << "\nDenne listen er jo tom, kanskje du skal heller legge til noen nye?";
    }
}