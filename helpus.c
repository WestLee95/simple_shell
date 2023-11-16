#include "verma.h"

/**
 *_help_ - Help info for builtin help.
 * Return: no return
 */
void _help_(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, String_findLength(help));
	help = "\tChange the working directory.\n ";
	write(STDOUT_FILENO, help, String_findLength(help));
}
/**
 * help_opt - option for help function
 * Return: no return
*/

void help_opt(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, String_findLength(help));
	help = "\tDisplay information about commands.\n ";
	write(STDOUT_FILENO, help, String_findLength(help));
	help = "Display brief summary of builtin commands.\n";
	write(STDOUT_FILENO, help, String_findLength(help));
}
/**
 * a_help_opt - same stuff
 * Return: no reurn
*/

void a_help_opt(void)
{
	char *help = "alias: alias [-p] [identity[=value]...]\n";

	write(STDOUT_FILENO, help, String_findLength(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, String_findLength(help));
}


/**
 * HELP - function that retrieves help send_messages according builtin
 * @dish: data structure (argz and enter)
 * Return: Return 0
*/
int HELP(verma_shell *dish)
{

	if (dish->argz[1] == 0)
		gen_h();
	else if (concomp(dish->argz[1], "setenv") == 0)
		h_env_setup_env();
	else if (concomp(dish->argz[1], "env") == 0)
		h_env();
	else if (concomp(dish->argz[1], "unsetenv") == 0)
		h_env_setdown_env();
	else if (concomp(dish->argz[1], "help") == 0)
		help_opt();
	else if (concomp(dish->argz[1], "exit") == 0)
		exit_h();
	else if (concomp(dish->argz[1], "cd") == 0)
		_help_();
	else if (concomp(dish->argz[1], "alias") == 0)
		a_help_opt();
	else
		write(STDERR_FILENO, dish->argz[0],
		      String_findLength(dish->argz[0]));

	dish->state = 0;
	return (1);
}
