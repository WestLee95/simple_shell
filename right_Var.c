#include "man.h"

/**
 * swap_non_printed_char - switch & and | for unprinted characters.
 * @enter: enter string.
 * @bool: kind of swtch.
 * Return: fetch switched string.
 */
char *swap_non_printed_char(char *enter, int bool)
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
 * addSep_cdLists - sum dividers and command lines in the lists.
 * @hs: head of divider list.
 * @hl: head of command lines list.
 * @enter: enter string.
 * Return:do not fetch
 */
void addSep_cdLists(def **hs, dap **hl, char *enter)
{
	int u;
	char *line;

	enter = swap_non_printed_char(enter, 0);

	for (u = 0; enter[u]; u++)
	{
		if (enter[u] == ';')
			add_def_node(hs, enter[u]);

		if (enter[u] == '|' || enter[u] == '&')
		{
			add_def_node(hs, enter[u]);
			u++;
		}
	}

	line = string_split(enter, ";|&");
	do {
		line = swap_non_printed_char(line, 1);
		end_dap_node(hl, line);
		line = string_split(NULL, ";|&");
	} while (line != NULL);

}
/**
 * next_com_Line - move to the immediate command line saved.
 * @l_s: divider list.
 * @l_l: command line list.
 * @shd: data framework.
 * Return: do not fetch.
 */
void next_com_Line(def **l_s, dap **l_l, man_shell *shd)
{
	int loop_sep;
	def *ls_s;
	dap *ls_l;

	loop_sep = 1;
	ls_s = *l_s;
	ls_l = *l_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shd->state == 0)
		{
			if (ls_s->divider == '&' || ls_s->divider == ';')
				loop_sep = 0;
			if (ls_s->divider == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->divider == '|' || ls_s->divider == ';')
				loop_sep = 0;
			if (ls_s->divider == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*l_s = ls_s;
	*l_l = ls_l;
}


/**
 * **split - represents the key in of string.
 * @enter: enter string.
 * Return: fetch string divided.
 */
char **split(char *enter)
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

	token = string_split(enter, TOK_DELIM);
	tokens[0] = token;

	for (u = 1; token != NULL; u++)
	{
		if (u == bs)
		{
			bs += TOK_BUFSIZE;
			tokens = pr_malloc(tokens, u, sizeof(char *) * bs);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = string_split(NULL, TOK_DELIM);
		tokens[u] = token;
	}

	return (tokens);
}
