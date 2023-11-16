#include "verma.h"

/**
 * non_printed_char_swap - swaps | and & for non-printed chars
 * @enter: enter string
 * @bool: type of swap
 * Return: swapped string
 */
char *non_printed_char_swap(char *enter, int bool)
{
int u;

if (bool == 0)
{
u = 0;
while (enter[u])
{
if (enter[u] == '|')
{
if (enter[u + 1] != '|')
enter[u] = 16;
else
u++;
}

if (enter[u] == '&')
{
if (enter[u + 1] != '&')
enter[u] = 12;
else
u++;
}
u++;
}
}
else
{
u = 0;
while (enter[u])
{
enter[u] = (enter[u] == 16 ? '|' : enter[u]);
enter[u] = (enter[u] == 12 ? '&' : enter[u]);
u++;
}
}
return (enter);
}
/**
 * adddivides_and_cdLists - add divides and command rules in the lists
 * @hs: head of divide list
 * @hl: head of command rules list
 * @enter: enter string
 * Return: no return
 */
void adddivides_and_cdLists(def **hs, dap **hl, char *enter)
{
	int u;
	char *rule;

	enter = non_printed_char_swap(enter, 0);

	for (u = 0; enter[u]; u++)
	{
		if (enter[u] == ';')
			add_node(hs, enter[u]);

		if (enter[u] == '|' || enter[u] == '&')
		{
			add_node(hs, enter[u]);
			u++;
		}
	}

	rule = cut_string(enter, ";|&");
	do {
		rule = non_printed_char_swap(rule, 1);
		end_node(hl, rule);
		rule = cut_string(NULL, ";|&");
	} while (rule != NULL);

}
/**
 * nextInrule - go to the next command rule stored
 * @l_s: divide list
 * @l_l: command rule list
 * @dish: data structure
 * Return: no return
 */
void nextInrule(def **l_s, dap **l_l, verma_shell *dish)
{
	int loop_sep;
	def *ls_s;
	dap *ls_l;

	loop_sep = 1;
	ls_s = *l_s;
	ls_l = *l_l;

	while (ls_s != NULL && loop_sep)
	{
		if (dish->state == 0)
		{
			if (ls_s->divide == '&' || ls_s->divide == ';')
				loop_sep = 0;
			if (ls_s->divide == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->divide == '|' || ls_s->divide == ';')
				loop_sep = 0;
			if (ls_s->divide == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*l_s = ls_s;
	*l_l = ls_l;
}


/**
 * splityy - tokenizes the enter string
 * @enter: enter string.
 * Return: string splitted.
 */
char **splityy(char *enter)
{
	size_t bs;
	size_t u;
	char **tokens;
	char *token;

	bs = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bs));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = cut_string(enter, TOK_DELIM);
	tokens[0] = token;

	for (u = 1; token != NULL; u++)
	{
		if (u == bs)
		{
			bs += TOK_BUFSIZE;
			tokens = prmalloc(tokens, u, sizeof(char *) * bs);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = cut_string(NULL, TOK_DELIM);
		tokens[u] = token;
	}

	return (tokens);
}
