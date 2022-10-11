#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    
    int pid = fork();
    if (pid == -1) {
        return 2;
    }
    
    if (pid == 0) {
        // Child  process
        close(fd[0]);
    
        char str[200];
        printf("Input string: ");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';
        
        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) < 0) {
            return 3;
        }
        printf("Sent n = %d\n", n);
        
        if (write(fd[1], &str, sizeof(char) * n) < 0) {
            return 4;
        }
        
        printf("Sent string\n");
        close(fd[1]);
    } else {
        close(fd[1]);
        char str[200];
        int n;
        
        if (read(fd[0], &n, sizeof(int)) < 0) {
            return 5;
        }
        printf("Received n = %d\n", n);
        if (read(fd[0], &str, sizeof(int) * n) < 0) {
            return 6;
        }
        printf("Received string %s\n", str);
        
        close(fd[0]);
        wait(NULL);
    }
    
    return 0;
}