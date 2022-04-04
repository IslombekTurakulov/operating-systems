#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *myThread(void *dummy) {
    pthread_t thid = pthread_self();
    printf("Thread %lu calculation result: %d\n", thid, ++a);
    return NULL;
}

int main() {
    pthread_t thread_fId;
    pthread_t thread_sId;
    pthread_t thread_tId;
    int result = pthread_create(&thread_fId, (pthread_attr_t *) NULL, myThread, NULL);
    if (result != 0) {
        printf("Error on first thread create, fault code: %d\n", result);
        exit(-1);
    }
    printf("Thread %lu created\n", thread_fId);
    result = pthread_create(&thread_sId, (pthread_attr_t *) NULL, myThread, NULL);
    if (result != 0) {
        printf("Error on second thread create, fault code: %d\n", result);
        exit(-1);
    }
    printf("Thread %lu created\n", thread_sId);
    thread_tId = pthread_self();
    printf("Thread %lu calculation result: %d\n", thread_tId, ++a);
    pthread_join(thread_fId, (void **) NULL);
    pthread_join(thread_sId, (void **) NULL);
    return 0;
}