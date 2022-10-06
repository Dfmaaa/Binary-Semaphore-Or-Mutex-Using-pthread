#include <stdio.h>
#include <pthread.h>
struct parameters{
    int thread_num;
    pthread_mutex_t *mutex; //mutex can be global too but this is more fun.
};
void* resource(void *params){
    struct parameters *p = (struct parameters*)params;
    pthread_mutex_lock(p->mutex);
    printf("Resource is being used by thread %d\n", p->thread_num);
    pthread_mutex_unlock(p->mutex); 
    return NULL;
}

int main(void){
    pthread_t threads[4];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    struct parameters ps[4]={{1, &mutex},{2, &mutex},{3, &mutex},{4, &mutex}};
    for(int counter = 0; counter < 4; ++counter)
        pthread_create(&threads[counter], NULL, resource, &ps[counter]);
    for(int counter = 0; counter < 4; ++counter){
        pthread_join(threads[counter], NULL);
		}
}
