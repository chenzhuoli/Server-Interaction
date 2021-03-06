/**//*
    (C) OOMusou 2006 http://oomusou.cnblogs.com

     Filename : pthread_create_semaphore.cpp
     Compiler : gcc 4.10 on Fedora 5 / gcc 3.4 on Cygwin 1.5.21
     Description : Demo how to create thread with semaphore in Linux.
     Release : 12/03/2006
     Compile : g++ -lpthread pthread_create_semaphore.cpp
    */
#include <stdio.h> // printf(),
#include <stdlib.h> // exit(), EXIT_SUCCESS
#include <pthread.h> // pthread_create(), pthread_join()
#include <semaphore.h> // sem_init()
#include <unistd.h> //sleep()

sem_t binSem;

void* helloWorld(void* arg);

int main() {
     // Result for System call
    int res = 0;

     // Initialize semaphore
     res = sem_init(&binSem, 0, 0);
    if (res) {
         printf("Semaphore initialization failed!!/n");
         exit(EXIT_FAILURE);
     }

     // Create thread
     pthread_t thdHelloWorld;
     res = pthread_create(&thdHelloWorld, NULL, helloWorld, NULL);
    if (res) {
         printf("Thread creation failed!!/n");
         exit(EXIT_FAILURE);
     }

    while(1) {
         // Post semaphore
         sem_post(&binSem);
         printf("In main, sleep several seconds.\n");
        sleep(1);
     }

     // Wait for thread synchronization
     void *threadResult;
     res = pthread_join(thdHelloWorld, &threadResult);
    if (res) {
         printf("Thread join failed!!\n");
         exit(EXIT_FAILURE);
     }

     exit(EXIT_SUCCESS);
}

void* helloWorld(void* arg) {
    while(1) {
         // Wait semaphore
         sem_wait(&binSem);
         printf("Hello World\n");
     }
}
