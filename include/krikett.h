#ifndef KRIKETT_H
#define KRIKETT_H

#include "stdbool.h"
#include "../include/lista.h"

void set_beallitas();
void leg_beallitas();
void krikett_jatekos_hozzaadas(int set, int leg);
void krikett_jatekos_torles();
bool krikett_szamol_dobas(Krikett_jatekosok *j, const char *dobas, bool *kilep);
bool ellenoriz_dobasok(Krikett_jatekosok *j, const char *d1, const char *d2, const char *d3, bool *kilep);
void szamol_pont(Krikett_jatekosok *j);
void mentes(Krikett_jatekosok *j);
void krikett_jatek();
void krikett_felszabadit();
void krikett_menu();

#endif