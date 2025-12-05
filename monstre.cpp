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
#include "monstre.h"

using namespace std;

void afficherMenu(int nbDeVieHero, int nbDeVieMonstre, int nbPotions)
{
	cout << "Vos points de vie : " << nbDeVieHero << endl;
	cout << "Vos potions : " << nbPotions << endl;
	cout << endl << "Points de vie du monstre : " << nbDeVieMonstre;
	cout << endl << endl;
	cout << "=======================================";
	cout << endl;
	cout << "1) Attaquer le monstre" << endl;
	cout << "2) Boire une potion (+50HP)" << endl;
	cout << "3) S'enfuir de la bataille" << endl;
	cout << "4) Quitter le jeu" << endl;
	cout << endl;
	cout << "Choissisez une option : ";
}

int choix(int choixDeCombat) {
	cin >> choixDeCombat;
	return choixDeCombat;
}

void enleverContenuDeConsole() {
	system("cls");
}

void tourDuHero() {
	cout << "***************************************";
	cout << endl;
	cout << "**          C'est votre tour         **";
	cout << endl;
	cout << "***************************************";
	cout << endl;
}

int attaqueDuHero(int& durabiliterHache, int& durabiliterMarteau, int& durabiliterArc, int& durabiliterFeux, int& durabiliterGlace) {
	int dommageInfligerAuMonstre = 0;

	fstream monflux;
	string ligne;
	monflux.open("attaques.txt", ios::in);

	if (!monflux) {
		cout << "Le fichier n'est pas ouvert! Erreur!";
		system("pause>0");
		exit(1);
	}
	else {
		while (getline(monflux, ligne)) {
			cout << ligne << endl;
		}
		monflux.close();
	}
	std::cout << endl << "Quelle arme voulez-vous utiliser ?" << endl;

	int choixArmes;
	cin >> choixArmes;
	switch (choixArmes) {
	case 1:
		dommageInfligerAuMonstre = rand() % (25 + 1 - 15) + 15;
		break;
	case 2:
		if (durabiliterHache > 0) {
			dommageInfligerAuMonstre = rand() % (40 + 1 - 30) + 30;
			durabiliterHache--;
		}
		else {
			cout << "Votre Hache est brisé, veuillez prendre une autre arme." << endl;
		}
		break;
	case 3:
		if (durabiliterMarteau > 0) {
			dommageInfligerAuMonstre = rand() % (45 + 1 - 40) + 40;
			durabiliterMarteau--;
		}
		else {
			cout << "Votre marteau est brisé, veuillez prendre une autre arme." << endl;
		}
		break;
	case 4:
		if (durabiliterArc > 0) {
			dommageInfligerAuMonstre = rand() % (10 + 1 - 30) + 30;
			durabiliterArc--;
		}
		else {
			cout << "Votre Arc est brisé, veuillez prendre une autre arme." << endl;
		}
		break;
	case 5:
		if (durabiliterFeux > 0) {
			dommageInfligerAuMonstre = rand() % (60 + 1 - 50) + 50;
			durabiliterFeux--;
		}
		else {
			cout << "Votre Feu est brisé, veuillez prendre une autre arme." << endl;
		}
		break;
	case 6:
		if (durabiliterGlace > 0) {
			dommageInfligerAuMonstre = rand() % (60 + 1 - 50) + 50;
			durabiliterGlace--;
		}
		else {
			cout << "Votre Glace est brisé, veuillez prendre une autre arme." << endl;
		}
		break;
	default:
		cout << "Option non disponible.";
	}
	return dommageInfligerAuMonstre;
}

int prendrePotion(int nbDeVieHero, int nbPotions) {
	if (nbPotions > 0) {
		nbDeVieHero = nbDeVieHero + 100;
		nbPotions = nbPotions - 1;
		cout << "Le hero a utiliser une potion. " << endl;
	}
	else {
		cout << "Tu n'a pas d'autres potions." << endl;
		cout << "Le hero n'a utiliser pas de potion. " << endl;
	}
	cout << "L'hero a " << nbDeVieHero << " de point de vie." << endl;
	cout << "Il te reste " << nbPotions << " potions." << endl;

	return nbPotions;
}

int fuite() {
	int chanceDeFuite = rand() % (20 + 1 - 1) + 1;
	if (chanceDeFuite <= 12) {
		int dommagesuplementaire = 5;
		cout << "Vous avez echouer a vous enfuir." << endl << "Le monstre va vous faire +15 de dommage supplementaire prochain tour.";
		return dommagesuplementaire;
	}
	else {
		cout << "Vous vous êtes enfuit." << endl;
		cout << "0 exp et 0 gold" << endl;
		exit(0);
	}
}

int attaqueDuMonstre(int dommagesuplementaire, int nbDeVieMonstre, int nbDeVieHero) {
	int dommageChance = rand() % (20 + 15 - 15) + 15;
	nbDeVieHero = nbDeVieHero - dommageChance;
	nbDeVieHero = nbDeVieHero - dommagesuplementaire;
	return nbDeVieHero;
}

void monstreGeneral(){
	int nbPotions;
	nbPotions = rand() % (5 + 1 - 1) + 1;
	int nbDeVieMonstre = 125, nbDeVieHero = 95, durabiliterHache = 6, durabiliterMarteau = 3, durabiliterArc = 12, durabiliterFeux = 1, durabiliterGlace = 1, dommageInfligerMonstre = 0, dommagesuplementaire = 0, choixDeCombat;
	do {
		afficherMenu(nbDeVieHero, nbDeVieMonstre, nbPotions);
		cin >> choixDeCombat;
		enleverContenuDeConsole();


		switch (choixDeCombat) {
		case 1:
			tourDuHero();
			dommageInfligerMonstre = attaqueDuHero(durabiliterHache, durabiliterMarteau, durabiliterArc, durabiliterFeux, durabiliterGlace);
			nbDeVieMonstre = nbDeVieMonstre - dommageInfligerMonstre;
			break;
		case 2:
			nbPotions = prendrePotion(nbDeVieHero, nbPotions);
			break;
		case 3:
			dommagesuplementaire = fuite();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "Vous avez rentrer aucune des options disponibles.";
			break;
		}

		system("pause");
		enleverContenuDeConsole();
		nbDeVieHero = attaqueDuMonstre(dommagesuplementaire, nbDeVieMonstre, nbDeVieHero);

	} while (nbDeVieHero > 0 && nbDeVieMonstre > 0);

	if (nbDeVieHero < 0) {
		cout << "Le monstre vous a battu !" << endl << endl;
		exit(0);
	}
	if (nbDeVieMonstre < 0) {
		cout << "Vous avez battu le monstre !" << endl << endl;
	}
	else {

	}
}