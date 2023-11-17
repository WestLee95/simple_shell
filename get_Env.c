#include "man.h"

/**
 * print_env_var - Display the env vars.
 * @shd: Data essential.
 * Return: fetch 1 if successful.
 */
int print_env_var(man_shell *shd)
{
	int g, h;

	for (g = 0; shd->environ_var[g]; g++)
	{

		for (h = 0; shd->environ_var[g][h]; h++)
			;

		write(STDOUT_FILENO, shd->environ_var[g], h);
		write(STDOUT_FILENO, "\n", 1);
	}
	shd->state = 0;

	return (1);
}
/**
 * comp_env_names - weigh out environment variable names.
 * including the name to be passed.
 * @newenv: Identity of the env var.
 * @tag: the name to be passed.
 * Return:fetch 0 if they are not equal or another value otherwise.
 */
int comp_env_names(const char *newenv, const char *tag)
{
	int p;

	for (p = 0; newenv[p] != '='; p++)
	{
		if (newenv[p] != tag[p])
		{
			return (0);
		}
	}

	return (p + 1);
}
/**
 * get_env_var - Obtain an env var.
 * @tag: Name of the ENV VAR
 * @environ_var: ENV VAR
 * Return: Worth of the env var if located.
 * Else, fetch NULL.
 */
char *get_env_var(const char *tag, char **environ_var)
{
	char *ptr_env;
	int n, mov;

	ptr_env = NULL;
	mov = 0;

	for (n = 0; environ_var[n]; n++)
	{
		mov = comp_env_names(environ_var[n], tag);
		if (mov)
		{
			ptr_env = environ_var[n];
			break;
		}
	}

	return (ptr_env + mov);
}


/**
 * checkInt_inString - initialise if the string passed is a number.
 * @s: enter string
 * Return: fetch 1 if string is a number else fetch 0.
 */
int checkInt_inString(const char *s)
{
unsigned int u;

u = 0;
while (s[u])
{
if (s[u] < 48 || s[u] > 57)
return (0);
u++;
}
return (1);
}

/**
 * Rev_String - overturn a stribg.
 * @s: enter string.
 * Return: do not fetch.
 */
void Rev_String(char *s)
{
int count = 0, a, b;
char *string, x;

for (count = 0; s[count] != '\0'; count++)
{
string = s;
}

a = 0;
while (a < count - 1)
{
b = a + 1;
while (b > 0)
{
x = *(string + b);
*(string + b) = *(string + (b - 1));
*(string + (b - 1)) = x;
b--;
}
a++;
}
}
