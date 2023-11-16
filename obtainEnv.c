#include "verma.h"

/**
 * print_env - prints the evironment variables
 * @dish: data relevant.
 * Return: 1 on success.
 */
int print_env(verma_shell *dish)
{
	int g, h;

	for (g = 0; dish->environ_var[g]; g++)
	{

		for (h = 0; dish->environ_var[g][h]; h++)
			;

		write(STDOUT_FILENO, dish->environ_var[g], h);
		write(STDOUT_FILENO, "\n", 1);
	}
	dish->state = 0;

	return (1);
}
/**
 * compare_envnames - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @identity: name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int compare_envnames(const char *nenv, const char *identity)
{
	int m;

	for (m = 0; nenv[m] != '='; m++)
	{
		if (nenv[m] != identity[m])
		{
			return (0);
		}
	}

	return (m + 1);
}
/**
 * obtainenv - get an environment variable
 * @identity: identity of the environment variable
 * @environ_var: environment variable
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *obtainenv(const char *identity, char **environ_var)
{
	char *ptr_env;
	int n, mov;

	ptr_env = NULL;
	mov = 0;

	for (n = 0; environ_var[n]; n++)
	{
		mov = compare_envnames(environ_var[n], identity);
		if (mov)
		{
			ptr_env = environ_var[n];
			break;
		}
	}

	return (ptr_env + mov);
}


/**
 * examine_if_int - defines if string passed is a number
 * @s: enter string
 * Return: 1 if string is a number. 0 in other case.
 */
int examine_if_int(const char *s)
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
 * AssistString - reverses a stribg.
 * @s: enter string.
 * Return: no return.
 */
void AssistString(char *s)
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
