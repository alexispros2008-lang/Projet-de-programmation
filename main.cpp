/*====================================
AUTEUR : Alexis Provencher
PROJET : Laboratoire 6.2
NOM DU FICHIER : mesFonctions.cpp
DATE : 11/5/2025
BUT : Les critères demandés par le laboratoire 5.
====================================*/
#include "dungeon.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstdlib>

using namespace std;

int main() {	
	affichageDuMenuAccueil();
	lancementDePartie();
	initierTableauDeDungeon();
}
	