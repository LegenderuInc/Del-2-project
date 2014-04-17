#pragma once
#include <iostream>
#include <cstring>
#include "listtool2.h"
#include "const.h"
#include <fstream>
#include "listtool2.h"
#include "Enum.h"
#include<stdlib.h>
#include<stdio.h>


using namespace std;


int les_tall(char* text, int min, int max);
int les_tall(ifstream* inn); // returnerer ett heltall
char* les_text(char* text); // returerer text input
char* les_text(ifstream* inn);
void lagNavn(char*t, char* s1, char* s2, int n, const int LEN); // Lager navn i t.
void les_fra_fil();
void skrivMeny();
void skrivMeny_Kunde();
void skrivMeny_Eiendom();
void skrivMeny_Sone();
//void EiendomMeny();
//void SoneMeny();
//void Kundemeny();
void getSisteInfo();
void skrivSiste();
char lesK();

EiendomsType les_eiendomstype();

