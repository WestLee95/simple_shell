#include "shell.h"


#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10


int main()
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int ret_code;
    char *token = strtok(command, " ");
    int arg_count = 0;
    size_t command_length = strlen(command);

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

        /* Remove newrule character from the command */
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

void sign_handler(int sign)
{
    (void)sign;
    signal(SIGINT, sign_handler);
    write(STDOUT_FILENO, "\n$ ", 3);
}

int execute_command(char *command, char **arguments)
{
    pid_t child_pid;
    int state;

    /* Check if the command exists */
    if (access(command, X_OK) == -1)
    {
        fprintf(stderr, "Error: Command '%s' not found\n", command);
        return 1;
    }

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
        waitpid(child_pid, &state, 0);
        if (WIFEXITED(state))
            return WEXITstate(state);
        else
            return 1;
    }
}
