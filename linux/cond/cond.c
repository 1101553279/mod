#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct cp{
    char *msg;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

void cp_init(struct cp *cp)
{
    if(NULL != cp)
    {
        cp->msg = NULL;
        pthread_cond_init(&cp->cond, NULL);
        pthread_mutex_init(&cp->mutex, NULL);
    }

    return;
}

void cp_produce(struct cp *cp, char *msg)
{
    pthread_mutex_lock(&cp->mutex);

    cp->msg = msg;                      /* product a msg */
    pthread_cond_signal(&cp->cond);     /* signal consumer that has a valid msg */

    pthread_mutex_unlock(&cp->mutex);
//    pthread_cond_signal(&cp->cond);     /* signal consumer that has a valid msg */

    return;
}

char *cp_consume(struct cp *cp)
{
    char *msg = NULL;
    
    pthread_mutex_lock(&cp->mutex);
    while(NULL == cp->msg)              /* check has a valid msg */
        pthread_cond_wait(&cp->cond, &cp->mutex);   /* wait a signal from producer */

    msg = cp->msg;                      /* consume a msg */
    cp->msg = NULL;
    pthread_mutex_unlock(&cp->mutex);

    return msg;
}

struct produce_arg{
    char *msg;
    struct cp *cp;
};

void *producer_routine(void *parg)
{
    struct produce_arg arg = *(struct produce_arg *)parg;
    while(1)
    {
        cp_produce(arg.cp, arg.msg);
        usleep(89902);
        printf("producer: %s\r\n", arg.msg);
    }

    return NULL;
}

void *consumer_routine(void *parg)
{
    struct cp *cp = (struct cp*)parg;
    char *msg = NULL;
    while(1)
    {
        msg = cp_consume(cp);
        if(NULL != msg)
            printf("consumer: %s", msg);
        sleep(1);
    }


    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t p_a;  /* produce a */
    pthread_t p_b;
    pthread_t p_c;
    pthread_t c_a;
    struct cp cp;
    struct produce_arg arg;

    cp_init(&cp);
    
    arg.msg = "produce A\r\n";
    arg.cp = &cp;
    pthread_create(&p_a, NULL, producer_routine, &arg);

    usleep(23);

    arg.msg = "produce B\r\n";
    arg.cp = &cp;
    pthread_create(&p_b, NULL, producer_routine, &arg);

#if 1
    usleep(11);
    arg.msg = "produce C\r\n";
    arg.cp = &cp;
    pthread_create(&p_c, NULL, producer_routine, &arg);
#endif

    usleep(43);
    pthread_create(&c_a, NULL, consumer_routine, &cp);


    while(1)
        sleep(1);


    return 0;
}
