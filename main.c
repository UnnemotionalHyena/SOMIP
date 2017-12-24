#include "orders.h"
#include "queue.h"
#include "prioritize_queue.h"

#define NUMBER_ORDERS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct Order orders[NUMBER_ORDERS];
struct Queue *queue;
heap_t *h;

int nr_order = 1;
int pending_orders[3];

const struct Food menu[8];

int get_max_wait(struct Order order);
int get_the_time(int id, struct Food *menu);

void *cook(void *cook_id)
{
    int id = (int)cook_id;

    int i;
    struct Order *order_temp;
    struct QNode *food_id;

    while (1)
    {
        pthread_mutex_lock(&mutex);

        food_id = deQueue(queue);

        pthread_mutex_unlock(&mutex);
        if (food_id == NULL)
        {
            pthread_mutex_lock(&mutex);

            order_temp = prioritize_pop(h);
            if (order_temp != -1)
            {
                for (i = 0; i < (*order_temp).items_size; i++)
                {
                    enQueue(queue, (int)(*order_temp).items[i].id, nr_order);
                }
                nr_order += 1;
            }

            pthread_mutex_unlock(&mutex);
        }
        else
        {
            printf("\nCook %d id working %d seconds(minutes) on order %d", id, menu[food_id->key].preparation_time, food_id->order);
            pending_orders[id] = (int)food_id->order;

            sleep(((int)menu[food_id->key].preparation_time)/3);

            pending_orders[id] = -1;
        }
    }

    pthread_exit(NULL);
}

void *waitress(void *waitress_id)
{
    int id = (int)waitress_id;

    int i, y, random_time, random_items, random_id, random_priority;

    for (i = 0; i < NUMBER_ORDERS; i++)
    {
        random_items    = rand() % 4 + 1;
        orders[i].items = (struct Food*) malloc(random_items * sizeof(struct Food));
        for (y = 0; y < random_items; y++)
        {
            random_id = rand() % 8 + 1;

            orders[i].items[y].id               = menu[random_id].id;
            orders[i].items[y].preparation_time = menu[random_id].preparation_time;
            orders[i].items[y].complexity       = menu[random_id].complexity;
            strcpy(orders[i].items[y].cooking_apparatus, menu[random_id].cooking_apparatus);
        }

        orders[i].items_size = random_items;
        random_priority      = rand() % 5 + 1;
        orders[i].priority   = random_priority;
        orders[i].max_wait   = get_max_wait(orders[i]);

        pthread_mutex_lock(&mutex);
        prioritize_push(h, orders[i].priority, &orders[i]);
        pthread_mutex_unlock(&mutex);
        printf("\nCame one order");
        sleep((rand() % (4 + 1 - 2)) + 2);
    }

    pthread_exit(NULL);
}

void *checker(void *checker_id)
{
    int id = (int)checker_id;
    int food_id = 1;
    int last_order = 0;
    // printf("checker initialized");
    while(1)
    {
        while(pending_orders[0] != 0 || pending_orders[1] != 0 || pending_orders[2] != 0)
        {
            if (pending_orders[0] == -1 && pending_orders[1] == -1 && pending_orders[2] == -1 && last_order)
            {
                // do nothing, wait for other orders
            }
            else if (pending_orders[0] == -1 && pending_orders[1] == -1 && pending_orders[2] == -1 && !last_order)
            {
                printf("\nOrder %d is ready\n", food_id);
                last_order = 1;
            }
            else if (pending_orders[0] != food_id && pending_orders[1] != food_id && pending_orders[2] != food_id)
            {
                printf("\nOrder %d is ready\n", food_id);
                food_id += 1;
                last_order = 0;
            }
        }
    }
}

int main()
{
    pthread_t cook_threads[3], waitress_thread, checker_thread;
    int i, thread_error;
    srand((unsigned)time(NULL));

    initialize_foods(&menu);

    h     = (heap_t *)calloc(1, sizeof (heap_t));
    queue = createQueue();

    pending_orders[0] = 0;
    pending_orders[1] = 0;
    pending_orders[2] = 0;

    for (i = 0; i < 3; i++)
    {
        thread_error = pthread_create(&cook_threads[i], NULL, cook, (void *)i);
        if (thread_error)
        {
            printf("ERROR; return code from pthread_create() is %d\n", thread_error);
            exit(-1);
        }
    }

    thread_error = pthread_create(&waitress_thread, NULL, waitress, (void *)0);
    if (thread_error)
    {
        printf("ERROR; return code from pthread_create() is %d\n", thread_error);
        exit(-1);
    }

    thread_error = pthread_create(&checker_thread, NULL, checker, (void *)0);
    if (thread_error)
    {
        printf("ERROR; return code from pthread_create() is %d\n", thread_error);
        exit(-1);
    }

    pthread_join(cook_threads[0], NULL);
    pthread_join(cook_threads[1], NULL);
    pthread_join(cook_threads[2], NULL);
    pthread_join(waitress_thread, NULL);
    pthread_join(checker_thread, NULL);
    return 0;
}

int get_max_wait(struct Order order)
{
    int j;
    int time = 0;

    for (j = 0; j < order.items_size; j++)
    {
        if (time < order.items[j].preparation_time)
        {
            time = order.items[j].preparation_time;
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