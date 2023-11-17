#include "man.h"
/**
 * check_directory - examine ":" if it's in the present directory.
 * @route: the kind of character pointer.
 * @m: kind of  int reference of index.
 * Return:fetch 1 if the route is explorable in the change directory, else 0.
 */
int check_directory(char *route, int *m)
{
	if (route[*m] == ':')
		return (1);

	while (route[*m] != ':' && route[*m])
	{
		*m += 1;
	}

	if (route[*m])
		*m += 1;

	return (0);
}
/**
 * locate_command - finds a directive.
 * @cmd: directive name
 * @environ_var: ENV VARS.
 * Return: address of the directive.
 */
char *locate_command(char *cmd, char **environ_var)
{
	char *route, *ptr_path, *token_path, *d;
	int len_dir, len_cmd, u;
	struct stat st;

	route = get_env_var("PATH", environ_var);
	if (route)
	{
		ptr_path = dup_mem(route);
		len_cmd = String_length(cmd);
		token_path = string_split(ptr_path, ":");
		u = 0;
		while (token_path != NULL)
		{
			if (check_directory(route, &u))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = String_length(token_path);
			d = malloc(len_dir + len_cmd + 2);
			*dup_string(d, token_path);
			*string_concat(d, "/");
			*string_concat(d, cmd);
			*string_concat(d, "\0");
			if (stat(d, &st) == 0)
			{
				free(ptr_path);
				return (d);
			}
			free(d);
			token_path = string_split(NULL, ":");
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
 * if_executable - dictates if it is feasible.
 * @shd: data framework
 * Return: fetch 0 if it's feasible, fetch another number if it's not.
 */
int if_executable(man_shell *shd)
{
	struct stat st;
	int u;
	char *enter;

	enter = shd->arggs[0];
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
	err_call(shd, 127);
	return (-1);
}
/**
 * check_user_perm_cmd - confirm if hte user is allowed to access.
 * @d: landing directory
 * @shd: data framework.
 * Return:fetch 1 if  an error occurs and 0 if otherwise.
 */
int check_user_perm_cmd(char *d, man_shell *shd)
{
	if (d == NULL)
	{
		err_call(shd, 127);
		return (1);
	}

	if (con_comp(shd->arggs[0], d) != 0)
	{
		if (access(d, X_OK) == -1)
		{
			err_call(shd, 126);
			free(d);
			return (1);
		}
		free(d);
	}
	else
	{
		if (access(shd->arggs[0], X_OK) == -1)
		{
			err_call(shd, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_cmd - carry out command lines
 * @shd: data essential.
 * Return: fetch 1 it's successful.
 */
int execute_cmd(man_shell *shd)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int executable;
	char *d;
	(void) wpd;

	executable = check_e(shd);
	if (executable == -1)
		return (1);
	if (executable == 0)
	{
		d = locate_command(shd->arggs[0], shd->environ_var);
		if (check_user_perm_cmd(d, dsh) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (executable == 0)
			d = locate_command(shd->arggs[0], shd->environ_var);
		else
			d = shd->arggs[0];
		execve(d + executable, shd->arggs, shd->environ_var);
	}
	else if (pd < 0)
	{
		perror(shd->man[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shd->state = state / 256;
	return (1);
}
