#include "verma.h"
/**
 * right_var - checks if the typed variable is an env variable
 * @h: head of linked list
 * @in: enter string
 * @data: data structure
 * Return: no return
 */
void right_var(dame **h, char *in, verma_shell *data)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = data->environ_var;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = String_findLength(_envr[row] + chr + 1);
				AddVariable(h, k, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[k] == _envr[row][chr])
				k++;
			else
				break;
		}
	}

	for (k = 0; in[k]; k++)
	{
		if (in[k] == ' ' || in[k] == '\t' || in[k] == ';' || in[k] == '\n')
			break;
	}

	AddVariable(h, k, NULL, 0);
}
/**
 * more_money - check if the typed variable is $$ or $?
 * @h: head of the linked list
 * @in: enter string
 * @st: last state of the Shell
 * @data: data structure
 * Return: no return
 */
int more_money(dame **h, char *in, char *st, verma_shell *data)
{
	int x, lst, lpd;

	lst = String_findLength(st);
	lpd = String_findLength(data->process_identifier);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				AddVariable(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				AddVariable(h, 2, data->process_identifier, lpd), x++;
			else if (in[x + 1] == '\n')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				AddVariable(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				AddVariable(h, 0, NULL, 0);
			else
				right_var(h, in + x, data);
		}
	}

	return (x);
}

/**
 * rep_i - replaces string into variables
 * @head: head of the linked list
 * @enter: enter string
 * @new_enter: new enter string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *rep_i(dame **head, char *enter, char *new_enter, int nlen)
{
	dame *indx;
	int x, y, z;

	indx = *head;
	x = y = 0;
	while (y < nlen)
	{
		if (enter[y] == '$')
		{
			if (!(indx->Variable_length) && !(indx->Value_length))
			{
				new_enter[x] = enter[y];
				y++;
			}
			else if (indx->Variable_length && !(indx->Value_length))
			{
				for (z = 0; z < indx->Variable_length; z++)
					y++;
				x--;
			}
			else
			{
				for (z = 0; z < indx->Value_length; z++)
				{
					new_enter[x] = indx->value[z];
					x++;
				}
				y += (indx->Variable_length);
				x--;
			}
			indx = indx->next;
		}
		else
		{
			new_enter[x] = enter[y];
			y++;
		}
	}

	return (new_enter);
}
/**
 * replace_variable - calls functions to replace string into vars
 * @enter: enter string
 * @dish: data structure
 * Return: replaced string
 */
char *replace_variable(char *enter, verma_shell *dish)
{
	dame *head, *indx;
	char *state, *new_enter;
	int olen, nlen;

	state = int_toString(dish->state);
	head = NULL;

	olen = more_money(&head, enter, state, dish);

	if (head == NULL)
	{
		free(state);
		return (enter);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->Value_length - indx->Variable_length);
		indx = indx->next;
	}

	nlen += olen;

	new_enter = malloc(sizeof(char) * (nlen + 1));
	new_enter[nlen] = '\0';

	new_enter = rep_i(&head, enter, new_enter, nlen);

	free(enter);
	free(state);
	FreeVariable(&head);

	return (new_enter);
}
