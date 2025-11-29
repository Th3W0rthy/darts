#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "../include/x01.h"
#include "../include/lista.h"

X01_jatekosok *X01_eleje = NULL;

void x01_set_beallitas(int *set)
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

        X01_jatekosok *mozgo = X01_eleje;
        while (mozgo != NULL)
        {
            mozgo->set = *set;
            mozgo = mozgo->kov;
        }
    } while (menupont != 8);
}

void x01_leg_beallitas(int *leg)
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
        X01_jatekosok *mozgo = X01_eleje;
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

        X01_jatekosok *mozgo = X01_eleje;
        while (mozgo != NULL)
        {
            mozgo->x01 = *x01;
            mozgo = mozgo->kov;
        }
    } while (menupont != '7');
}

void x01_jatekos_hozzaadas(int x01, int set, int leg)
{
    char nev[31];
    printf("Játékos neve: ");
    scanf("%30s", nev);

    X01_jatekosok *mozgo = X01_eleje;
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
    strcpy(uj->dobas_1, "");
    strcpy(uj->dobas_2, "");
    strcpy(uj->dobas_3, "");
    uj->x01 = x01;
    uj->set = set;
    uj->leg = leg;
    uj->nyert_set = 0;
    uj->nyert_leg = 0;
    uj->stat.nyilak_db = 0;
    uj->stat.atlag = 0;
    uj->stat.max_dobas_db = 0;
    uj->stat.kiszallo_dobas_db = 0;
    uj->stat.jo_kiszallo = 0;
    uj->stat.max_kiszallo = 0;
    uj->stat.gyozelmek = 0;
    uj->elozo = NULL;
    uj->kov = NULL;

    if (X01_eleje == NULL)
    {
        X01_eleje = uj;
    }
    else
    {
        X01_jatekosok *mozgo = X01_eleje;
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
    if (X01_eleje == NULL)
    {
        printf("Nincs törlendő játékos!\n");
        return;
    }

    int sorszam;
    printf("Törlendő játékos sorszáma: ");
    scanf("%d", &sorszam);

    X01_jatekosok *lemarado = NULL;
    X01_jatekosok *mozgo = X01_eleje;

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
        X01_eleje = mozgo->kov;
        if (X01_eleje)
        {
            X01_eleje->elozo = NULL;
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

bool x01_szamol_dobas(X01_jatekosok *j, const char *dobas, bool *kilep, bool *sok)
{
    int szorzo = 1;
    int szam;
    char betu;
    if (isalpha(dobas[0]))
    {
        betu = tolower(dobas[0]);
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

    if (szam == -1)
    {
        *kilep = true;
    }

    if ((szam >= 0 && szam <= 20) || szam == 25 )
    {
        if (szam == 25 && betu == 't')
        {
            return false;
        }
        
        int temp = j->x01;
        temp -= szorzo * szam;
        if (temp < 0 || temp == 1)
        {
           *sok = true;
           return true;
        }
        j->x01 = temp;
        return true;
    }
    else
    {
        return false;
    }
}

void kiir_kiszallo(const int x01)
{
    FILE *fajl = fopen("data/kiszallok.txt", "r");
    if (!fajl)
    {
        perror("Nem sikerült a fájl megnyitása");
        return;
    }

    int pont;
    char dobasok[20];
    char *temp;

    while (fscanf(fajl, "%9d;%19s", &pont, dobasok) == 2)
    {
        if (x01 == pont)
        {
            printf("\nKiszálló: ");

            temp = strtok(dobasok, ";");
            if (temp)
            {
                while (*temp == ' ') temp++;
                printf("%s ", temp);
            }

            temp = strtok(NULL, ";");
            if (temp)
            {
                while (*temp == ' ') temp++;
                printf("%s ", temp);
            }

            temp = strtok(NULL, ";");
            if (temp)
            {
                while (*temp == ' ') temp++;
                printf("%s ", temp);
            }

            printf("\n");
        }
    }
    
    fclose(fajl);
}

void x01_jatek(int x01, int set, int leg)
{
    X01_jatekosok *mozgo;
    X01_jatekosok *mozgo2;
    X01_jatekosok *mozgo3;
    bool nyert = false;
    bool kilep = false;
    char dobasok[16];
    int korszam = 1;
    char *temp;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    for (mozgo = X01_eleje; mozgo != NULL; mozgo = mozgo->kov)
    {
        mozgo->nyert_leg = 0;
        mozgo->nyert_set = 0;
        mozgo->x01 = x01;
        mozgo->set = set;
        mozgo->leg = leg;
    }

    while (!nyert)
    {
        printf("\n---%d. kör---\n", korszam);
        bool hibatlan = true;
        bool ujrakezd = false;
        bool sok = false;
        for (mozgo = X01_eleje; mozgo != NULL; mozgo = mozgo->kov)
        {
            mozgo->dobas_1[0] = '\0';
            mozgo->dobas_2[0] = '\0';
            mozgo->dobas_3[0] = '\0';
            
            printf("\n%s\nPontszám: %d\nNyert leg: %d\nNyert set: %d\n",
            mozgo->nev, mozgo->x01, mozgo->nyert_leg, mozgo->nyert_set);
            if (mozgo->x01 <= 170)
            {
                kiir_kiszallo(mozgo->x01);
            }
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

            int temp_x01 = mozgo->x01;

            if (!x01_szamol_dobas(mozgo, mozgo->dobas_1, &kilep, &sok) || 
            !x01_szamol_dobas(mozgo, mozgo->dobas_2, & kilep, &sok) || 
            !x01_szamol_dobas(mozgo, mozgo->dobas_3, &kilep, &sok))
            {
                if (kilep)
                {
                    printf("\nKilépés a menübe!\n");
                    nyert = kilep;
                }
                else
                {
                    printf("\nHibás dobás! Dobj újra!");
                    hibatlan = false;
                    break;
                }
            }
            
            if (sok)
            {
                printf("\nBesokalt!\n");
                mozgo->x01 = temp_x01;
                continue;
            }

            if (mozgo->x01 == 0)
            {
                printf("\n%s játékos nyert egy kört!\n", mozgo->nev);
                mozgo->nyert_leg++;
                for (mozgo3 = X01_eleje; mozgo3 != NULL; mozgo3 = mozgo3->kov)
                {
                    mozgo3->x01 = x01;
                }
                if (mozgo->nyert_leg == mozgo->leg)
                {
                    for (mozgo2 = X01_eleje; mozgo2 != NULL; mozgo2 = mozgo2->kov)
                    {
                        mozgo2->nyert_leg = 0;
                    }
                    mozgo->nyert_set++;
                    if (mozgo->nyert_set == mozgo->set)
                    {
                        nyert = true;
                        printf("\n%s játékos győzött!\n", mozgo->nev);
                    }
                }
                ujrakezd = true;
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

void x01_menu()
{
    char menupont;
    int x01 = 501;
    int set = 1;
    int leg = 1;

    do
    {
        printf("\n--X01--\n");
        printf("\nA pontszám: %d\n"
        "Szettek száma: %d\nLegek száma: %d\n",x01, set, leg);

        if (X01_eleje == NULL)
        {
            printf("\nNincs játékos!\n");
        }
        else
        {
            printf("\nJátékosok:\n");
        }
        X01_jatekosok *mozgo = X01_eleje;
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
            x01_set_beallitas(&set);
            break;
        case '3':
            x01_leg_beallitas(&leg);
            break;
        case '4':
            x01_jatekos_hozzaadas(x01, set, leg);
            break;
        case '5':
            x01_jatekos_torlese();
            break;
        case '6':
            if (!X01_eleje)
            {
                printf("\nJátékos nélnül nem lehet játszani!\n");
            }
            else
            {
                x01_jatek(x01, set, leg);
            }
            break;
        case '7':
            printf("\nVisszalépés a játékok menübe!\n");
            return;
            break;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }
    } while (menupont != '7');
}