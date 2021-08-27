#### 1. About Semaphore
- **P**: **Prolagen** means try to ==decrease==
- **V**: **Verhogen** means ==increase==

#### 2. Two Basic Sorts Of Semaphores
- **Binary Semaphore**: which never take on values other than zero or one
- **Counting Semaphore**: which can take arbitrary nonnegative values

#### 3. Notices
- counting semaphore must use with mutex or binary semaphore, when **P** and **V** refer to the same resources

```c
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

    sem_post(&b->cmut);     /* unlock resource: because finish chaged */
    sem_post(&b->empty);    /* verhogen: V Operation for empty countting semaphore */
    
    return item;
}

```
-  counting semaphore don't need to use **mutex**, when **P** and **V** does not operate the same resource

-  don't need to **mutex**, when the functions **producer** and **consumer** are called by **only one pthread**

