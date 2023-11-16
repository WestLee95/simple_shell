#include "verma.h"

/**
 * add_rvar_node - adds up a variable
 * at the end of a dame list.
 * @head: head of linked list.
 * @lvar: the length of variable.
 * @val: the value of variable.
 * @lval:the length of value.
 * Return: the address of the head.
 */
dame *AddVariable(dame **head, int lvar, char *val, int lval)
{
	dame *fresh, *x;

	fresh = malloc(sizeof(dame));
	if (fresh == NULL)
		return (NULL);

	fresh->Variable_length = lvar;
	fresh->val = value;
	fresh->Value_length = lval;

	fresh->next = NULL;
	x = *head;

	if (x == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (x->next != NULL)
			x = x->next;
		x->next = fresh;
	}

	return (*head);
}

/**
 * FreeVariable - frees up a dame list
 * @head: head of linked list.
 * Return: no return.
 */
void FreeVariable(dame **head)
{
	dame *x;
	dame *curl;

	if (head != NULL)
	{
		curl = *head;
		while ((x = curl) != NULL)
		{
			curl = curl->next;
			free(x);
		}
		*head = NULL;
	}
}

/**
 * info_PathError - the error info for env in get_env.
 * @dish: data relevant (count, arguments)
 * Return: an error senh_fend_message.
 */


char *info_PathError(verma_shell *dish)
{
	int lathum;
	char *h_f;
	char *p;

	h_f = int_toString(dish->count);
	lathum = String_findLength(dish->verma[0]) + String_findLength(h_f);
	lathum += String_findLength(dish->argz[0]) + 24;
	o = malloc(sizeof(char) * (lathum + 1));
	if (o == 0)
	{
		free(o);
		free(h_f);
		return (NULL);
	}
	concpy(o, dish->verma[0]);
	concat(o, ": ");
	concat(o, h_f);
	concat(o, ": ");
	concat(o, dish->argz[0]);
	concat(o, ": insufficient permission\n");
	concat(o, "\0");
	free(h_f);
	return (o);
}
/**
 * info_About_error - error info for path and failure denied permission.
 * @dish: data relevant (count, arguments).
 * Return: error string.
 */

char *info_About_error(verma_shell *dish)
{
	int lathum;
	char *p;
	char *h_f;
	char *send_message;

	h_f = int_toString(dish->count);
	send_message = ": Cannot add or Remove environment\n";
	lathum = String_findLength(dish->verma[0]) + String_findLength(h_f);
	lathum += String_findLength(dish->argz[0]) + String_findLength(send_message) + 4;
	p = malloc(sizeof(char) * (lathum + 1));
	if (p == 0)
	{
		free(p);
		free(h_f);
		return (NULL);
	}

	concpy(p, dish->verma[0]);
	concat(p, ": ");
	concat(p, h_f);
	concat(p, ": ");
	concat(p, dish->argz[0]);
	concat(p, send_send_message);
	concat(p, "\0");
	free(h_f);

	return (p);
}


