#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
// main
int main(int argc, char* argv[]) {
    int fds[2];
    char buff[60];
    int count;
    int i;
    pipe(fds);
    if (fork() == 0) {
        printf("upstream end writer process\n");
        close(fds[0]);
        char msg[60];
        int len = snprintf(msg, sizeof(msg), "Message from writer process\n");
        write(fds[1], msg, len);
        printf("upstream end writer process done\n");
        exit(0);
    } 
    else if (fork() == 0) {
        printf("\nConsumer (reader) on downstream end of the pipe\n");
        close(fds[1]); 

        while ((count = read(fds[0], buff, sizeof(buff))) > 0) {
            // print what we received
            write(1, buff, count);
        }

        close(fds[0]);
        exit(0);
    }
     else {
        close(fds[0]);
        close(fds[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
