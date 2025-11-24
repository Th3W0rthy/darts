#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/x01.h"
#include "../include/lista.h"

X01_jatekosok *eleje = NULL;

void set_beallitas(int *set)
{
    char menupont;
    do
    {
        printf("\nSzettek száma: \n1. 1\n2. 3\n3. 5\n4. 7\n5. 9\n6. 11\n7. 13\n8. Vissza\nMenüpont: ");
        scanf(" %c", &menupont);
        
        switch (menupont)
        {
        case '1': *set = 1; return;
        case '2': *set = 3; return;
        case '3': *set = 5; return;
        case '4': *set = 7; return;
        case '5': *set = 9; return;
        case '6': *set = 11; return;
        case '7': *set = 13; return;
        case '8':
            printf("\nVisszalépés a játékok menübe!\n");
            return;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }

        X01_jatekosok *mozgo = eleje;
        while (mozgo != NULL)
        {
            mozgo->set = *set;
            mozgo = mozgo->kov;
        }
    } while (menupont != 8);
}

void leg_beallitas(int *leg)
{
    char menupont;
do
    {
        printf("\nLegek száma: \n1. 1\n2. 3\n3. 5\n4. Vissza\nMenüpont: ");
        scanf(" %c", &menupont);
        
        switch (menupont)
        {
        case '1': *leg = 1; return;
        case '2': *leg = 3; return;
        case '3': *leg = 5; return;
        case '4':
            printf("\nVisszalépés a játékok menübe!\n");
            return;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }
        X01_jatekosok *mozgo = eleje;
        while (mozgo != NULL)
        {
            mozgo->leg = *leg;
            mozgo = mozgo->kov;
        }
    } while (menupont != 4);
}

void x01_beallitas(int *x01)
{
    char menupont;
    do
    {
        printf("\nPontszámok: \n1. 101\n2. 201\n3. 301\n4. 501\n5. 701\n6. 1001\n7. Vissza\nMenüpont: ");
        scanf(" %c", &menupont);

        switch (menupont)
        {
        case '1': *x01 = 101; return;
        case '2': *x01 = 201; return;
        case '3': *x01 = 301; return;
        case '4': *x01 = 501; return;
        case '5': *x01 = 701; return;
        case '6': *x01 = 1001; return;
        case '7': 
            printf("\nVisszalépés a játékok menübe!\n");
            return;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }

        X01_jatekosok *mozgo = eleje;
        while (mozgo != NULL)
        {
            mozgo->x01 = *x01;
            mozgo = mozgo->kov;
        }
    } while (menupont != '7');
}

void x01_jatekos_hozzaadas(int x01, int set, int leg)
{
    char nev[30];
    printf("Játékos neve: ");
    scanf("%30s", nev);

    X01_jatekosok *mozgo = eleje;
    while (mozgo != NULL)
    {
        if (strcmp(mozgo->nev, nev) == 0)
        {
            printf("Ez a név már szerepel!\n");
            return;
        }
        mozgo = mozgo->kov;
    }

    X01_jatekosok *uj = malloc(sizeof(X01_jatekosok));
    if (uj == NULL)
    {
        printf("Memóriafoglalási hiba!\n");
        return;
    }

    strcpy(uj->nev, nev);
    uj->dobas_1 = 0;
    uj->dobas_2 = 0;
    uj->dobas_3 = 0;
    uj->x01 = x01;
    uj->set_gyoz = 0;
    uj->leg_gyoz = 0;
    uj->set = set;
    uj->leg = leg;
    uj->stat.nyilak_db = 0;
    uj->stat.atlag = 0;
    uj->stat.max_dobas_db = 0;
    uj->stat.kiszallo_dobas_db = 0;
    uj->stat.jo_kiszallo = 0;
    uj->stat.max_kiszallo = 0;
    uj->stat.gyozelmek = 0;
    uj->elozo = NULL;
    uj->kov = NULL;

    if (eleje == NULL)
    {
        eleje = uj;
    }
    else
    {
        X01_jatekosok *mozgo = eleje;
        while (mozgo->kov != NULL)
            {
                mozgo = mozgo->kov;
            }
        mozgo->kov = uj;
        uj->elozo = mozgo;
    }

    printf("Játékos hozzáadva.\n");
}

void x01_jatekos_torlese()
{
    if (!eleje)
    {
        printf("Nincs törlendő játékos!\n");
        return;
    }

    int sorszam;
    printf("Törlendő játékos sorszáma: ");
    scanf("%d", &sorszam);

    X01_jatekosok *lemarado = NULL;
    X01_jatekosok *mozgo = eleje;

    int i = 1;
    while (mozgo != NULL && i < sorszam)
    {
        lemarado = mozgo;
        mozgo = mozgo->kov;
        i++;
    }

    if (mozgo == NULL)
    {
        printf("Nincs törlendő játékos!\n");
        return;
    }

    if (lemarado == NULL)
    {
        eleje = mozgo->kov;
        if (eleje)
        {
            eleje->elozo = NULL;
        }
    } 
    else
    { 
        lemarado->kov = mozgo->kov;
        if (mozgo->kov)
        {
            mozgo->kov->elozo = lemarado;
        }
    }

    free(mozgo);
    printf("Játékos törölve.\n");
}

void x01_jatek()
{
    
}

void x01_menu()
{
    char menupont;
    int x01 = 501;
    int set = 1;
    int leg = 1;

    do
    {
        printf("\nA pontszám: %d\n", x01);
        printf("\nSzettek száma: %d\n", set);
        printf("\nLegek száma: %d\n", leg);

        if (eleje == NULL)
        {
            printf("\nNincs játékos!\n");
        }
        else
        {
            printf("\nJátékosok:\n");
        }
        X01_jatekosok *mozgo = eleje;
        int sorszam = 1;
        while (mozgo != NULL)
        {
            printf("%d. %s\n", sorszam, mozgo->nev);
            mozgo = mozgo->kov;
            sorszam++;
        }

        printf("\n1. X01 pontszám módosítása\n2. Szet szám módosítás\n"
        "3. Leg szám módosítás\n4. Játékos hozzáadása\n5. Játékos törlése\n6. Játék kezdése\n7. Vissza\n\nMenüpont: ");
        scanf(" %c", &menupont);
        switch (menupont)
        {
        case '1':
            x01_beallitas(&x01);
            break;
        case '2':
            set_beallitas(&set);
            break;
        case '3':
            leg_beallitas(&leg);
            break;
        case '4':
            x01_jatekos_hozzaadas(x01, set, leg);
            break;
        case '5':
            x01_jatekos_torlese();
            break;
        case '6':

            break;
        case '7':
            printf("\nVisszalépés a játékok menübe!\n");
            return;
            break;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }
    } while (menupont != '5');
}