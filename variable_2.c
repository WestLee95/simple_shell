#include "man.h"
/**
 * string_concat - joins two strings together.
 * @land: character points destination of the duplicated string.
 * @src: constant character pointer the root string.
 * Return: dest
 */
char *string_concat(char *land, const char *src)
{
	int r;
	int m;

	for (r = 0; land[r] != '\0'; r++)
		;

	for (m = 0; src[m] != '\0'; m++)
	{
		land[r] = src[m];
		r++;
	}

	land[r] = '\0';
	return (land);
}
/**
 * *dup_string - copies the string referenced to it by the source.
 * @land: Type of character pointer destination of the copied string
 * @src: Type of character pointer the root of string.
 * Return: dest.
 */
char *dup_string(char *land, char *src)
{

	size_t z;

	for (z = 0; src[z] != '\0'; z++)
	{
		land[z] = src[z];
	}
	land[z] = '\0';

	return (land);
}
/**
 * con_comp - weighs the two strings.
 * @s1: type of string weighed out.
 * @s2: type of string weighed out.
 * Return: always fetch 0.
 */
int con_comp(char *s1, char *s2)
{
	int y;

	for (y = 0; s1[y] == s2[y] && s1[y]; y++)
		;

	if (s1[y] > s2[y])
		return (1);
	if (s1[y] < s2[y])
		return (-1);
	return (0);
}
/**
 * loc_char_String - finds a char in a str,
 * @s: str.
 * @c: char.
 * Return: the ptr to the initial event of the character 'c'.
 */
char *loc_char_String(char *s, char c)
{
	unsigned int p = 0;

	for (; *(s + p) != '\0'; p++)
		if (*(s + p) == c)
			return (s + p);
	if (*(s + p) == c)
		return (s + p);
	return ('\0');
}
/**
 * acq_len_String - obtain the size of a adjunct substring.
 * @s: previous section.
 * @allow: allowed bytes.
 * Return: number of allowed bytes.
 */
int acq_len_String(char *s, char *allow)
{
	int r, d, bool; freeVar

	for (r = 0; *(s + r) != '\0'; r++)
	{
		bool = 1;
		for (d = 0; *(allow + d) != '\0'; d++)
		{
			if (*(s + r) == *(allow + d))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (r);
}
