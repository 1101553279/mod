#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BSIZE 10
typedef struct {
    char buf[BSIZE];/* for storing items */
    int nextin;     /* for producer puts a item */
    int nextout;    /* for consumer gets a item */

    sem_t occupied; /* occupied counting semaphore */
    sem_t empty;    /* empty counting semaphore */
    sem_t pmut;     /* puducer mutex lock */
    sem_t cmut;     /* consumer mutex lock */
} buffer_t;

buffer_t buffer;

/* init a buffer_t information */
void buffer_init(buffer_t *b)
{
    sem_init(&b->occupied, 0, 0);
    sem_init(&b->empty,0, BSIZE);
    sem_init(&b->pmut, 0, 1);
    sem_init(&b->cmut, 0, 1);
    b->nextin = b->nextout = 0;
    
    return;
}

/* producer do: maybe **multiple pthreads** call this, so **must lock** when change ==nextin== */
void buffer_producer(buffer_t *b, char item)
{
    sem_wait(&b->empty);    /* prolagen: P operation */
    sem_wait(&b->pmut);     /* lock resource: prepare to change share variables */
    printf("producer '%lu': put item '%c'\r\n", pthread_self(), item); 

    b->buf[ b->nextin ] = item;
    b->nextin++;
    b->nextin %= BSIZE;

    sem_post(&b->pmut);     /* unlock resource: because finish changed */
    sem_post(&b->occupied); /* verhogen: V operation for occupied countting semaphore */
    
    return;
}

/* consumer do: maybe **multiple pthreads** call this, so **must lock** when change ==nextout== */
char buffer_consumer(buffer_t *b)
{
    char item;

    sem_wait(&b->occupied);	/* prolagen: P operation */
    sem_wait(&b->cmut);     /* locke resource: prepare to change share variables */

    item = b->buf[ b->nextout ];
    b->nextout++;
    b->nextout %= BSIZE;

    printf("-- consumer '%lu': get item '%c'\r\n", pthread_self(), item); 
    sem_post(&b->cmut);     /* unlock resource: because finish chaged */
    sem_post(&b->empty);    /* verhogen: V Operation for empty countting semaphore */
    
    return item;
}

struct routine_arg{
    buffer_t *b;
    char c;
};
void *producer_routine(void *arg)
{
    struct routine_arg *p = (struct routine_arg *)arg;

    while(1)
    {
        buffer_producer(p->b, p->c);
        sleep(1);
    }
    return NULL;
}

void *consumer_routine(void *arg)
{
    struct routine_arg *p = (struct routine_arg *)arg;

    while(1)
    {
        buffer_consumer(p->b);
        usleep(1000*550);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    int occupied_val = 0;
    int empty_val = 0;
    pthread_t c_p_a;
    pthread_t c_p_b;
    pthread_t p_p_c;
    pthread_t p_p_d;
    struct routine_arg arg_list[] = {{&buffer, 'a'}, {&buffer, 'b'}, {&buffer, 'c'}, {&buffer, 'd'}};
    printf("This is a semaphore example!\r\n");
    
    buffer_init(&buffer);

    pthread_create(&c_p_a, NULL, producer_routine, &arg_list[0]);
    pthread_create(&c_p_b, NULL, producer_routine, &arg_list[1]);
    pthread_create(&p_p_c, NULL, consumer_routine, &arg_list[2]);
//    pthread_create(&p_p_d, NULL, consumer_routine, &arg_list[3]);

    while(1)
    {
        sem_getvalue(&buffer.occupied, &occupied_val);
        sem_getvalue(&buffer.empty, &empty_val);
        printf("occupied value: %d, empty value: %d\r\n", occupied_val, empty_val);
        usleep(1000*100);
    }

    return 0;
}
