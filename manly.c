#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_COMMAND_LENGTH 100

void sign_handler(int sign)
{
    (void)sign;
    signal(SIGINT, sign_handler);
    write(STDIN_FILENO, "\n$ ", 3);
}

int execute_command(char *command)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error creating child process");
        return 1;
    }

    if (child_pid == 0)
    {
        execlp(command, command, (char *)NULL);
        perror("Error executing command");
        _exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return 1;
    }
}

int main()
{
    char command[MAX_COMMAND_LENGTH];
    int ret_code;
    size_t command_length = strlen(command);

    signal(SIGINT, sign_handler);

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /*Handle end of file (Ctrl+D)*/
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /*Remove newline character from the command*/
        if (command_length > 0 && command[command_length - 1] == '\n')
            command[command_length - 1] = '\0';

        ret_code = execute_command(command);

        if (ret_code != 0)
            fprintf(stderr, "Error: Command failed with exit code %d\n", ret_code);
    }

    return 0;
}
