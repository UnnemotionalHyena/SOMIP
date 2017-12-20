#include "orders.h"

int get_max_wait(int items[4], struct Food *menu);
int get_the_time(int id, struct Food *menu);

void *cook(void *threadid)
{
    int time = (int)threadid;
    // printf("Time of waiting: %d\n", time);
    sleep(time/5);

    pthread_exit(NULL);
}

int main() 
{
    struct Food menu[8];
    struct Order order[10];
    struct Order *temp;

    srand((unsigned)time(NULL));
    int i, y, t, time, random_time, random_items, random_id, random_priority;
    pthread_t threads[3];

    int thread_error, free_cooks, nr_thread, item;
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));


    initialize_foods(&menu);


    for (i = 0; i < 10; i++)
    {
        random_items = rand() % 4 + 1;
        for (y = 0; y < random_items; y++)
        {
            random_id         = rand() % 8 + 1;
            order[i].items[y] = random_id;
        }
        random_priority   = rand() % 5 + 1;
        order[i].priority = random_priority;
        order[i].max_wait = get_max_wait(order[i].items, &menu);

        push(h, order[i].priority, &order[i]);
    }

    nr_thread = 0;
    for (i = 0; i < 10; i++)
    {
        temp = pop(h);
        item = 0;

        while (1)
        {
            if (!get_the_time((*temp).items[item], &menu) == 0)
            {
                time         = get_the_time((*temp).items[item], &menu);
                thread_error = pthread_create(&threads[nr_thread], NULL, cook, (void *)time);
                if (nr_thread == 2){
                    pthread_join(threads[0], NULL);
                    pthread_join(threads[1], NULL);
                    pthread_join(threads[2], NULL);
                }
                item += 1;
                nr_thread += 1;
                if (thread_error)
                {
                    printf("ERROR; return code from pthread_create() is %d\n", thread_error);
                    exit(-1);
                }
                if (nr_thread == 3)
                {
                    nr_thread = 0;
                }
            }
            else if (get_the_time((*temp).items[item], &menu) == 0)
            {
                if (nr_thread == 3)
                {
                    nr_thread = 0;
                }
                break;
            }
        }
        printf("Order %d finished\n\n",i);
    }

    return 0;
}

int get_max_wait(int items[4], struct Food *menu)
{
    int i, j;
    int time = 0;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (items[i] == menu[j].id && time < menu[j].preparation_time)
            {
                time = menu[j].preparation_time;
            }
        }
    }
    return time * 1.3;
}

int get_the_time(int id, struct Food *menu)
{
    int j, time;
    for (j = 0; j < 8; j++)
    {
        if (id == menu[j].id)
        {
            time = menu[j].preparation_time;
        }
    }

    return time;
}