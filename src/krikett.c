#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
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
    char nev[31];
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
    strcpy(uj->dobas_1, "");
    strcpy(uj->dobas_2, "");
    strcpy(uj->dobas_3, "");
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
    uj->nyert_set = 0;
    uj->nyert_leg = 0;
    uj->stat.nyilak_db = 0;
    uj->stat.atlag = 0;
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

bool ellenoriz_dobasok(Krikett_jatekosok *j, const char *d1, const char *d2, const char *d3)
{
    int ment15 = j->db_15;
    int ment16 = j->db_16;
    int ment17 = j->db_17;
    int ment18 = j->db_18;
    int ment19 = j->db_19;
    int ment20 = j->db_20;
    int ment25 = j->db_25;

    bool ok1 = szamol_dobas(j, d1);
    bool ok2 = szamol_dobas(j, d2);
    bool ok3 = szamol_dobas(j, d3);

    if (ok1 && ok2 && ok3)
        return true;

    j->db_15 = ment15;
    j->db_16 = ment16;
    j->db_17 = ment17;
    j->db_18 = ment18;
    j->db_19 = ment19;
    j->db_20 = ment20;
    j->db_25 = ment25;

    return false;
}

bool szamol_dobas(Krikett_jatekosok *j, const char *dobas)
{
    int szorzo = 1;
    int szam;

    if (isalpha(dobas[0]))
    {
        char betu = tolower(dobas[0]);
        if (betu != 'd' && betu != 't') {
            printf("Hibás szorzó!\n");
            return false;
        }
        szorzo = (betu == 'd') ? 2 : (betu == 't') ? 3 : 1;
        szam = atoi(&dobas[1]);
    }
    else
    {
        szam = atoi(dobas);
    }

    switch (szam)
    {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        case 8: break;
        case 9: break;
        case 10: break;
        case 11: break;
        case 12: break;
        case 13: break;
        case 14: break;
        case 15: j->db_15 += szorzo; break;
        case 16: j->db_16 += szorzo; break;
        case 17: j->db_17 += szorzo; break;
        case 18: j->db_18 += szorzo; break;
        case 19: j->db_19 += szorzo; break;
        case 20: j->db_20 += szorzo; break;
        case 25: j->db_25 += szorzo; break;
        default: 
            printf("Hibás bemenet! ");
            return false;
    }
    return true;
}

void szamol_pont(Krikett_jatekosok *j)
{
    int szorzo;
    j->pontok = 0;
    if (j->db_15 > 3) { szorzo = j->db_15 - 3; j->pontok += 15 * szorzo; }
    if (j->db_16 > 3) { szorzo = j->db_16 - 3; j->pontok += 16 * szorzo; }
    if (j->db_17 > 3) { szorzo = j->db_17 - 3; j->pontok += 17 * szorzo; }
    if (j->db_18 > 3) { szorzo = j->db_18 - 3; j->pontok += 18 * szorzo; }
    if (j->db_19 > 3) { szorzo = j->db_19 - 3; j->pontok += 19 * szorzo; }
    if (j->db_20 > 3) { szorzo = j->db_20 - 3; j->pontok += 20 * szorzo; }
    if (j->db_25 > 3) { szorzo = j->db_25 - 3; j->pontok += 25 * szorzo; }
}

