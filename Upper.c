#include "verma.h"
/**
 * examine_dir - checks ":" if is in the current directory.
 * @path: the type char pointer char.
 * @m: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int examine_dir(char *path, int *m)
{
	if (path[*m] == ':')
		return (1);

	while (path[*m] != ':' && path[*m])
	{
		*m += 1;
	}

	if (path[*m])
		*m += 1;

	return (0);
}
/**
 * z_cmd - locates a command
 * @cmd: command identity
 * @environ_var: environment variable
 * Return: location of the command.
 */
char *z_cmd(char *cmd, char **environ_var)
{
	char *path, *ptr_path, *token_path, *d;
	int len_dir, len_cmd, u;
	struct stat st;

	path = obtainenv("PATH", environ_var);
	if (path)
	{
		ptr_path = Moon(path);
		len_cmd = String_findLength(cmd);
		token_path = cut_string(ptr_path, ":");
		u = 0;
		while (token_path != NULL)
		{
			if (examine_dir(path, &u))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = String_findLength(token_path);
			d = malloc(len_dir + len_cmd + 2);
			concpy(d, token_path);
			concat(d, "/");
			concat(d, cmd);
			concat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = cut_string(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}
/**
 * check_f - determines if is an executable
 * @dish: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int check_f(verma_shell *dish)
{
	struct stat st;
	int u;
	char *enter;

	enter = dish->argz[0];
	for (u = 0; enter[u]; u++)
	{
		if (enter[u] == '.')
		{
			if (enter[u + 1] == '.')
				return (0);
			if (enter[u + 1] == '/')
				continue;
			else
				break;
		}
		else if (enter[u] == '/' && u != 0)
		{
			if (enter[u + 1] == '.')
				continue;
			u++;
			break;
		}
		else
			break;
	}
	if (u == 0)
		return (0);

	if (stat(enter + u, &st) == 0)
	{
		return (u);
	}
	G_ERROR(dish, 127);
	return (-1);
}
/**
 * check_SU_permission_cmd - verifies if user has permissions to access
 * @d: destination directory
 * @dish: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_SU_permission_cmd(char *d, verma_shell *dish)
{
	if (d == NULL)
	{
		G_ERROR(dish, 127);
		return (1);
	}

	if (concomp(dish->argz[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			G_ERROR(dish, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(dish->argz[0], X_OK) == -1)
		{
			G_ERROR(dish, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - executes command rules
 * @dish: data relevant
 * Return: 1 on success.
 */
int execute_cmd(verma_shell *dish)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int executable;
	char *d;
	(void) wpd;

	executable = check_f(dish);
	if (executable == -1)
		return (1);
	if (executable == 0)
	{
		d = z_cmd(dish->argz[0], dish->environ_var);
		if (check_for_permission(d, dish) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (executable == 0)
			d = z_cmd(dish->argz[0], dish->environ_var);
		else
			d = dish->argz[0];
		execve(d + executable, dish->argz, dish->environ_var);
	}
	else if (pd < 0)
	{
		perror(dish->verma[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	dish->state = state / 256;
	return (1);
}
