#include "verma.h"
/**
 * G_ERROR - calls the error according the builtin, syntax or permission
 * @dish: data structure that contains arguments
 * @eva: the error value
 * Return: error
 */
int G_ERROR(verma_shell *dish, int eva)
{
	char *e;

	switch (eva)
	{
	case -1:
		e = info_About_error(dish);
		break;
	case 126:
		e = info_PathError(dish);
		break;
	case 127:
		e = repetitive_msg(dish);
		break;
	case 2:
		if (concomp("exit", dish->argz[0]) == 0)
			e = obtain_exit(dish);
		else if (concomp("cd", dish->argz[0]) == 0)
			e = msg_error_cd(dish);
		break;
	}

	if (e)
	{
		write(STDERR_FILENO, e, String_findLength(e));
		free(e);
	}

	dish->state = eva;
	return (eva);
}
/**
 * sing_rule - Handle crtl + c call in prompt
 * @sig: Signal handler
 */
void sing_rule(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
/**
 * READrule- reads the enter string.
 * @dub: return value of getrule function
 * Return: enter string
 */

char *READrule(int *dub)
{
	char *enter = NULL;
	size_t bufsize = 0;

	*dub = getrule(&enter, &bufsize, stdin);

	return (enter);
}

/**
 * kano - finds builtins and commands
 * @dish: data relevant (argz)
 * Return: 1 on success.
 */
int kano(verma_shell *dish)
{
	int (*builtin)(verma_shell *dish);

	if (dish->argz[0] == NULL)
		return (1);

	builtin = builtINFunctions(dish->argz[0]);

	if (builtin != NULL)
		return (builtin(dish));

	return (execute_cmd(dish));
}
