#pragma once
void affichageDuMenuAccueil();
int lancementDePartie();
void initierTableauDeDungeon();
void mouvementDeCase(int tableauPositionX, int tableauPositionY, struct PositionCase tableauDeDungeon[5][7]);
void caseDePotion(int tableauPositionX, int tableauPositionY, PositionCase tableauDeDungeon[5][7]);
void caseDeMonstre(int tableauPositionX, int tableauPositionY, PositionCase tableauDeDungeon[5][7]);
void caseDeBoss(int tableauPositionX, int tableauPositionY, PositionCase tableauDeDungeon[5][7]);