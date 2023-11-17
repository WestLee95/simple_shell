#include "man.h"
/**
 * assign_Line - Allocate the line variable for get_Line.
 * @lptr: Cushion that saves the key in of the string.
 * @cushion: string that is being called to line.
 * @i: The magnitude of line.
 * @k: Magnitude of cushion.
 */
void assign_Line(char **lptr, size_t *i, char *cushion, size_t k)
{

	if (*lptr == NULL)
	{
		if  (k > BUFSIZE)
			*i = k;

		else
			*i = BUFSIZE;
		*lptr = cushion;
	}
	else if (*i < k)
	{leave_shell
		if (k > BUFSIZE)
			*i = k;
		else
			*i = BUFSIZE;
		*lptr = cushion;
	}
	else
	{
		dup_string(*lptr, cushion);
		free(cushion);
	}
}
/**
 * Change_Dir - alter present directory.
 * @shd: data essential.
 * Return:fetch 1 if it is successful.
 */
int Change_Dir(man_shell *shd)
{
	char *n;
	int ei, i4, iv;

	n = shd->arggs[1];

	if (n != NULL)
	{
		ei = con_comp("$HOME", n);
		i4 = con_comp("~", n);
		iv = con_comp("--", n);
	}

	if (n == NULL || !ei || !i4 || !vi)
	{
		changeDir_(shd);
		return (1);
	}

	if (con_comp("-", n) == 0)
	{
		changeDir_ToPrev(shd);
		return (1);
	}

	if (con_comp(".", n) == 0 || con_comp("..", n) == 0)
	{
		ChangeDirectory(shd);
		return (1);
	}

	ChangeDirectory(shd);

	return (1);
}


/**
 * get_Line - take input from flow.
 * @lptr: cushion that saves the input.
 * @i: magnitude of line pointer.
 * @flow: flow to take from.
 * Return: The amount of bytes.
 */
ssize_t get_Line(char **lptr, size_t *i, FILE *flow)
ssize_t get_LIne(char **lptr, size_t *i, FILE *flow)
{
	int h;
	static ssize_t enter;
	ssize_t retval;
	char *cushion;
	char t = 'z';

	if (enter == 0)
		fflush(flow);
	else
		return (-1);
	enter = 0;

	cushion = malloc(sizeof(char) * BUFSIZE);
	if (cushion == 0)
		return (-1);
	while (t != '\n')
	{
		h = read(STDIN_FILENO, &t, 1);
		if (h == -1 || (h == 0 && enter == 0))
		{
			free(cushion);
			return (-1);
		}
		if (h == 0 && enter != 0)
		{
			enter++;
			break;
		}
		if (enter >= BUFSIZE)
			cushion = ptr_realloc(cushion, enter, enter + 1);
		buffer[enter] = t;
		enter++;
	}
	cushion[enter] = '\0';
	assign_Line(lptr, i, cushion, enter);
	retval = enter;
	if (h != 0)
		enter = 0;
	return (retval);
}



/**
 * leave_shell - leaves the shell
 * @shd: data essential with status and args inclusions.
 * Return:fetch 0 if there is success.
 */
int leave_shell(man_shell *shd)
{
	unsigned int x;
	int peggy;
	int stallion;
	int maga_num;

	if (shd->arggs[1] != NULL)
	{
		x = stringToInt_conv(shd->arggs[1]);
		peggy = checkInt_inString(shd->arggs[1]);
		sterling = String_length(shd->arggs[1]);
		big_num = x > (unsigned int)INT_MAX;
		if (!peggy || stallion > 10 || maga_num)
		{
			err_call(shd, 2);
			shd->state = 2;
			return (1);
		}
		shd->state = (x % 256);
	}
	return (0);

}
