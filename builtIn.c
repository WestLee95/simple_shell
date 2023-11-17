#include "man.h"

/**
 * builtINFunctions -A built-in function that proceeds the directive inside the argument.
 * @cmd: Directive
 * Return: reference to the function of the built-in directive.
 */
int (*builtINFunctions(char *cmd))(man_shell *)
{
	builtin_t builtIN[] = {
		{ "env", print_env },
		{ "exit", lefshell },
		{ "setenv", compa_env_names },
		{ "unsetenv", del_env },
		{ "cd", CD },
		{ "help", HELP },
		{ NULL, NULL }
	};
	int l;

	for (l = 0; builtIN[l].name; l++)
	{
		while (concomp(builtIN[l].name, cmd) == 0)
			break;
	}

	return (builtIN[l].f);
}


/**
 * stringToInt_conv - alters a string to an integer.
 * @s: this refers to the keyed in string.
 * Return: should return an integer.
 */
int stringToInt_conv(char *s)
{
	unsigned int total_sum = 0, size = 0, oi = 0, pn = 1, m = 1, r;

	while (*(s + total_sum) != '\0')
	{
		if (size > 0 && (*(s + total_sum) < '0' || *(s + total_sum) > '9'))
			break;

		if (*(s + total_sum) == '-')
			pn *= -1;

		if ((*(s + total_sum) >= '0') && (*(s + total_sum) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		total_sum++;
	}

	for (r = total_sum - size; r < total_sum; r++)
	{
		oi = oi + ((*(s + r) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}


/**
 *getLength_ofInt - fetch the length of the number.
 * @n: shows the kind int number.
 * Return: this should return the length  of the number.
 */
int getLength_ofInt(int n)
{
	unsigned int r;
	int s = 1;

	if (n < 0)
	{
		s++;
		r = n * -1;
	}
	else
	{
		r = n;
	}
	while (r > 9)
	{
		t++;
		r = r / 10;
	}

	return (s);
}

/**
 * intTo_String - function convert an  int to a string.
 * @n: shows  the type of int number
 * Return: return a String.
 */
char *intTo_String(int n)
{
	unsigned int r;
	int s = getLength_ofInt(n);
	char *cushion;

	cushion = malloc(sizeof(char) * (s + 1));
	if (cushion == 0)
		return (NULL);

	*(cushion + s) = '\0';

	if (n < 0)
	{
		r = n * -1;
		cushion[0] = '-';
	}
	else
	{
		r = n;
	}

	y--;
	do {
		*(cushion + s) = (r % 10) + '0';
		r = r / 10;
		y--;
	}
	while (x > 0)
		;
	return (cushion);
}

/**
 * interm_func - next function to
 * get and display a syntax error
 * @shd: this refers to the data structure
 * @enter: this is a keyed in string
 * Return:return  1 should there be an error otherwise 0 should be returned.
 */
int interm_func(man_shell *shd, char *enter)
{
	int c = 0;
	int f_char = 0;
	int a = 0;

	f_char = indexOf_char1(enter, &c);
	if (f_char == -1)
	{
		Print_error_message(shd, enter, c, 0);
		return (1);
	}

	i = syntaxError(enter + c, 0, *(enter + c));
	if (i != 0)
	{
		Print_error_message(shd, enter, c + a, 1);
		return (1);
	}

	return (0);
}

