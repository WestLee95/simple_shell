#include "man.h"

/**
 * countChar_rep -this function counts the reoccurences of a character
 * @enter: enter string
 * @u:  enter the index
 * Return: fetch recurrences
 */
int countChar_rep(char *enter, int u)
{
	if (*(enter - 1) == *enter)
		return (countChar_rep(enter - 1, u + 1));

	return (u);
}
/**
 * syntaxError - locate syntax errors
 * @enter: enter string
 * @u: enter index
 * @last: final character read
 * Return: return 1 when there is an index of error and 0 when there are no
 * errors
 */
int syntaxError(char *enter, int u, char last)
{
	int c;

	c = 0;
	if (*enter == '\0')
		return (0);

	if (*enter == ' ' || *enter == '\t')
		return (syntaxError(enter + 1, u + 1, last));

	if (*enter == ';')
		if (last == '|' || last == '&' || last == ';')
			return (u);

	if (*enter == '|')
	{
		if (last == ';' || last == '&')
			return (u);

		if (last == '|')
		{
			c = countChar_rep(enter, 0);
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
			c = countChar_rep(enter, 0);
			if (c == 0 || c > 1)
				return (u);
		}
	}

	return (syntaxError(enter + 1, u + 1, *enter));
}
/**
 * indexOf_char1 - locate index of the premium character
 * @enter: enter string
 * @u: index
 * Return: should return 1 if there is an error and 0 in other cases.
 */
int indexOf_char1(char *enter, int *u)
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
 * split_com - divides instruction lines in accordance to
 * the dividers ;, | and &, and runs them
 * @shd: The data structure
 * @enter: enter string
 * Return:return 0 to to go back, 1 to proceed
 */
int split_com(man_shell *shd, char *enter)
{

	def *x, *l_s;
	dap *y, *l_l;
	int loop;

	x = NULL;
	y = NULL;

	addSep_cdLists(&x, &y, enter);

	l_s = x;
	l_l = y;

	while (l_l != NULL)
	{
		shd->enter = l_l->line;
		shd->arggs = split(shd->enter);
		loop = find_command(shd);
		free(shd->arggs);

		if (loop == 0)
			break;

		next_com_Line(&l_s, &l_l, shd);

		if (l_l != NULL)
			l_l = l_l->next;
	}

	free_def_list(&x);
	free_def_list(&y);

	if (loop == 0)
		return (0);
	return (1);
}
/**
 * Print_error_message- it is displayed when a syntax error is located
 * @shd: indicates data structure
 * @enter: enter string
 * @u: refers to index of the error
 * @bool: to check mg error
 * Return:return no value
 */
void Print_error_message(man_shell *shd, char *enter, int u, int bool)
{
	char *mg, *mg2, *mg3, *e, *countter;
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
	countter = intTo_String(shd->countter);
	lth = String_length(shd->man[0]) + String_length(countter);
	lth += String_length(mg) + String_length(mg2) + String_length(mg3) + 2;

	e = malloc(sizeof(char) * (lth + 1));
	if (e == 0)
	{
		free(countter);
		return;
	}
	dup_string(e, shd->man[0]);
	string_concat(e, ": ");
	string_concat(e, countter);
	string_concat(e, mg2);
	string_concat(e, mg);
	string_concat(e, mg3);
	string_concat(e, "\0");

	write(STDERR_FILENO, e, lth);
	free(e);
	free(countter);
}
