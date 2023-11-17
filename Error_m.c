#include "man.h"
/**
 * err_call - Signals the error depending on the syntax, builtin or permission.
 * @shd: data framework withs args.
 * @ave: The error worth.
 * Return: error
 */
int err_call(man_shell *shd, int ave)
{
	char *w;

	switch (ave)
	{
	case -1:
		w = disp_error_info(shd);
		break;
	case 126:
		w = display_path_error(shd);
		break;
	case 127:
		w = *cmdNotFound_msg(shd);
		break;
	case 2:
		if (con_comp("exit", shd->arggs[0]) == 0)
			w = exitIn_get(dsh);
		else if (con_comp("cd", shd->arggs[0]) == 0)
			w = error_cd(shd);
		break;
	}

	if (w)
	{
		write(STDERR_FILENO, w, String_length(e));
		free(w);
	}

	shd->state = ave;
	return (ave);
}
/**
 * sing_line_handler - Handle control + c signal in alert.
 * @signal: Sig line handler.
 */
void sing_line_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * READ_LINE- take the key in of string.
 * @duber: fetch worth of the getLine function
 * Return: enter string
 */

char *READ_LINE(int *dubber)
{
	char *enter = NULL;
	size_t bufsize = 0;

	*dub = getline(&enter, &bufsize, stdin);

	return (enter);
}

/**
 * find_command - Locates the commands and biltins.
 * @shd: data essential args.
 * Return: fetch 1 if there's success.
 */
int find_command(man_shell *shd)
{
	int (*builtin)(man_shell *shd);

	if (shd->arggs[0] == NULL)
		return (1);

	builtin = builtINFunctions(shd->arggs[0]);

	if (builtin != NULL)
		return (builtin(shd));

	return (execute_cmd(shd));
}
