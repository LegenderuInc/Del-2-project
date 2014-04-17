#include "Globalevariabler.h"
#include "Soner.h"
#include "Kunder.h"

Soner* mSoner;



//int main() {
//	mSoner = new Soner();
//	mSoner->add_sone();
//	mSoner->nytt_oppdrag();
//	/*mSoner->add_sone();*/
//
//
//
//	//mSoner->get_sone(1)->add_oppdrag();
//
//	
//	
//	/*Eiendom mEiendom(35672);
//	mEiendom.skriv_til_fil();*/
//
//	//ifstream ifil("E00035672.DTA");
//
//	//Eiendom mEiendom2(&ifil,23);
//
//	//mEiendom2.skriv_til_fil();
//
//
//
//	////mEiendom2.skirv_til_fil(fil);23
//
//
//
//	system("pause");
//}


void eiendomMeny();
void soneMeny();
void kundeMeny();
Sone* mSone;

int main() {
	mSoner = new Soner();
	/*mSoner->nytt_oppdrag();
	mSoner->nytt_oppdrag();
	
	mSoner->display_soneoppdrag(1);*/

    char kommando;
    skrivMeny();
    kommando = lesK();

    while (kommando != 'Q') {
        switch (kommando) {
            case 'E': eiendomMeny();
                break;
			case 'S': soneMeny();
                break;
			case 'K': kundeMeny();
                break;
            case 'U':
                break;
            default: skrivMeny();
                break;
        }
        kommando = lesK();
    }
    return 0;
}










void eiendomMeny() {

	skrivMeny_Eiendom();

    char kommando;
    
    kommando = lesK();
    
    while (kommando != 'Q') {
        switch (kommando) {
		case 'D': mSoner->display_oppdrag(23000);  // les tall i parameter
            break;
		case 'N': mSoner->nytt_oppdrag(); 
            break;
        case 'S':
            break;
        case 'E':
            break;
        default: skrivMeny_Eiendom();
            break;
        }
		skrivMeny_Eiendom();
		kommando = lesK();
	}	
}


void kundeMeny() {

	skrivMeny_Kunde();

    char kommando;
    
    kommando = lesK();
    
    while (kommando != 'Q') {
        switch (kommando) {
            case 'D': 
                break;
			case 'N': 
                break;
            case 'S':
                break;
            case 'E':
                break;
            default:
                break;
        }
    }
}

void soneMeny() {

	skrivMeny_Sone();

    char kommando;
    
    kommando = lesK();
    
    while (kommando != 'Q') {
        switch (kommando) {
		case 'D': mSoner->display_soneoppdrag(les_tall("\nAngi sonenummer: ", 1, 100)); 
            break;
		case 'N': 
            break;
        case 'S':
            break;
        case 'E':
            break;
		case 'Q': break;
		default: skrivMeny_Sone();
            break;

        }
		skrivMeny_Sone();
		kommando = lesK();
    }
}
