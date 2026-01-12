/*
 * Name: Ayush Gupta
 * Date: 12th Jan 2026
 * Title: Lab2 - Step 8 - 
 * Description: Creates a thread that runs concurrently with main thread
 */
/* C program to demonstrate the use of fork()*/
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait */
#include <unistd.h>    /* fork */
#include <pthread.h>    /* pthreads */

/* main function */

void * thread_function(void *thread_data){
    int* n = (int*)thread_data;
    for (int i = 0; i < 10; i++) {
        printf("I am the child? thread displaying iteration %d\n", i);
        usleep(*n);
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }    
    int n = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations, taken as command line argument
    pthread_t thread2; 
    int i;  
    printf("\n Before forking.\n");
    if (pthread_create(&thread2, NULL, thread_function, &n) != 0) {
        fprintf(stderr, "can't create thread, error %d\n", errno);
        exit(0);
    }

    for (i = 0; i < 10; i++) {
        printf("\t \t \t I am the original? thread displaying iteration %d \n", i);
        usleep(n);
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "can't join thread, error %d\n", errno);
        exit(0);
    }

    return 0;
}