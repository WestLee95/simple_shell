#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

/* Signal handler for interrupt (Ctrl+C) */
void sign_handler(int sign)
{
    (void)sign;
    signal(SIGINT, sign_handler);
    write(STDOUT_FILENO, "\n$ ", 3);
}

/* Execute a command with arguments */
int execute_command(char *command, char **arguments)
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
        /* Execute the command with arguments */
        execvp(command, arguments);
        perror("Error executing command");
        _exit(EXIT_FAILURE);
    }
    else
    {
        /* Wait for the child process to finish */
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
    char *arguments[MAX_ARGUMENTS];
    int ret_code;
    size_t command_length = strlen(command);
    char *token = strtok(command, " ");
    int arg_count = 0;

    signal(SIGINT, sign_handler);

    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Handle end of file (Ctrl+D) */
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        /* Remove newline character from the command */
        if (command_length > 0 && command[command_length - 1] == '\n')
            command[command_length - 1] = '\0';

        /* Tokenize the command and arguments */
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1)
        {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL; /* Null-terminate the array */

        /* Execute the command with arguments */
        ret_code = execute_command(arguments[0], arguments);

        if (ret_code != 0)
            fprintf(stderr, "Error: Command failed with exit code %d\n", ret_code);
    }

    return 0;
}