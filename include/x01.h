#ifndef X01_H
#define X01_H

#include "stdbool.h"
#include "../include/lista.h"

void x01_set_beallitas(X01_jatekosok *X01_eleje, int *set);
void x01_leg_beallitas(X01_jatekosok *X01_eleje, int *leg);
void x01_beallitas(X01_jatekosok *X01_eleje, int *x01);
void x01_jatekos_hozzaadas(X01_jatekosok **X01_eleje, int x01, int set, int leg);
void x01_jatekos_torlese(X01_jatekosok **X01_eleje);
bool x01_szamol_dobas(X01_jatekosok *j, const char *dobas, bool *kilep, bool *sok);
void kiir_kiszallo(const int x01);
void x01_mentes(X01_jatekosok *X01_eleje);
void x01_jatek(X01_jatekosok *X01_eleje, int x01, int set, int leg);
void x01_felszabadit(X01_jatekosok **X01_eleje);
void x01_menu();

#endif