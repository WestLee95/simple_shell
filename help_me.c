#include "man.h"

/**
 * gen_help - Entrance spot for help informatio and for help builtins.
 * Return: do not fetch
 */
void gen_help(void)
{
char *help = "$ bash, version 1.0(1)-release\n";

write(STDOUT_FILENO, help, Length_ofString(help));
help = "These commands are defined internally.Type 'help' to see the list";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "Type 'help name' to find out more about the function 'name'.\n\n ";
write(STDOUT_FILENO, help, Length_ofString(help));
help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "unsetenv [variable]\n";
write(STDOUT_FILENO, help, Length_ofString(help));
}


/**
 * help_setup_env - Help setup for the builtin setenv.
 * Return: do not fetch.
 */
void help_setup_env(void)
{
char *help = "setenv: setenv (const char *name, const char *value,";

write(STDOUT_FILENO, help, Length_ofString(help));
help = "int replace)\n\t";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "Add a new path or directory to the environment\n";
write(STDOUT_FILENO, help, Length_ofString(help));
}
/**
 * help_info_env - Help information environment for builtin environ.
 * Return: do not fetch.
 */
void help_info_env(void)
{
char *help = "env: env [option] [name=value] [command [args]]\n\t";

write(STDOUT_FILENO, help, Length_ofString(help));
help = "Print the environment of the shell.\n";
write(STDOUT_FILENO, help, Length_ofString(help));
}


/**
 * exit_help - help information for builtin exit.
 * Return: do not fetch.
 */
void exit_help(void)
{
char *help = "exit: exit [n]\n Exit shell.\n";

write(STDOUT_FILENO, help, Length_ofString(help));
help = "Exits the shell with a status of N. If N is omitted, the exit";
write(STDOUT_FILENO, help, Length_ofString(help));
help = "status is that of the last command executed\n";
write(STDOUT_FILENO, help, Length_ofString(help));
}


/**
 * help_setdown_env - Help information for builtin unset environment.
 * Return: do not fetch.
 */
void help_setdown_env(void)
{
char *help = "unsetenv: unsetenv (const char *name)\n\t";

write(STDOUT_FILENO, help, Length_ofString(help));
help = "Remove an entry completely from the environment\n";
write(STDOUT_FILENO, help, Length_ofString(help));
}
