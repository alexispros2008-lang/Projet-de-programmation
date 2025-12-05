/*====================================
AUTEUR : Alexis Provencher
PROJET : Laboratoire 6.2
NOM DU FICHIER : main.cpp
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

struct PositionCase
{
	bool existenceDeLaCase,
		presencePotion,
		presenceMonstreBasique,
		presenceBoss;
};

void affichageDuMenuAccueil() {
	locale::global(locale{ "" });
	cout << "Dans les cavernes, le Dungeon de la légende" << endl;
	cout << "se trouve dans les parties les plus profondes." << endl;
	cout << "Il est dit qu’un jour, un aventurier légendaire va vaincre le monstre" << endl;
	cout << "de la légende et obtenir un trésor sans limite." << endl;
	system("pause");
	system("cls");
	cout << "------------------------------------------------------------------------" << endl;
	cout << "-                                                                      -" << endl;
	cout << "-                         Le dungeon légendaire                        -" << endl;
	cout << "-                                                                      -" << endl;
	cout << "------------------------------------------------------------------------" << endl;
	system("pause");
	system("cls");
	cout << "Choisissez une option." << endl << endl;
	cout << "------------------------------------------------------------------------" << endl;
	cout << "- 1) Nouvelle partie                                                   -" << endl;
	cout << "- 2) Quitter le jeu                                                    -" << endl;
	cout << "------------------------------------------------------------------------" << endl;
}

int lancementDePartie() {
	int choixCommencementDePartie;
	cin >> choixCommencementDePartie;
	switch (choixCommencementDePartie){
		case '1':
			system("cls");
			break;
		case '2':
			exit(1);
	}
}

void initierTableauDeDungeon() {
	struct PositionCase tableauDeDungeon[5][7];
	int tableauPositionX = 3,
		tableauPositionY = 6;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
			tableauDeDungeon[i][j] = { 0,0,0,0 };

	ifstream fichier("tableauDungeonLevel1.txt");

	if (!fichier) {
		cerr << "Erreur : impossible d'ouvrir tableauDungeonLevel1.txt" << endl;
	}

	int x,
		y;
	int existence, boss, monstre, potion;

	while (fichier >> x >> y >> existence >> boss >> monstre >> potion) {
		tableauDeDungeon[x][y].existenceDeLaCase = existence;
		tableauDeDungeon[x][y].presenceBoss = boss;
		tableauDeDungeon[x][y].presenceMonstreBasique = monstre;
		tableauDeDungeon[x][y].presencePotion = potion;
	}

	fichier.close();
	mouvementDeCase(tableauPositionX, tableauPositionY, tableauDeDungeon);
}

void mouvementDeCase(int tableauPositionX, int tableauPositionY, struct PositionCase tableauDeDungeon[5][7]){
	while (true) {
		bool possibleBas = false,
			possibleGauche = false,
			possibleDroite = false,
			possibleHaut = false,
			pouvoirContinuer = false;
		if (tableauDeDungeon[tableauPositionX][tableauPositionY + 1].existenceDeLaCase == true) {
			possibleBas = true;
			cout << "1 - Vous pouvez essayer d'aller vers le sud." << endl;
		}
		if (tableauDeDungeon[tableauPositionX][tableauPositionY - 1].existenceDeLaCase == true) {
			possibleHaut = true;
			cout << "2 - Vous pouvez essayer d'aller vers le nord." << endl;
		}
		if (tableauDeDungeon[tableauPositionX + 1][tableauPositionY].existenceDeLaCase == true) {
			possibleDroite = true;
			cout << "3 - Vous pouvez essayer aller vers l'est." << endl;
		}
		if (tableauDeDungeon[tableauPositionX - 1][tableauPositionY].existenceDeLaCase == true) {
			possibleGauche = true;
			cout << "4 - Vous pouvez essayer aller vers l'ouest." << endl;
		}
		else {

		}
		int choixDeMouvement;
		do {
			cout << endl << "Qu'est ce que vous voulez faire : " << endl;
			cin >> choixDeMouvement;
			switch (choixDeMouvement) {
			case 1:
				if (possibleBas == false) {
					cout << "Vous ne pouvez pas aller vers le sud.";
				}
				else {
					tableauPositionY = tableauPositionY + 1;
					pouvoirContinuer = true;
					cout << "Vous vous êtes déplacé dans une salle vers le sud.";
				}
				break;
			case 2:
				if (possibleHaut == false) {
					cout << "Vous ne pouvez pas aller vers le nord.";
				}
				else {
					tableauPositionY = tableauPositionY - 1;
					pouvoirContinuer = true;
					cout << "Vous vous êtes déplacé dans une salle vers le nord.";
				}
				break;
			case 3:
				if (possibleDroite == false) {
					cout << "Vous ne pouvez pas aller vers l'est.";
				}
				else if (possibleDroite == true) {
					tableauPositionX = tableauPositionX + 1;
					pouvoirContinuer = true;
					cout << "Vous vous êtes déplacé dans une salle vers l'est.";
				}
				else {

				}
				break;
			case 4:
				if (possibleGauche == false) {
					cout << "Vous ne pouvez pas aller vers l'ouest.";
				}
				else {
					tableauPositionX = tableauPositionX - 1;
					pouvoirContinuer = true;
					cout << "Vous vous êtes déplacé dans une salle vers l'ouest.";
				}
				break;
			default:
				cout << "Vous ne pouvez pas utiliser une valeur qui n'est pas dans celle indiquée.";
				pouvoirContinuer = false;
				break;
			}
		} while (pouvoirContinuer == false);
		system("cls");
		caseDePotion(tableauPositionX, tableauPositionY, tableauDeDungeon);
		caseDeMonstre(tableauPositionX, tableauPositionY, tableauDeDungeon);
		caseDeBoss(tableauPositionX, tableauPositionY, tableauDeDungeon);
		cout << endl;
		system("pause");
		system("cls");
	}
}

void caseDePotion(int tableauPositionX, int tableauPositionY, struct PositionCase tableauDeDungeon[5][7]) {
	if (tableauDeDungeon[tableauPositionX][tableauPositionY].presencePotion == false) {
		cout << endl << "Il n'y a pas de potion dans la salle actuelle." << endl;
	}
	else if (tableauDeDungeon[tableauPositionX][tableauPositionY].presencePotion == true) {
		cout << endl << "Vous avez trouvé une potion dans la salle." << endl;
	}
	else {

	}
}

void caseDeMonstre(int tableauPositionX, int tableauPositionY, struct PositionCase tableauDeDungeon[5][7]) {
	if (tableauDeDungeon[tableauPositionX][tableauPositionY].presenceMonstreBasique == false) {
		cout << endl << "Il n'y a pas de monstre basique dans la salle actuelle." << endl;
	}
	else if (tableauDeDungeon[tableauPositionX][tableauPositionY].presenceMonstreBasique == true) {
		cout << endl << "Il y a un monstre dans cette salle!" << endl;
		system("pause");
		enleverContenuDeConsole();
		monstreGeneral();
	}
}

void caseDeBoss(int tableauPositionX, int tableauPositionY, struct PositionCase tableauDeDungeon[5][7]) {
	if (tableauDeDungeon[tableauPositionX][tableauPositionY].presenceMonstreBasique == false) {
		cout << endl << "Il n'y a pas de boss dans la salle actuelle." << endl;
	}
	else if (tableauDeDungeon[tableauPositionX][tableauPositionY].presenceMonstreBasique == true) {
		cout << endl << "Il y a un boss dans cette salle!" << endl;
	}
	else {

	}
}