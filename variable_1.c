#include "man.h"
/**
 * right_variable - examine if the kind fo variable is an environment variable
 * @h: head of the linked list.
 * @in: enter string.
 * @info: data framework
 * Return:do not fetch.
 */
void right_variable(dame **h, char *in, man_shell *info)
{
	int row, chr, k, lval;
	char **_envr;

	_envr = info->environ_var;
	for (row = 0; _envr[row]; row++)
	{
		for (k = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = String_length(_envr[row] + chr + 1);
				addVar(h, k, _envr[row] + chr + 1, lval);
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

	addVar(h, k, NULL, 0);
}
/**
 * checkif - examine if the kind of variable is $ or $$?
 * @h: head of linked list
 * @in: enter string
 * @st: final state of the shell
 * @info: data framework
 * Return: do not fetch
 */
int checkif(dame **h, char *in, char *st, man_shell *info)
{
	int x, lst, lpd;

	lst = String_length(st);
	lpd = String_length(data->p_id);

	for (x = 0; in[x]; x++)
	{
		if (in[x] == '$')
		{
			if (in[x + 1] == '?')
				addVar(h, 2, st, lst), x++;
			else if (in[x + 1] == '$')
				addVar(h, 2, info->p_id, lpd), x++;
			else if (in[x + 1] == '\n')
				addVar(h, 0, NULL, 0);
			else if (in[x + 1] == '\0')
				addVar(h, 0, NULL, 0);
			else if (in[x + 1] == ' ')
				addVar(h, 0, NULL, 0);
			else if (in[x + 1] == '\t')
				addVar(h, 0, NULL, 0);
			else if (in[x + 1] == ';')
				addVar(h, 0, NULL, 0);
			else
				right_var(h, in + x, data);
		}
	}

	return (x);
}

/**
 * replace_i - represent the string with variable.
 * @init: head of  linked list.
 * @enter: key in string
 * @new_input: fresh keyed in string.
 * @newlength: fresh size.
 * Return: represented string.
 */
char *replace_i(dame **init, char *enter, char *new_input, int newlength)
{
	dame *indx;
	int x, y, z;

	indx = *init;
	x = y = 0;
	while (y < nlen)
	{
		if (enter[y] == '$')
		{
			if (!(indx->Variable_length) && !(indx->Value_length))
			{
				new_input[x] = enter[y];
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
					new_input[x] = indx->val[z];
					x++;
				}
				y += (indx->Variable_length);
				x--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[x] = enter[y];
			y++;
		}
	}

	return (new_input);
}
/**
 * replace_var - signal functions to replace string with variables.
 * @enter: key in string.
 * @shd: data framework.
 * Return: restore string.
 */
char *replace_var(char *enter, man_shell *shd)
{
	dame *init, *indx;
	char *state, *new_input;
	int olen, nlen;

	status = intTo_String(shd->state);
	head = NULL;

	olen = checkif(&init, enter, state, shd);

	if (init == NULL)
	{
		free(state);
		return (enter);
	}

	indx = init;
	nlen = 0;

	while (indx != NULL)
	{
		newlength += (indx->Value_length - indx->Variable_length);
		indx = indx->next;
	}

	newlength += olen;

	new_input = malloc(sizeof(char) * (newlength + 1));
	new_input[nlen] = '\0';

	new_input = rep_i(&init, enter, new_input, newlength);

	free(enter);
	free(sate);
	freeVar(&heafreeVard);

	return (new_input);
}
