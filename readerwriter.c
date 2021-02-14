typedef struct _rwlock_t
{
    sem_t lock;
    sem_t writelock;
    int readers;        // Number of readers in critical section
    sem_t prioritySem;  // New semaphore to avoid starvation
} rwlock_t;

void rwlock_init(rwlock_t *rw)
{
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
    sem_init(&rw->prioritySem, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw)
{
    sem_wait(&rw->prioritySem); // Add thread to queue of threads
    sem_wait(&rw->lock);
    if (rw->readers == 0)
        sem_wait(&rw->writelock);
    rw->readers++;
    sem_post(&rw->prioritySem); // Remove thread from queue of threads
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw)
{
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0)   // Last reader lets it go
        sem_post(&rw->writelock);
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw)
{
    sem_wait(&rw->prioritySem); // Add thread to queue of threads
    sem_wait(&rw->writelock);
    sem_post(&rw->prioritySem); // Remove thread from queue of threads
}

void rwlock_release_writelock(rwlock_t *rw)
{
    sem_post(&rw->writelock);
}

rwlock_t mutex;
double rtotals = 0;
double wtotals = 0;

void reading_writing(void)
{
    int x = 0;
    int i, j;
    int T = rand() % 10000;

    for (i = 0; i < T; i++)
        for (j = 0; j < T; j++)
            x = i * j;
    return;
}

void *reader(void *arg)
{
    int *tmp = ((int *)arg);
    int id = *tmp;              // Get thread ID from arg
    clock_t start, stop, total; // Create a timer

    start = clock();            // Start the timer
    rwlock_acquire_readlock(&mutex);
    stop = clock();             // Stop the timer
    total = stop - start;       // Find the total time

    reading_writing();

    rwlock_release_readlock(&mutex);

    rtotals += total;           // Add the totals (for averaging)
    printf("READ completed for thread %d\n", id);

    return NULL;
}

void *writer(void *arg)
{
    int *tmp = ((int *)arg);
    int id = *tmp;              // Get thread ID from arg
    clock_t start, stop, total; // Create a timer

    start = clock();            // Start the timer
    rwlock_acquire_writelock(&mutex);
    stop = clock();             // Stop the timer
    total = stop - start;       // Find the total time

    reading_writing();

    rwlock_release_writelock(&mutex);

    wtotals += total;           // Add the totals (for averaging)
    printf("WRITE completed for thread %d\n", id);

    return NULL;
}
