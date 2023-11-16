#include "verma.h"

/**
 * copy_s - copies infor betwixt void pointers.
 * @newptr:the destination pointer.
 * @ptr: the source pointer.
 * @size: the size of new pointer.
 * Return: no return.
 */

void copy_s(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int r;

	for (r = 0; r < size; r++)
		char_newptr[r] = char_ptr[r];
}
/**
 * prrealloc - reallocates the memory block.
 * @ptr: pointer to the memory allocated previously
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *prrealloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		copy_s(newptr, ptr, new_size);
	else
		copy_s(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}




/**
 * del_COMMENT - deletes comments from the enter
 * @in: enter string
 * Return: enter without comments
 */
char *del_COMMENT(char *in)
{
	int u, u_to;

	u_to = 0;
	for (u = 0; in[u]; u++)
	{
		if (in[u] == '#')
		{
			if (u == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[u - 1] == ' ' || in[u - 1] == '\t' || in[u - 1] == ';')
				u_to = u;
		}
	}

	if (u_to != 0)
	{
		in = prrealloc(in, u, u_to + 1);
		in[u_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shell
 * @dish: data relevant (av, enter, argz)
 * Return: no return.
 */
void shell_loop(verma_shell *dish)
{
int loop, iff;
char *enter;

for (loop = 1; loop == 1;)
{
write(STDIN_FILENO, "^-^ ", 4);
enter = READrule(&iff);
if (iff != -1)
{
enter = del_COMMENT(enter);
if (enter == NULL)
continue;

if (case_intfunc(dish, enter) == 1)
{
dish->state = 2;
free(enter);
continue;
}
enter = replace_variable(enter, dish);
loop = split(dish, enter);
dish->count += 1;
free(enter);
}
else
{
loop = 0;
free(enter);
}
}
}

/**
 * prmalloc - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory allocated previously.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **prmalloc(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int r;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (r = 0; r < old_size; r++)
		newptr[r] = ptr[r];

	free(ptr);

	return (newptr);
}

