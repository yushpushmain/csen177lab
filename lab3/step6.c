#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char* argv[]) {
    key_t key = 1234;

    int id = shmget(key, 60, IPC_CREAT | 0666);
    if (id == -1) {
        perror("shmget");
        return 1;
    }

    // Parent attaches and WRITES first
    char *data = (char*)shmat(id, NULL, 0);
    if (data == (char*)-1) {
        perror("shmat (parent)");
        return 1;
    }

    char msg[60];
    snprintf(msg, sizeof(msg), "Message from parent process\n");

    // Copy message into shared memory (include terminating '\0')
    memcpy(data, msg, strlen(msg) + 1);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        shmdt(data);
        return 1;
    }

    if (pid == 0) {
        // Child attaches and reads data
        char *data = shmat(id, NULL, 0);
        printf("Child process reading from shared memory:\n");
        printf("%s", data);

        shmdt(data);
        exit(0);
    }

    // Parent
    wait(NULL);
    shmdt(data);

    return 0;
}
