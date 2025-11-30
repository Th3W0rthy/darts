#include <stdio.h>
#include <stdlib.h>
#include <debugmalloc.h>
#include "../include/menu.h"
#include "../include/x01.h"
#include "../include/krikett.h"

void jatekok_menu()
{
    char menupont;
    do
    {
        printf("\n1. X01\n2. Krikett\n3. Vissza\n\nMenüpont: ");
        scanf(" %c", &menupont);

        switch (menupont)
        {
        case '1':
            x01_menu();
            break;
        case '2':
            krikett_menu();
            break;
        case '3':
            return;
        default:
            printf("\nHibás menüpont!\n");
        }
    } while (menupont != '3');
}

void utmutato_menu()
{
    printf("\n--Útmutató--\n\n"
    "- Menü használata:\n"
    "A menüben a menüpont sorszámát kell írni és\nutána entert kell nyomni és átnavigál a választott menüpontra.\n"
    "- Dobások beírása:\n"
    "A dobásokat többféle képpen is be lehet írni.\nAlapvetően, ha szimplát dob a játékos csak a számot kell beírni.\n"
    "Amikor duplát vagy triplát dob, akkor a szám elé be kell írni a 'd' vagy 't' betűt.\n"
    "Ha a játékos érvénytelent dobott, akkor be tud írni 1 vagy 2 dobást is.\n"
    "A dobásokat vesszővel, szóközzel vagy mindkettővel kell elválasztani.\n"
    "- Kilépni úgy tudsz, hogy a dobás helyett -1-et írsz be.\n"
    "- Ha kilépsz egy játékból a dobások elvesznek és újrakezdődik a játék!\n"
    );
}

void menu()
{
    char menupont;
    do
    {
        printf("\n1. Új játék \n2. Útmutató \n3. Mentett játékok \n4. Kilépés\n\nMenüpont: ");
        scanf(" %c", &menupont);

        switch (menupont)
        {
        case '1':
            jatekok_menu();
            break;
        case '2':
            utmutato_menu();
            break;
        case '3':
            printf("Mentett játékok\n");
            break;
        case '4':
            x01_felszabadit();
            krikett_felszabadit();
            printf("Kilépés\n");
            exit(0);
        default:
            printf("\nHibás menüpont!\n");
        }

    } while (menupont != '4');
}
