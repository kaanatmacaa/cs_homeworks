#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

// Kaan Atmaca 28239

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe(fd)");
        exit(1);
    }
    printf("I’m SHELL process, with PID: %d - Main command is: man ls | grep \"--after-context\" \"1\" \"-e\" \"-Z\" \n", getpid());

    int pid1 = fork();
    if (pid1 < 0)
    {
        perror("pid1");
        exit(1);
    }
    else if (pid1 == 0)
    {
        printf("I’m MAN process, with PID: %d - My command is: man ls \n", getpid());
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]); // closeing the read fd
        char *cmd = "man";
        char *my[3];
        my[0] = "man";
        my[1] = "ls";
        my[2] = NULL;
        execvp(cmd, my);
    }

    int pid2 = fork();
    if (pid2 < 0)
    {
        perror("pid2");
        exit(1);
    }
    else if (pid2 == 0 && pid1 != 0)
    {
        printf("I’m GREP process, with PID: %d - My command is: grep \"--after-context\" \"1\" \"-e\" \"-Z\" \n", getpid());
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]); // closing the write fd
        close(fd[0]);
        char *cmd = "grep";
        char *my[5];
        my[0] = "grep";
        my[1] = "--after-context";
        my[2] = "1";
        my[3] = "-e";
        my[4] = "-Z";
        my[5] = NULL;
        int new_fd = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
        if (dup2(new_fd, STDOUT_FILENO) < 0)
        {
            perror("dup2");
            exit(1);
        }
        execvp(cmd, my);
    }

    close(fd[1]);
    close(fd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("I’m SHELL process, with PID: %d - execution is completed, you can find the results in output.txt \n", getpid());
    return 0;
}