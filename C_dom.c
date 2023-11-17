#include "man.h"
/**
 * dup_mem - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: the duplicated str
 */
char *dup_mem(const char *s)
{
	char *modern;
	size_t distance;

	distance = String_length(s);
	modern = malloc(sizeof(char) * (distance + 1));
	if (fresh == NULL)
		return (NULL);
	copy_info_s(modern, s, distance + 1);
	return (modern);
}
/**
 * String_length - Returns the size of a string.
 * @s: shows type char reference
 * Return: Always return 0.
 */
int String_length(const char *s)
{
	int distance;

	for (distance = 0; s[distance] != 0; distance++)
	{
	}
	return (distance);
}
/**
 * comp_char_strings - weigh out characters of strings
 * @string: enter string.
 * @miled: delimiter.
 * Return: return 1 if are equals, 0 if not.
 */
int comp_char_strings(char string[], const char *miled)
{
unsigned int u, v, w;

u = 0;
w = 0;
while (string[u])
{
v = 0;
while (miled[v])
{
if (string[u] == miled[v])
{
w++;
break;
}
v++;
}
u++;
}
if (u == w)
return (1);
return (0);
}
/**
 * string_split - divides a string by the delimiter.
 * @string: enter string.
 * @miled: delimiter.
 * Return: string divided.
 */
char *string_split(char string[], const char *miled)
{
static char *split_com, *string_end;
char *string_start;
unsigned int u, bool;

if (string != NULL)
{
if (comp_char(string, miled))
return (NULL);
split_com = string; /*save initial location*/
u = String_length(string);
string_end = &string[u]; /*save final location*/
}
string_start = split_com;
if (string_start == string_end) /*getting to the end*/
return (NULL);

for (bool = 0; *split_com; split_com++)
{
/*cutting the  loop to find the next token*/
if (split_com != string_start)
if (*split_com && *(split_com - 1) == '\0')
break;
/*represent delimiter with null char*/
for (u = 0; miled[u]; u++)
{
if (*split_com == miled[u])
{
*split = '\0';
if (split_com == string_start)
string_start++;
break;
}
}
if (bool == 0 && *split_com) /*String not equal to 	Miled*/
bool = 1;
}
if (bool == 0) /*String equivalent to Delim*/
return (NULL);
return (string_start);
}
