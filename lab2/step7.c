/*
 * Name: Ayush Gupta
 * Date: 12th Jan 2026
 * Title: Lab2 - Step 7 - 
 * Description: Creates a child process that runs "ls" command
 */
/* C program to demonstrate the use of fork() */
#include <errno.h>     /* errno */
#include <stdio.h>     /* printf, stderr */
#include <stdlib.h>    /* atoi */
#include <sys/types.h> /* pid_t */
#include <unistd.h>    /* fork */
#include <sys/wait.h>  /* wait */

/* main function */
int main() {
    pid_t pid;  // process id
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(0);
    }
    if (pid) {
        // Parent process: pid is > 0
        wait(NULL);
        printf("Child has completed the task! \n");
        exit(0);
    } 
    else {
        // Child process: pid = 0
        execlp("/bin/ls", "ls", 0);
    }
    return 0;
}