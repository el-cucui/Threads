#include <pthread.h>
#include <assert.h>
#include <iostream>
using namespace std;
int a = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_function(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock);
        a++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
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