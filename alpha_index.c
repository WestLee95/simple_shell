#include "verma.h"

/**
 * count_repchar - counts the repetitions of a char
 * @enter: enter string
 * @u: the index
 * Return: repetitions
 */
int count_repchar(char *enter, int u)
{
	if (*(enter - 1) == *enter)
		return (count_repchar(enter - 1, u + 1));

	return (u);
}
/**
 * syntax_err - finds syntax errors
 * @enter: enter string
 * @u: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int syntax_err(char *enter, int u, char last)
{
	int c;

	c = 0;
	if (*enter == '\0')
		return (0);

	if (*enter == ' ' || *enter == '\t')
		return (syntax_err(enter + 1, u + 1, last));

	if (*enter == ';')
		if (last == '|' || last == '&' || last == ';')
			return (u);

	if (*enter == '|')
	{
		if (last == ';' || last == '&')
			return (u);

		if (last == '|')
		{
			c = count_repchar(enter, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	if (*enter == '&')
	{
		if (last == ';' || last == '|')
			return (u);

		if (last == '&')
		{
			c = count_repchar(enter, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	return (syntax_err(enter + 1, u + 1, *enter));
}
/**
 * index_char - finds index of the first char
 * @enter: enter string
 * @u: index
 * Return: 1 if there is an error. 0 in other case.
 */
int index_char(char *enter, int *u)
{
	for (*u = 0; enter[*u]; *u += 1)
	{
		if (enter[*u] == ' ' || enter[*u] == '\t')
			continue;

		if (enter[*u] == ';' || enter[*u] == '|' || enter[*u] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * split - splits command rules according to
 * the divides ;, | and &, and executes them
 * @dish: data structure
 * @enter: enter string
 * Return: 0 to exit, 1 to continue
 */
int split(verma_shell *dish, char *enter)
{

	def *x, *l_s;
	dap *y, *l_l;
	int loop;

	x = NULL;
	y = NULL;

	adddivides_and_cdLists(&x, &y, enter);

	l_s = x;
	l_l = y;

	while (l_l != NULL)
	{
		dish->enter = l_l->rule;
		dish->argz = splityy(dish->enter);
		loop = kano(dish);
		free(dish->argz);

		if (loop == 0)
			break;

		nextInrule(&l_s, &l_l, dish);

		if (l_l != NULL)
			l_l = l_l->next;
	}

	fee_list(&x);
	free_list(&y);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * error_send_send_message- prints when a syntax error is found
 * @dish: data structure
 * @enter: enter string
 * @u: index of the error
 * @bool: to control mg error
 * Return: no return
 */
void error_send_message(verma_shell *dish, char *enter, int u, int bool)
{
	char *mg, *mg2, *mg3, *e, *count;
	int lth;

	if (enter[u] == ';')
	{
		if (bool == 0)
			mg = (enter[u + 1] == ';' ? ";;" : ";");
		else
			mg = (enter[u - 1] == ';' ? ";;" : ";");
	}

	if (enter[u] == '|')
		mg = (enter[u + 1] == '|' ? "||" : "|");

	if (enter[u] == '&')
		mg = (enter[u + 1] == '&' ? "&&" : "&");

	mg2 = ": Syntax error: \"";
	mg3 = "\" unexpected\n";
	count = int_toString(dish->count);
	lth = String_findLength(dish->verma[0]) + String_findLength(count);
	lth += String_findLength(mg) + String_findLength(mg2) + String_findLength(mg3) + 2;

	e = malloc(sizeof(char) * (lth + 1));
	if (e == 0)
	{
		free(count);
		return;
	}
	concpy(e, dish->verma[0]);
	concat(e, ": ");
	concat(e, count);
	concat(e, mg2);
	concat(e, mg);
	concat(e, mg3);
	concat(e, "\0");

	write(STDERR_FILENO, e, lth);
	free(e);
	free(count);
}
