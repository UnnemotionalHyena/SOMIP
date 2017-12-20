#include "orders.h"

void push (heap_t *h, int priority,struct Order *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority < priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

struct Order *pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    struct Order * data = h->nodes[1].data;

    h->nodes[1] = h->nodes[h->len];
    int priority = h->nodes[1].priority;

    h->len--;

    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority > priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority > h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}

void initialize_foods(struct Food *menu)
{
    menu[0].id = 1;
    menu[0].preparation_time = 20;
    menu[0].complexity = 2;
    // menu[0].cooking_apparatus = "oven";

    menu[1].id = 2;
    menu[1].preparation_time = 10;
    menu[1].complexity = 1;
    // menu[1].cooking_apparatus = "";

    menu[2].id = 3;
    menu[2].preparation_time = 7;
    menu[2].complexity = 1;
    // menu[2].cooking_apparatus = "stove";

    menu[3].id = 4;
    menu[3].preparation_time = 32;
    menu[3].complexity = 3;
    // menu[3].cooking_apparatus = "";

    menu[4].id = 5;
    menu[4].preparation_time = 35;
    menu[4].complexity = 3;
    // menu[4].cooking_apparatus = "oven";

    menu[5].id = 6;
    menu[5].preparation_time = 10;
    menu[5].complexity = 1;
    // menu[5].cooking_apparatus = "stove";

    menu[6].id = 7;
    menu[6].preparation_time = 20;
    menu[6].complexity = 2;
    // menu[6].cooking_apparatus = "";

    menu[7].id = 8;
    menu[7].preparation_time = 30;
    menu[7].complexity = 2;
    // menu[7].cooking_apparatus = "oven";
}