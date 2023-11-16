#include "verma.h"

/**
 * gen_h - Entry point for help info for help builtin
 * Return: no return
 */
void gen_h(void)
{
char *help = "$ bash, version 1.0(1)-release\n";

write(STDOUT_FILENO, help, String_findLength(help));
help = "These commands are defined internally.Type 'help' to see the list";
write(STDOUT_FILENO, help, String_findLength(help));
help = "Type 'help identity' to find out more about the function 'identity'.\n\n ";
write(STDOUT_FILENO, help, String_findLength(help));
help = " alias: alias [identity=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
write(STDOUT_FILENO, help, String_findLength(help));
help = "[dir]\nexit: exit [n]\n  env: env [option] [identity=value] [command ";
write(STDOUT_FILENO, help, String_findLength(help));
help = "[argz]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
write(STDOUT_FILENO, help, String_findLength(help));
help = "unsetenv [variable]\n";
write(STDOUT_FILENO, help, String_findLength(help));
}


/**
 * h_env_setup_env - Help info for builtin setenv
 * Return: no return
 */
void h_env_setup_env(void)
{
char *help = "setenv: setenv (const char *identity, const char *value,";

write(STDOUT_FILENO, help, String_findLength(help));
help = "int replace)\n\t";
write(STDOUT_FILENO, help, String_findLength(help));
help = "Add a new path or directory to the environment\n";
write(STDOUT_FILENO, help, String_findLength(help));
}
/**
 * h_env - Help info for builtin env
 * Return: no return
 */
void h_env(void)
{
char *help = "env: env [option] [identity=value] [command [argz]]\n\t";

write(STDOUT_FILENO, help, String_findLength(help));
help = "Print the environment of the shell.\n";
write(STDOUT_FILENO, help, String_findLength(help));
}


/**
 * exit_h - Help info for builtin exit
 * Return: no return
 */
void exit_h(void)
{
char *help = "exit: exit [n]\n Exit shell.\n";

write(STDOUT_FILENO, help, String_findLength(help));
help = "Exits the shell with a state of N. If N is omitted, the exit";
write(STDOUT_FILENO, help, String_findLength(help));
help = "state is that of the last command executed\n";
write(STDOUT_FILENO, help, String_findLength(help));
}


/**
 * h_env_setdown_env - Help info for builtin unsetenv
 * Return: no return
 */
void h_env_setdown_env(void)
{
char *help = "unsetenv: unsetenv (const char *identity)\n\t";

write(STDOUT_FILENO, help, String_findLength(help));
help = "Remove an entry completely from the environment\n";
write(STDOUT_FILENO, help, String_findLength(help));
}

