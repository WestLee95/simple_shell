#include "my_shell.h"

void custom_signal_handler(int signum)
{
	char *new_prompt = "\n$ ";

	(void)signum;
	signal(SIGINT, custom_signal_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

int custom_execute(char **args, char **args_start)
{
	char *command = args[0];
	int execute_flag = 0;

	if (command[0] != '/' && command[0] != '.')
	{
		execute_flag = 1;
		command = custom_get_location(command);
	}

	int return_value = execute_command(command, args, args_start, execute_flag);

	if (execute_flag)
		free(command);

	return (return_value);
}

int execute_command(char *command, char **args,
		char **args_start, int execute_flag)
{
	pid_t child_pid;
	int return_value = 0;

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			return_value = (custom_error_handling(args, 126));
		else
			return_value = (custom_error_handling(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (execute_flag)
				free(command);
			perror("Child process error:");
			return (1);
		}
		if (child_pid == 0)
		{
			return_value = (execute_child_process(command, args, args_start));
		}
		else
		{
			return_value = (wait_for_child_process(child_pid));
		}
	}

	return (return_value);
}

int execute_child_process(char *command, char **args, char **args_start)
{
	execve(command, args, custom_environment);
	if (errno == EACCES)
		return (custom_error_handling(args, 126));

	custom_free_environment();
	custom_free_args(args, args_start);
	custom_free_alias_list(aliases);
	_exit(return_value);
}

int wait_for_child_process(pid_t child_pid)
{
	int status;
	wait(&status);
	return (WEXITSTATUS(status));
}

int main(int argc, char *argv[])
{
	int return_value = 0;

	shell_name = argv[0];
	history_count = 1;
	aliases = NULL;
	signal(SIGINT, custom_signal_handler);

	if (argc != 1)
	{
		return_value = (handle_non_interactive_mode(argv[1]));
	}
	else
	{
		return_value = (handle_interactive_mode(void));
	}

	custom_free_environment();
	custom_free_alias_list(aliases);

	return (return_value);
}

int handle_non_interactive_mode(char *file_path)
{
	int custom_return = 0;
	return (custom_process_files_and_commands(file_path, &custom_return));
}

int handle_interactive_mode()
{
	char *prompt = "$ ", *newline_char = "\n";
	int custom_return = 0;

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		int return_value = custom_handle_args(&custom_return);

		if (return_value == END_OF_FILE || return_value == EXIT)
		{
			if (return_value == END_OF_FILE)
				write(STDOUT_FILENO, newline_char, 1);

			custom_free_environment();
			custom_free_alias_list(aliases);
			exit(custom_return);
		}
	}
}
