#ifndef LISTA_H
#define LISTA_H

typedef struct X01_stats
{
    double nyilak_db;
    double atlag;
    double ossz_dobas;
    int max_dobas_db;
    int kiszallo_dobas_db;
    int jo_kiszallo;
    int max_kiszallo;
    int nyert_set;
    int nyert_leg;
} X01_stats;

typedef struct Krikett_stats
{
    double nyilak_db;
    double atlag;
    double ossz_dobas;
    int nyert_set;
    int nyert_leg;
} Krikett_stats;

typedef struct X01_jatekosok
{
    char nev[31];
    char dobas_1[4];
    char dobas_2[4];
    char dobas_3[4];

    int x01;
    int set;
    int leg;
    int nyert_set;
    int nyert_leg;
    X01_stats stat;

    struct X01_jatekosok *elozo, *kov;
} X01_jatekosok;

typedef struct Krikett_jatekosok
{
    char nev[31];
    char dobas_1[6];
    char dobas_2[6];
    char dobas_3[6];

    int set;
    int leg;
    int nyert_set;
    int nyert_leg;

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