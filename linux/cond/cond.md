#### Condition Variable

**The Producer/Consumer Problem**
This problem is one of the small collection of standard, well-known problems in ***concurrent programming:*** a finite-size buffer and two classes of threads, `producers` and `consumers`, put items into the buffer (producers) and take items out of the buffer (consumers).

A producer must wait until the buffer has space before it can put something in, and a consumer must 
wait until something is in the buffer before it can take something out.

A condition variable represents **a queue of threads** waiting for some condition to be signaled.

Example 4-11 has two such queues, one (less) for producers waiting for a slot in the buffer, and the 
other (more) for consumers waiting for a buffer slot containing information. The example also has a 
mutex, as the data structure describing the buffer must be accessed by **only one thread at a time.**

Example 4-11 The Producer/Consumer Problem and Condition Variables

````c
typedef struct {
    char buf[BSIZE];
    int occupied;
    int nextin;			
    int nextout;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
} buffer_t;

buffer_t buffer;
````

As Example 4-12 shows, the producer thread acquires the mutex protecting the buffer data structure and
then makes certain that space is available for the item being produced. If not, it calls pthread_cond_wait(), which causes it to join the queue of threads waiting for the condition less, representing there is room in the buffer, to be signaled.

At the same time, as part of the call to pthread_cond_wait(), the thread releases its lock on the mutex
. The waiting producer threads depend on consumer threads to signal when the condition is true (as show
n in Example 4-12). When the condition is signaled, the first thread waiting on less is awakened. 
However, before the thread can return from pthread_cond_wait(), it muscquire the lock on the mutex 
again.

This ensures that it again has mutually exclusive access to the buffer data structure. The thread then 
must check that there really is room available in the buffer; if so, it puts its item into the next 
available slot.

At the same time, consumer threads might be waiting for items to appear in the buffer. These threads 
are waiting on the condition variable more. A producer thread, having just deposited something in the 
buffer, calls pthread_cond_signal() to wake up the next waiting consumer. (If there are no waiting 
consumers, this call has no effect.)

Finally, the producer thread unlocks the mutex, allowing other threads to operate on the buffer data 
structure.

Example 4-12 The Producer/Consumer Problem--the ==Producer==

```c
void producer(buffer_t *b, char item)
{
    pthread_mutex_lock(&b->mutex);
    while (b->occupied >= BSIZE)
        pthread_cond_wait(&b->less, &b->mutex);

    assert(b->occupied < BSIZE);

    b->buf[b->nextin++] = item;

    b->nextin %= BSIZE;
    b->occupied++;

    /* now: either b->occupied < BSIZE and b->nextin is the index
       of the next empty slot in the buffer, or
       b->occupied == BSIZE and b->nextin is the index of the
       next (occupied) slot that will be emptied by a consumer
       (such as b->nextin == b->nextout) */

    pthread_cond_signal(&b->more);

    pthread_mutex_unlock(&b->mutex);
}
```


Note the use of the assert() statement; unless the code is compiled with NDEBUG defined, assert() 
does nothing when its argument evaluates to true (that is, nonzero), but causes the program to abort 
if the argument evaluates to false (zero). Such assertions are especially useful in multithreaded 
programs--they immediately point out runtime problems if they fail, and they have the additional 
effect of being useful comments.

The comment that begins /* now: either b->occupied ... */could better be expressed as an assertion, 
but it is too complicated as a Boolean-valued expression and so is given in English.

Both the assertion and the commen are examples of invariants. These are logical statements that should 
not be falsified by the execution of the program, except during brief moments when a thread is 
modifying some of the program variables mentioned in the invariant. (An assertion, of course, should 
be true whenever any thread executes it.)

Using invariants is an extremely useful technique. Even if they are not stated in the program text, think in terms of invariants when you analyze a program.

The invariant in the producer code that is expressed as a comment is always true whenever a thread is 
in the part of the code where the comment appears. If you move this comment to just after the 
mutex_unlock(), this does not necessarily remain true. If you move this comment to just after the 
assert(), this is still true.

The point is that this invariant expresses a property that is true at all times, except when either a 
producer or a consumer is changing the state of the buffer. While a thread is operating on the buffer 
(under the protection of a mutex), it might temporarily falsify the invariant. However, once the 
thread is finished, the invariant should be true again.

Example 4-13 shows the code for the consumer. Its flow is symmetric with that of the producer.

Example 4-13 The **Producer/Consumer** Problem--the ==Consumer==

```c
char consumer(buffer_t *b)
{
    char item;
    pthread_mutex_lock(&b->mutex);
    while(b->occupied <= 0)
        pthread_cond_wait(&b->more, &b->mutex);

    assert(b->occupied > 0);

    item = b->buf[b->nextout++];
    b->nextout %= BSIZE;
    b->occupied--;

    /* now: either b->occupied > 0 and b->nextout is the index
       of the next occupied slot in the buffer, or
       b->occupied == 0 and b->nextout is the index of the next
       (empty) slot that will be filled by a producer (such as
       b->nextout == b->nextin) */

    pthread_cond_signal(&b->less);
    pthread_mutex_unlock(&b->mutex);

    return(item);
}
```
