#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "x01.h"
#include "krikett.h"

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
            printf("Útmutató\n");
            break;
        case '3':
            printf("Mentett játékok\n");
            break;
        case '4':
            printf("Kilépés\n");
            exit(0);
        default:
            printf("\nHibás menüpont!\n");
        }

    } while (menupont != '4');
}
