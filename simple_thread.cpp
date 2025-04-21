#include <iostream>
#include <pthread.h>
using namespace std;

int a = 0;
void *thread_function(void *arg)
{
    cout << (char *)arg << endl;
    for (int i = 0; i < 1000000; i++)
    {
        a++;
    }
    return (void *)a;
}

int main()
{
    pthread_t pt, pt2;
    int rt = pthread_create(&pt, NULL, thread_function, (void *)"A");
    if (rt != 0)
        cout << "Error in pthread creation\n";
    rt = pthread_create(&pt2, NULL, thread_function, (void *)"B");
    if (rt != 0)
        cout << "Error in pthread creation 2\n";
    int x;
    pthread_join(pt, (void **)&x);
    cout << "A: " << x << endl;
    pthread_join(pt2, (void **)&x);
    cout << "B: " << x << endl;
    cout << a << endl;
}