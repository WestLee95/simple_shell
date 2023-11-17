#include "man.h"

/**
 * cdErr_message - joins the message for chnange directory error
 * @shd: data essential 
 * @memo: message to display
 * @o: display message
 * @d_s: defines counter lines
 * Return: fetch error message
 */
char *cdErr_message(man_shell *shd, char *memo, char *o, char *d_s)
{
char *bad_thing;

dup_string(o, shd->man[0]);
string_concat(o, ": ");
string_concat(o, d_s);
string_concat(o, ": ");
string_concat(o, shd->arggs[0]);
string_concat(o, memo);
if (shd->arggs[1][0] == '-')
{
bad_thing = malloc(3);
bad_thing[0] = '-';
bad_thing[1] = shd->arggs[1][1];
bad_thing[2] = '\0';
string_concat(o, bad_thing);
free(bad_thing);
}
else
{
string_concat(o, shd->arggs[1]);
}

string_concat(o, "\n");
string_concat(o, "\0");
return (o);
}

/**
 * error_cd - this is an error message for a cd command in get_cd
 * @shd: data essential (directory)
 * Return:fetch Error message
 *
 */
char *error_cd(man_shell *shd)
{
int lathum, lathum_id;
char *o, *d_s, *memo;

d_s = intTo_String(shd->countter);
if (shd->arggs[1][0] == '-')
{
memo = ": Bad option ";
lathum_id = 2;
}
else
{
memo = ": There is no such file or directory ";
lathum_id = String_length(shd->args[1]);
}

lathum = String_length(shd->man[0]) + String_length(shd->arggs[0]);
lathum += String_length(d_s) + String_length(memo) + lathum_id + 5;
o = malloc(sizeof(char) * (lathum + 1));
if (o == NULL)
{
free(d_s);
return (NULL);
}

o = cdErr_message(shd, memo, o, d_s);

free(d_s);

return (o);
}


/**
 * cmdNotFound_msg - iterable error message for directive not found
 * @shd: data essential with counter and arguments included
 * Return: fetch Error message
 */
char *cmdNotFound_msg(man_shell *shd)
{
int lathum;
char *o;
char *d_s;

d_s = intTo_String(shd->countter);
lathum = String_length(shd->man[0]) + String_length(d_s);
lathum += String_length(shd->arggs[0]) + 16;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
{
free(o);
free(d_s);
return (NULL);
}
*dup_string(o, shd->man[0]);
string_concat(o, ": ");
string_concat(o, d_s);
string_concat(o, ": ");
string_concat(o, shd->arggs[0]);
string_concat(o, ": not found\n");
string_concat(o, "\0");
free(d_s);
return (o);
}

/**
 * exitIn_get - iterable error message for exiting in get_exit
 * @shd: data essential counter, arguments
 * Return: fetch Error message
 */
char *exitIn_get(man_shell *shd)
{
int lathum;
char *o;
char *d_s;

d_s = intTo_String(shd->countter);
lathum = String_length(shd->man[0]) + String_length(d_s);
lathum += String_length(shd->arggs[0]) + String_length(shd->arggs[1]) + 23;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
{
free(d_s);
return (NULL);
}
dup_string(o, shd->man[0]);
string_concat(o, ": ");
string_concat(o, d_s);
string_concat(o, ": ");
string_concat(o, shd->arggs[0]);
string_concat(o, ": Bad number: ");
string_concat(o, shd->arggs[1]);
string_concat(o, "\n\0");
free(d_s);

return (o);
}
