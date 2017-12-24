#include "orders.h"

void initialize_foods(struct Food *menu)
{
    menu[0].id               = 0;
    menu[0].preparation_time = 20;
    menu[0].complexity       = 2;
    strcpy(menu[0].cooking_apparatus, "oven");

    menu[1].id               = 1;
    menu[1].preparation_time = 10;
    menu[1].complexity       = 1;
    strcpy(menu[1].cooking_apparatus, "");

    menu[2].id               = 2;
    menu[2].preparation_time = 7;
    menu[2].complexity       = 1;
    strcpy(menu[2].cooking_apparatus, "stove");

    menu[3].id               = 3;
    menu[3].preparation_time = 32;
    menu[3].complexity       = 3;
    strcpy(menu[3].cooking_apparatus, "");

    menu[4].id               = 4;
    menu[4].preparation_time = 35;
    menu[4].complexity       = 3;
    strcpy(menu[4].cooking_apparatus, "oven");

    menu[5].id               = 5;
    menu[5].preparation_time = 10;
    menu[5].complexity       = 1;
    strcpy(menu[5].cooking_apparatus, "stove");

    menu[6].id               = 6;
    menu[6].preparation_time = 20;
    menu[6].complexity       = 2;
    strcpy(menu[6].cooking_apparatus, "");

    menu[7].id               = 7;
    menu[7].preparation_time = 30;
    menu[7].complexity       = 2;
    strcpy(menu[7].cooking_apparatus, "oven");
}