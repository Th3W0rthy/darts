#ifndef LISTA_H
#define LISTA_H

typedef struct X01_stats
{
    int nyilak_db;
    double atlag;
    int max_dobas_db;
    int kiszallo_dobas_db;
    int jo_kiszallo;
    int max_kiszallo;
    int gyozelmek;
} X01_stats;

typedef struct Krikett_stats
{
    int nyilak_db;
    double atlag;
    int max_dobas_db;
    int max_kiszallo;
} Krikett_stats;

typedef struct X01_jatekosok
{
    char nev[31];
    int dobas_1;
    int dobas_2;
    int dobas_3;

    int x01;
    int set;
    int leg;
    int set_gyoz;
    int leg_gyoz;
    X01_stats stat;

    struct X01_jatekosok *elozo, *kov;
} X01_jatekosok;

typedef struct Krikett_jatekosok
{
    char nev[31];
    int dobas_1;
    int dobas_2;
    int dobas_3;

    int db_15;
    int db_16;
    int db_17;
    int db_18;
    int db_19;
    int db_20;
    int db_25;

    int pontok;
    Krikett_stats stat;

    struct Krikett_jatekosok *elozo, *kov;
} Krikett_jatekosok;

#endif