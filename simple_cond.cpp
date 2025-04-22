#include <iostream>
#include <pthread.h>
#include <assert.h>

using namespace std;

pthread_mutex_t lock;
pthread_cond_t cond;

int a = 0;
int wait_count = 0;

void *adding(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock);
        a++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *removing(void *arg)
{
    for (int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&lock);
        while (a == 0)
        {
            wait_count++;
            pthread_cond_wait(&cond, &lock);
        }
        a--;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_t pt1, pt2;
    int rt;
    rt = pthread_create(&pt1, NULL, adding, NULL);
    assert(rt == 0);
    rt = pthread_create(&pt2, NULL, removing, NULL);
    assert(rt == 0);

    rt = pthread_join(pt1, NULL);
    assert(rt == 0);
    rt = pthread_join(pt2, NULL);
    assert(rt == 0);
    cout << "Wait count: " << wait_count << " result: " << a << endl;
    return 0;
}