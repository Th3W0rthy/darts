#ifndef X01_H
#define X01_H

#include "stdbool.h"
#include "../include/lista.h"

void x01_beallitas(int *x01);
void x01_leg_beallitas(int *leg);
void x01_set_beallitas(int *set);
void x01_jatekos_hozzaadas(int x01_pont, int set, int leg);
void x01_jatekos_torlese();
bool x01_szamol_dobas(X01_jatekosok *j, const char *dobas, bool *kilep, bool *sok);
void kiir_kiszallo(const int x01);
void x01_jatek(int x01, int set, int leg);
void x01_felszabadit();
void x01_menu();

#endif