#include "verma.h"
/**
 * Moon - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: the duplicated str
 */
char *Moon(const char *s)
{
	char *fresh;
	size_t length;

	length = String_findLength(s);
	fresh = malloc(sizeof(char) * (length + 1));
	if (fresh == NULL)
		return (NULL);
	copy_s(fresh, s, length + 1);
	return (fresh);
}
/**
 * String_findLength - Returns the lengthght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int String_findLength(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}
/**
 * compile_alpha - compare chars of strings
 * @string: enter string.
 * @delim: delimiter.
 * Return: 1 if are equals, 0 if not.
 */
int compile_alpha(char string[], const char *delim)
{
unsigned int x, y, z;

x = 0;
z = 0;
while (string[x])
{
y = 0;
while (delim[y])
{
if (string[x] == delim[y])
{
z++;
break;
}
y++;
}
x++;
}
if (x == z)
return (1);
return (0);
}
/**
 * cut_string - splits a string by some delimiter.
 * @string: enter string.
 * @delim: delimiter.
 * Return: string splited.
 */
char *cut_string(char string[], const char *delim)
{
static char *split, *string_end;
char *string_start;
unsigned int u, bool;

if (string != NULL)
{
if (compile_alpha(string, delim))
return (NULL);
split = string; /*Store first address*/
u = String_findLength(string);
string_end = &string[u]; /*Store last address*/
}
string_start = split;
if (string_start == string_end) /*Reaching the end*/
return (NULL);

for (bool = 0; *split; split++)
{
/*Breaking loop finding the next token*/
if (split != string_start)
if (*split && *(split - 1) == '\0')
break;
/*Replacing delimiter for null char*/
for (u = 0; delim[u]; u++)
{
if (*split == delim[u])
{
*split = '\0';
if (split == string_start)
string_start++;
break;
}
}
if (bool == 0 && *split) /*String != Delim*/
bool = 1;
}
if (bool == 0) /*String == Delim*/
return (NULL);
return (string_start);
}