void krikett_jatek()
{
    Krikett_jatekosok *mozgo;
    Krikett_jatekosok *mozgo2;
    Krikett_jatekosok *mozgo3;
    Krikett_jatekosok *mozgo4;
    bool nyert = false;
    char dobasok[16]; 
    int korszam = 1;
    char *temp;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    for (mozgo = Kr_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        mozgo->nyert_leg = 0;
        mozgo->nyert_set = 0;
    }

    while (!nyert)
    {
        printf("\n---%d. kör---\n", korszam);
        bool hibatlan = true;
        bool ujrakezd = false;
        for (mozgo = Kr_eleje; mozgo != NULL; mozgo = mozgo->kov)
        {
            mozgo->dobas_1[0] = '\0';
            mozgo->dobas_2[0] = '\0';
            mozgo->dobas_3[0] = '\0';

            printf("\n%s\n15: %d\n16: %d\n17: %d\n18: %d\n19: %d\n20: %d\n25: %d\nPotnok: %d",
            mozgo->nev, mozgo->db_15, mozgo->db_16, mozgo->db_17, mozgo->db_18,
            mozgo->db_19, mozgo->db_20, mozgo->db_25, mozgo->pontok);
            printf("\nNyert leg: %d\nNyert set: %d", mozgo->nyert_leg, mozgo->nyert_set);
            printf("\nDobások: ");
            
            if (fgets(dobasok, sizeof(dobasok), stdin) == NULL)
            {
                printf("Hiba beolvasáskor!\n");
                hibatlan = false;
                break;
            }

            dobasok[strcspn(dobasok, "\n")] = '\0';

            temp = strtok(dobasok, ", ");
            if (temp) {
                while (*temp == ' ') temp++;  
                strcpy(mozgo->dobas_1, temp);
            }

            temp = strtok(NULL, ", ");
            if (temp) {
                while (*temp == ' ') temp++;
                strcpy(mozgo->dobas_2, temp);
            }

            temp = strtok(NULL, ", ");
            if (temp) {
                while (*temp == ' ') temp++;
                strcpy(mozgo->dobas_3, temp);
            }

            if (!ellenoriz_dobasok(mozgo, mozgo->dobas_1, mozgo->dobas_2, mozgo->dobas_3))
            {
                printf("\nHibás dobás! Dobj újra!");
                hibatlan = false;
                break;
            }
                
            szamol_pont(mozgo);

            if (mozgo->db_15 > 2 && mozgo->db_16 > 2 && mozgo->db_17 > 2 && mozgo->db_18 > 2 && 
                mozgo->db_19 > 2 && mozgo->db_20 > 2 && mozgo->db_25 > 2)
            {
                for (mozgo2 = Kr_eleje; mozgo2 != NULL; mozgo2 = mozgo2->kov)
                {
                    if (strcmp(mozgo->nev, mozgo2->nev) != 0)
                    {
                        if (mozgo->pontok >= mozgo2->pontok)
                        {
                            printf("\n%s játékos nyert egy kört!\n", mozgo->nev);
                            mozgo->nyert_leg++;
                            for (mozgo3 = Kr_eleje; mozgo3 != NULL; mozgo3 = mozgo3->kov)
                            {
                                mozgo3->db_15 = 0;
                                mozgo3->db_16 = 0;
                                mozgo3->db_17 = 0;
                                mozgo3->db_18 = 0;
                                mozgo3->db_19 = 0;
                                mozgo3->db_20 = 0;
                                mozgo3->db_25 = 0;
                                mozgo3->pontok = 0;
                            }
                            if (mozgo->nyert_leg == mozgo->leg)
                            {
                                for (mozgo4 = Kr_eleje; mozgo4 != NULL; mozgo4 = mozgo4->kov)
                                {
                                    mozgo4->nyert_leg = 0;
                                }
                                mozgo->nyert_set++;
                            }
                            if (mozgo->nyert_set == mozgo->set)
                            {
                                nyert = true;
                                printf("\n%s játékos győzött!\n", mozgo->nev);
                            }
                            ujrakezd = true;
                            break;
                        } 
                    }
                }
                if (ujrakezd)
                    break;
            }
        }

        if (hibatlan)
        {
            korszam++;
        }
        
        if (ujrakezd)
        {
            korszam = 1;
            continue;
        }
    }
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
        int jatekos_szam = 0;
        int sorszam = 1;
        while (mozgo != NULL)
        {
            printf("%d. %s\n", sorszam, mozgo->nev);
            mozgo = mozgo->kov;
            sorszam++;
            jatekos_szam++;
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
            if (!Kr_eleje)
            {
                printf("\nJátékos nélnül nem lehet játszani!\n");
            }
            else if (jatekos_szam < 2)
            {
                printf("\n2 játékos szükséges a játékhoz!\n");
            }
            else
            {
                printf("\nKezdődjön a játék!\n");
                krikett_jatek();
            }
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