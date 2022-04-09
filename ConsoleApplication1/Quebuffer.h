
#ifndef Quebuffer_H
#define Quebuffer_H
#include <pthread.h>
#include <queue>
template <typename T>
class Quebuffer {
private:
    std::queue<T> buffer_item; 
    pthread_mutex_t QueryMX;
       
    pthread_cond_t CondtitionalMX;
public:
    Quebuffer(); //constructor 
    void addbuffer_item(T b_item); // add bufferdata in queue
    T remove(); // pop the bufferdata
};

template <typename T>
Quebuffer<T>::Quebuffer()
{
    pthread_mutex_init(&QueryMX, NULL);
    pthread_cond_init(&CondtitionalMX, NULL);
}

template <typename T>
void Quebuffer<T>::addbuffer_item(T b_item)
{
    pthread_mutex_lock(&QueryMX);
    buffer_item.push(b_item);
    pthread_cond_signal(&CondtitionalMX);
    pthread_mutex_unlock(&QueryMX);
}
template <typename T>
T Quebuffer<T>::remove()
{
    pthread_mutex_lock(&QueryMX);
    while (buffer_item.size() == 0){pthread_cond_wait(&CondtitionalMX, &QueryMX);}
    T b_item = buffer_item.front();
    buffer_item.pop();
    pthread_mutex_unlock(&QueryMX);
    return b_item;
}
#endif