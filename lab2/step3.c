/*
 * Name: Ayush Gupta
 * Date: 12th Jan 2026
 * Title: Lab2 - Step 3 - 
 * Description: Uses command line arguments for delay
 */
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait */
#include <unistd.h>    /* fork */

/* main function */
int main(int argc, char *argv[]) {
    if (argc != 2){
        printf ("Usage: %s <delay> \n",argv[0]);
        exit(0);
    }    
    int n = atoi(argv[1]); // n is a delay in microseconds inserted in parent and child iterations, taken as command line argument
    pid_t pid; // process id
    int i;  
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid) {
        // Parent process: pid is > 0
        for (i = 0; i < 10; i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(n);
        }
        wait(NULL);
    } else {
        // Child process: pid = 0
        for (i = 0; i < 10; i++) {
            printf("I am the child process displaying iteration %d\n", i);
            usleep(n);
        }
    }
    return 0;
}