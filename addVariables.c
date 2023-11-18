#include "man.h"

/**
 * addVar -this should Append a variable to the latter of a given list.
 * @init: This indicates the premium  element of a linked list.
 * @lvar:This indicates the actual size of the variable.
 * @Vall:  should hold The variable's value.
 * @lval: should hold The size or length of the value.
 * Return: return the location of the head.
 */
dame *addVar(dame **init, int lvar, char *Vall, int lval)
{
	dame *crisp, *b;

	crisp = malloc(sizeof(dame));
	if (crisp == NULL)
		return (NULL);

	crisp->Variable_length = lvar;
	crisp->Vall = Vall;
	crisp->Value_length = lval;

	crisp->next = NULL;
	b = *init;

	if (b == NULL)
	{
		*init = crisp;
	}
	else
	{
		while (b->next != NULL)
			b = b->next;
		b->next = crisp;
	}

	return (*init);
}

/**
 * freeVar - it release the materials allocated by the given list.
 * @init: The starting of a linked list.
 * Return:should not return any output or result.
 */
void freeVar(dame **init)
{
	dame *f;
	dame *coil;

	if (init != NULL)
	{
		coil = *init;
		while ((f = coil) != NULL)
		{
			coil = coil->next;
			free(f);
		}
		*init = NULL;
	}
}

/**
 *  display_path_error- Error data related to the
 *  surrounding variable in get_env_Var.
 * @shd: important data, as well as counters and arguments.
 * Return: A notice showing that there's an error.
 */


char *display_path_error(man_shell *shd)
{
	int lathum;
	char *d_s;
	char *o;

	d_s = intTo_String(shd->countter);
	lathum = String_length(shd->man[0]) + String_length(d_s);
	lathum += String_length(shd->arggs[0]) + 24;
	o = malloc(sizeof(char) * (lathum + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}
	dup_string(o, shd->man[0]);
	string_concat(o, ": ");
	string_concat(o, d_s);
	string_concat(o, ": ");
	string_concat(o, shd->arggs[0]);
	string_concat(o, ": insufficient permission\n");
	string_concat(o, "\0");
	free(d_s);
	return (o);
}

/**
 * disp_error_info - Error data in  relation
 * to route and permission denial failure..
 * @shd: important  data, with counters and arguments also.
 * Return: String with an error output.
 */

char *disp_error_info(man_shell *shd)
{
	int lathum;
	char *o;
	char *d_s;
	char *memo;

	d_s = intTo_String(shd->countter);
	memo = ": Cannot add or Remove environment\n";
	lathum = String_length(shd->man[0]) + String_length(d_s);
	lathum += String_length(shd->arggs[0]) + String_length(memo) + 4;
	o = malloc(sizeof(char) * (lathum + 1));
	if (o == 0)
	{
		free(o);
		free(d_s);
		return (NULL);
	}

	dup_string(o, shd->man[0]);
	string_concat(o, ": ");
	string_concat(o, d_s);
	string_concat(o, ": ");
	string_concat(o, shd->arggs[0]);
	string_concat(o, memo);
	string_concat(o, "\0");
	free(d_s);

	return (o);
}


