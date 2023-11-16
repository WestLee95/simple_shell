#include "verma.h"
/**
 * therule - assigns the rule var for get_rule
 * @lptr: Buffer that store the enter str
 * @buffer: str that is been called to rule
 * @i: the size of rule
 * @k: size of buffer
 */
void therule(char **lptr, size_t *i, char *buffer, size_t k)
{

	if (*lptr == NULL)
	{
		if  (k > BUFSIZE)
			*i = k;

		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else if (*i < k)
	{
		if (k > BUFSIZE)
			*i = k;
		else
			*i = BUFSIZE;
		*lptr = buffer;
	}
	else
	{
		concpy(*lptr, buffer);
		free(buffer);
	}
}
/**
 * ALT - changes current directory
 * @dish: data relevant
 * Return: 1 on success
 */
int ALT(verma_shell *dish)
{
	char *d;
	int ie, i2, ih;

	d = dish->argz[1];

	if (d != NULL)
	{
		ie = concomp("$HOME", d);
		i2 = concomp("~", d);
		ih = concomp("--", d);
	}

	if (d == NULL || !ie || !i2 || !ih)
	{
		alterDir_(dish);
		return (1);
	}

	if (concomp("-", d) == 0)
	{
		alterDir_prev(dish);
		return (1);
	}

	if (concomp(".", d) == 0 || concomp("..", d) == 0)
	{
		Change_Dir(dish);
		return (1);
	}

	Change_Dir(dish);

	return (1);
}


/**
 * gettherule - Read inpt from stream
 * @lptr: buffer that stores the enter
 * @i: size of ruleptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t gettherule(char **lptr, size_t *i, FILE *stream)
{
	int n;
	static ssize_t enter;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (enter == 0)
		fflush(stream);
	else
		return (-1);
	enter = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		n = read(STDIN_FILENO, &t, 1);
		if (n == -1 || (n == 0 && enter == 0))
		{
			free(buffer);
			return (-1);
		}
		if (n == 0 && enter != 0)
		{
			enter++;
			break;
		}
		if (enter >= BUFSIZE)
			buffer = prrealloc(buffer, enter, enter + 1);
		buffer[enter] = t;
		enter++;
	}
	buffer[enter] = '\0';
	therule(lptr, i, buffer, enter);
	retval = enter;
	if (n != 0)
		enter = 0;
	return (retval);
}



/**
 * lefshell - exits the shell
 * @dish: data relevant (state and argz)
 * Return: 0 on success.
 */
int lefshell(verma_shell *dish)
{
	unsigned int x;
	int jiggy;
	int sterling;
	int big_num;

	if (dish->argz[1] != NULL)
	{
		x = string_toInt(dish->argz[1]);
		jiggy = examine_if_int(dish->argz[1]);
		sterling = String_findLength(dish->argz[1]);
		big_num = x > (unsigned int)INT_MAX;
		if (!jiggy || sterling > 10 || big_num)
		{
			G_ERROR(dish, 2);
			dish->state = 2;
			return (1);
		}
		dish->state = (x % 256);
	}
	return (0);

}
