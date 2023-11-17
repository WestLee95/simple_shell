#include "man.h"

/**
 * copy_info_s - duplicates  information of  betwixt void reference.
 * @newpointer:the home pointer.
 * @pointer: the origin pointer.
 * @size: the size of fresh pointer.
 * Return: no return.
 */

void copy_info_s(void *newpointer, const void *pointer, unsigned int size)
{
	char *char_ptr = (char *)pointer;
	char *char_newptr = (char *)newpointer;
	unsigned int r;

	for (r = 0; r < size; r++)
		char_newptr[r] = char_ptr[r];
}
/**
 * ptr_realloc - reassigns the memory unit.
 * @pointer: pointer to the memory assigned initially
 * @old_size: size, in bytes, of the assigned space of pointerr.
 * @new_size: new size, in bytes, of the new memory block.
 * Return:fetch pointer.
 * if new_size == old_size, fetches pointer unchanged.
 * if memory allocation fails, fetch NULL.
 */
void *ptr_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	void *newpointer;

	if (pointer == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(pointer);
		return (NULL);
	}

	if (new_size == old_size)
		return (pointer);

	newpointer = malloc(new_size);
	if (newpointer == NULL)
		return (NULL);

	if (new_size < old_size)
		copy_info_s(newpointer, pointer, new_size);
	else
		copy_info_s(newpointer, pointer, old_size);

	free(pointer);
	return (newpointer);
}




/**
 * del_com - removes comments from the key in
 * @in: enter string
 * Return: enter with no comments
 */
char *del_com(char *in)
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
		in = ptr_realloc(in, u, u_to + 1);
		in[u_to] = '\0';
	}

	return (in);
}

/**
 * loop_shell - funtion for Loop of shell
 * @shd: data relevant (av, enter, args)
 * Return: no return.
 */
void loop_shell(man_shell *shd)
{
int loop, iff;
char *enter;

for (loop = 1; loop == 1;)
{
write(STDIN_FILENO, "^-^ ", 4);
enter = READ_LINE(&iff);
if (iff != -1)
{
enter = del_com(enter);
if (enter == NULL)
continue;

if (interm_func(dsh, enter) == 1)
{
shd->state = 2;
free(enter);
continue;
}
enter = replace_var(enter, shd);
loop = split_com(shd, enter);
shd->countter += 1;
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
 * pr_malloc - reassign a memory unit of a double pointer.
 * @pointer: double pointer to the memory assigned initially.
 * @old_size: size, in bytes, of the assigned room of poinetr.
 * @new_size: new size, in bytes, of the fresh memory unit.
 * Return: fetch pointer.
 * if new_size == old_size, fetch pointer with no alterations.
 * if memory allocation fails, fetch NULL.
 */
char **pr_malloc(char **pointer, unsigned int old_size, unsigned int new_size)
{
	char **newpointer;
	unsigned int r;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newpointer = malloc(sizeof(char *) * new_size);
	if (newpointer == NULL)
		return (NULL);

	for (r = 0; r < old_size; r++)
		newpointer[r] = pointer[r];

	free(pointer);

	return (newpointer);
}

