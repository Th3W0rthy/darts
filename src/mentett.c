#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <debugmalloc.h>

void krikett_beolvasas()
{
    char fajlnev[] = "data/krikett_";
    char datum[50];
    char teljes_ut[100];
    FILE *fajl;

    printf("Add meg a dátumot és időt a fájl nevében (pl.: 2025_11_09_11_09.txt): ");
    if (fgets(datum, sizeof(datum), stdin) == NULL) {
        printf("Hiba a beolvasásnál!\n");
        return;
    }

    datum[strcspn(datum, "\n")] = '\0';
    snprintf(teljes_ut, sizeof(teljes_ut), "%s%s", fajlnev, datum);

    fajl = fopen(teljes_ut, "r");
    if (!fajl) {
        perror("Nem sikerült a fájl megnyitása");
        return;
    }

    char sor[256];
    while (fgets(sor, sizeof(sor), fajl)) {
        printf("%s", sor);
    }

    fclose(fajl);
}

void x01_beolvasas()
{
    char fajlnev[] = "data/x01_";
    char datum[50];
    char teljes_ut[100];
    FILE *fajl;

    printf("Add meg a dátumot és időt a fájl nevében (pl.: 2025_11_09_11_09.txt): ");
    if (fgets(datum, sizeof(datum), stdin) == NULL) {
        printf("Hiba a beolvasásnál!\n");
        return;
    }

    datum[strcspn(datum, "\n")] = '\0';
    snprintf(teljes_ut, sizeof(teljes_ut), "%s%s", fajlnev, datum);

    fajl = fopen(teljes_ut, "r");
    if (!fajl) {
        perror("Nem sikerült a fájl megnyitása");
        return;
    }

    char sor[256];
    while (fgets(sor, sizeof(sor), fajl)) {
        printf("%s", sor);
    }

    fclose(fajl);
}

void fajl_beolvas()
{
    char menupont;
    do
    {
        printf("\n1. Krikett beolvasása \n2. X01 beolvasása\n3. Vissza\n\nMenüpont: ");
        scanf(" %c", &menupont);
        while (getchar() != '\n');

        switch (menupont)
        {
        case '1':
            krikett_beolvasas();
            break;
        case '2':
            x01_beolvasas();
            break;
        case '3':
            return;
        default:
            printf("\nHibás menüpont!\n");
            break;
        }

    } while (menupont != '3');
}