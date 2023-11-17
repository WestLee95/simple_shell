#include "man.h"

/**
 *_help_info - _help_info for builtin help.
 * Return: do not fetch.
 */
void _help_info(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tChange the working directory.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
}
/**
 * help_options - alternative for the help function.
 * Return: do not fetch
*/

void help_options(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tDisplay information about commands.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "Display brief summary of builtin commands.\n";
	write(STDOUT_FILENO, help, Length_ofString(help));
}
/**
 * help_option2 - exact thing.
 * Return: do not fetch.
*/

void help_option2(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, Length_ofString(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, Length_ofString(help));
}


/**
 * HELP_ret - Recovers help notices according to builtin.
 * @shd: data framework with argumentss and key ins.
 * Return: fetch 0
*/
int HELP_ret(man_shell *shd)
{

	if (shd->arggs[1] == 0)
		gen_help();
	else if (con_comp(shd->arggs[1], "setenv") == 0)
		help_setup_env();
	else if (con_comp(shd->arggs[1], "env") == 0)
		help_info_env();
	else if (con_comp(shd->arggs[1], "unsetenv") == 0)
		help_setdown_env();
	else if (con_comp(shd->arggs[1], "help") == 0)
		help_options();
	else if (con_comp(shd->arggs[1], "exit") == 0)
		exit_h();
	else if (con_comp(shd->arggs[1], "cd") == 0)
		_help_info();
	else if (con_comp(shd->arggs[1], "alias") == 0)
		elp_option2();
	else
		write(STDERR_FILENO, shd->arggs[0],
		      String_length(shd->arggs[0]));

	shd->state = 0;
	return (1);
}
