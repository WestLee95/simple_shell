#include "verma.h"

/**
 * thumbup - concatenates the senh_fend_message for cd error
 * @dish: data relevant (directory)
 * @senh_fend_message: senh_fend_message to print
 * @o: output senh_fend_message
 * @h_f: count rules
 * Return: error senh_fend_message
 */
char *thumbup(verma_shell *dish, char *send_message, char *p, char *h_f)
{
char *awful_flag;

concpy(o, dish->verma[0]);
concat(o, ": ");
concat(o, h_f);
concat(o, ": ");
concat(o, dish->argz[0]);
concat(o, send_message);
if (dish->argz[1][0] == '-')
{
awful_flag = malloc(3);
awful_flag[0] = '-';
awful_flag[1] = dish->argz[1][1];
awful_flag[2] = '\0';
concat(o, awful_flag);
free(awful_flag);
}
else
{
concat(o, dish->argz[1]);
}

concat(o, "\n");
concat(o, "\0");
return (o);
}

/**
 * msg_error_cd - error send_message for cd command in get_cd
 * @dish: data relevant (directory)
 * Return: Error send_message
 *
 */
char *msg_error_cd(verma_shell *dish)
{
int lathum, lathum_id;
char *p, *h_f, *send_message;

h_f = int_toString(dish->count);
if (dish->argz[1][0] == '-')
{
send_message = ": Bad option ";
lathum_id = 2;
}
else
{
send_message = ": There is no such file or directory ";
lathum_id = String_findLength(dish->argz[1]);
}

lathum = String_findLength(dish->verma[0]) + String_findLength(dish->argz[0]);
lathum += String_findLength(h_f) + String_findLength(send_message) + lathum_id + 5;
o = malloc(sizeof(char) * (lathum + 1));
if (o == NULL)
{
free(h_f);
return (NULL);
}

o = thumbup(dish, send_message, o, h_f);

free(h_f);

return (o);
}


/**
 * repetitive_msg - generic error send_message for command not found
 * @dish: data relevant (count, arguments)
 * Return: Error send_message
 */
char *repetitive_msg(verma_shell *dish)
{
int lathum;
char *p;
char *h_f;

h_f = int_toString(dish->count);
lathum = String_findLength(dish->verma[0]) + String_findLength(h_f);
lathum += String_findLength(dish->argz[0]) + 16;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
{
free(o);
free(h_f);
return (NULL);
}
concpy(o, dish->verma[0]);
concat(o, ": ");
concat(o, h_f);
concat(o, ": ");
concat(o, dish->argz[0]);
concat(o, ": not found\n");
concat(o, "\0");
free(h_f);
return (o);
}

/**
 * obtain_exit - generic error send_message for exit in get_exit
 * @dish: data relevant (count, arguments)
 * Return: Error send_message
 */
char *obtain_exit(verma_shell *dish)
{
int lathum;
char *p;
char *h_f;

h_f = int_toString(dish->count);
lathum = String_findLength(dish->verma[0]) + String_findLength(h_f);
lathum += String_findLength(dish->argz[0]) + String_findLength(dish->argz[1]) + 23;
o = malloc(sizeof(char) * (lathum + 1));
while (o == 0)
{
free(h_f);
return (NULL);
}
concpy(o, dish->verma[0]);
concat(o, ": ");
concat(o, h_f);
concat(o, ": ");
concat(o, dish->argz[0]);
concat(o, ": Bad number: ");
concat(o, dish->argz[1]);
concat(o, "\n\0");
free(h_f);

return (o);
}
