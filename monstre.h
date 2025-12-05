#pragma once
void afficherMenu(int nbDeVieHero, int nbDeVieMonstre, int nbPotions);
void enleverContenuDeConsole();
void tourDuHero();
int choix(int lettre);
int prendrePotion(int nbDeVieHero, int NbPotions);
int fuite();
int attaqueDuHero(int& durabiliterHache, int& durabiliterMarteau, int& durabiliterArc, int& durabiliterFeux, int& durabiliterGlace);
int attaqueDuMonstre(int dommagesuplementaire, int nbDeVieMonstre, int nbDeVieHero);
void monstreGeneral();
