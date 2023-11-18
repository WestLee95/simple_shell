#include "man.h"

/**
 * free_def_list - releases the definition list.
 * @upper: top of the linked list.
 * Return: do not fecth
 */
void free_def_list(def **upper)
{
def *b;
def *def;

if (upper != NULL)
{
def = *upper;
while (def != NULL)
{
b = def;
def = def->next;
free(b);
}
*upper = NULL;
}
}

/**
 * free_dap_list -releases a dap list
 * @upper: top of the linked lists.
 * Return:do not fetch.
 */
void free_dap_list(dap **upper)
{
dap *b;
dap *def;

if (upper != NULL)
{
def = *upper;
while (def != NULL)
{
b = def;
def = def->next;
free(b);
}
*upper = NULL;
}
}

/**
 * end_dap_node - sum up a command line
 * at the last part of a dap.
 * @upper: top of the linked lists.
 * @line: the command line.
 * Return: fetch the location of top.
 */
dap *end_dap_node(dap **upper, char *line)
{
dap *current, *b;

while (1)
{
current = malloc(sizeof(dap));
if (current == NULL)
continue;

current->line = line;
current->next = NULL;
b = *upper;

if (b == NULL)
{
*upper = current;
}
else
{
while (b->next != NULL)
b = b->next;
b->next = current;
}

return (*upper);
}
}

/**
 * add_def_node - sum up a divider seen
 * at the end of a def node.
 * @upper: top of the linked list.
 * @sep: divider located ; ,| and &.
 * Return: location of top.
 */
def *add_def_node(def **upper, char sep)
{
def *current, *b;

while (1)
{
current = malloc(sizeof(def));
if (current == NULL)
continue;

current->divider = sep;
current->next = NULL;
b = *upper;

if (b == NULL)
{
*upper = current;
}
else
{
while (b->next != NULL)
b = b->next;
b->next = current;
}

return (*upper);
}
}
