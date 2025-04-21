#include <pthread.h>
#include <assert.h>
#include <iostream>
#include <time.h>
using namespace std;
int a = 0;
pthread_mutex_t lock; // = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg)
{
    int rt;
    /*
    other type of locks

    timespec timed;
    timed.tv_sec = 0;
    timed.tv_nsec = 5;
    pthread_mutex_trylock(&lock);
    pthread_mutex_timedlock(&lock, &timed);
    */
    for (int i = 0; i < 1000000; i++)
    {
        rt = pthread_mutex_lock(&lock);
        assert(rt == 0);
        a++;
        rt = pthread_mutex_unlock(&lock);
        assert(rt == 0);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL); // NULL is for attr and not the initial value
    pthread_t pt1, pt2;
    int rt;
    rt = pthread_create(&pt1, NULL, thread_function, NULL);
    assert(rt == 0);
    rt = pthread_create(&pt2, NULL, thread_function, NULL);
    assert(rt == 0);

    rt = pthread_join(pt1, NULL);
    assert(rt == 0);
    rt = pthread_join(pt2, NULL);
    assert(rt == 0);
    cout << a << endl;
}