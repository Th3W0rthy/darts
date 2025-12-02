#ifndef KRIKETT_H
#define KRIKETT_H

#include "stdbool.h"
#include "../include/lista.h"

void krikett_set_beallitas(Krikett_jatekosok *eleje, int *set);
void krikett_leg_beallitas(Krikett_jatekosok *eleje, int *leg);
void krikett_jatekos_hozzaadas(Krikett_jatekosok **eleje, int set, int leg);
void krikett_jatekos_torles(Krikett_jatekosok **eleje);
bool krikett_szamol_dobas(Krikett_jatekosok *j, const char *dobas, bool *kilep);
bool ellenoriz_dobasok(Krikett_jatekosok *j, const char *d1, const char *d2, const char *d3, bool *kilep);
void szamol_pont(Krikett_jatekosok *j);
void krikett_mentes(Krikett_jatekosok *eleje);
void krikett_jatek(Krikett_jatekosok *eleje);
void krikett_felszabadit(Krikett_jatekosok **eleje);
void krikett_menu();

#endif