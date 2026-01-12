/*
 * Name: Ayush Gupta
 * Date: 12th Jan 2026
 * Title: Lab2 - Step 5 - 
 * Description: Creates 4 processes including parent with different delays
 */
/* C program to demonstrate the use of fork()*/
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* wait */
#include <unistd.h>    /* fork */

/* main function */
int main(int argc, char *argv[]) {
    int process_count = 4; // Total number of processes including parent
    if (argc != 5){
        printf ("Usage: %s <delay1> <delay2> <delay3> <delay4> \n",argv[0]);
        exit(0);
    }    
    pid_t pid; // process id
    int i;  
    printf("\n Before forking.\n");
    int process_number = 0; // To keep track of which child process we are in     
    for (int a = 1; a < process_count; a++){
        pid = fork();
        if (pid == 0){
            process_number = a;
            break;
        }        
    }

    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid) {
        // Parent process: pid is > 0
        for (i = 0; i < 10; i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n", i);
            usleep(atoi(argv[1]));
        }
        for (int a = 1; a < process_count; a++){
            wait(NULL);
        }
    } else {
        // Child process: pid = 0
        for (i = 0; i < 10; i++) {
            printf("I am the child process %d displaying iteration %d\n", process_number, i);
            usleep(atoi(argv[process_number + 1]));
        }
    }
    return 0;
}