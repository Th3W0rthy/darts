#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/krikett.h"
#include "../include/lista.h"


Krikett_jatekosok *Kr_eleje = NULL;

void krikett_set_beallitas(int *set)
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

        Krikett_jatekosok *mozgo = Kr_eleje;
        while (mozgo != NULL)
        {
            mozgo->set = *set;
            mozgo = mozgo->kov;
        }
    } while (menupont != 8);
}

void krikett_leg_beallitas(int *leg)
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
        Krikett_jatekosok *mozgo = Kr_eleje;
        while (mozgo != NULL)
        {
            mozgo->leg = *leg;
            mozgo = mozgo->kov;
        }
    } while (menupont != 4);
}

void krikett_jatekos_hozzaadas(int set, int leg)
{
    char nev[30];
    printf("Játékos neve: ");
    scanf("%30s", nev);

    Krikett_jatekosok *mozgo = Kr_eleje;
    while (mozgo != NULL)
    {
        if (strcmp(mozgo->nev, nev) == 0)
        {
            printf("Ez a név már szerepel!\n");
            return;
        }
        mozgo = mozgo->kov;
    }

    Krikett_jatekosok *uj = malloc(sizeof(Krikett_jatekosok));
    if (uj == NULL)
    {
        printf("Memóriafoglalási hiba!\n");
        return;
    }

    strcpy(uj->nev, nev);
    uj->dobas_1 = 0;
    uj->dobas_2 = 0;
    uj->dobas_3 = 0;
    uj->db_15 = 0;
    uj->db_16 = 0;
    uj->db_17 = 0;
    uj->db_18 = 0;
    uj->db_19 = 0;
    uj->db_20 = 0;
    uj->db_25 = 0;
    uj->pontok = 0;
    uj->set = set;
    uj->leg = leg;
    uj->stat.nyilak_db = 0;
    uj->stat.atlag = 0;
    uj->stat.gyozelmek = 0;
    uj->elozo = NULL;
    uj->kov = NULL;

    if (Kr_eleje == NULL)
    {
        Kr_eleje = uj;
    }
    else
    {
        Krikett_jatekosok *mozgo = Kr_eleje;
        while (mozgo->kov != NULL)
            {
                mozgo = mozgo->kov;
            }
        mozgo->kov = uj;
        uj->elozo = mozgo;
    }

    printf("Játékos hozzáadva.\n");
}

void krikett_jatekos_torles()
{
    if (Kr_eleje == NULL)
    {
        printf("Nincs törlendő játékos!\n");
        return;
    }

    int sorszam;
    printf("Törlendő játékos sorszáma: ");
    scanf("%d", &sorszam);

    Krikett_jatekosok *lemarado = NULL;
    Krikett_jatekosok *mozgo = Kr_eleje;

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
        Kr_eleje = mozgo->kov;
        if (Kr_eleje)
        {
            Kr_eleje->elozo = NULL;
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

void krikett_menu()
{
    char menupont;
    int set = 1;
    int leg = 1;

    do
    {
        printf("\n--Krikett--\n");
        printf("\nSzettek száma: %d\nLegek száma: %d\n",set, leg);

        if (Kr_eleje == NULL)
        {
            printf("\nNincs játékos!\n");
        }
        else
        {
            printf("\nJátékosok:\n");
        }
        Krikett_jatekosok *mozgo = Kr_eleje;
        int sorszam = 1;
        while (mozgo != NULL)
        {
            printf("%d. %s\n", sorszam, mozgo->nev);
            mozgo = mozgo->kov;
            sorszam++;
        }

        printf("\n1. Szet szám módosítása\n2. Leg szám módosítása\n3. Játékos hozzáadása\n4. Játékos törlése"
        "\n5. Játék kezdése\n6. Vissza\nMenüpont: ");
        scanf(" %c", &menupont);

        switch (menupont)
        {
        case '1':
            krikett_set_beallitas(&set);
            break;
        case '2':
            krikett_leg_beallitas(&leg);
            break;
        case '3':
            krikett_jatekos_hozzaadas(set, leg);
            break;
        case '4':
            krikett_jatekos_torles();
            break;
        case '5':
            
            break;
        case '6':
            printf("\nVisszalépés a játékok menübe!\n");
            return;
            break;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }
    } while (menupont != '6');
    
}