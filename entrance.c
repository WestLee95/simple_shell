#include "verma.h"
/**
 * f_data - frees data struct
 * @dish: data struct
 * Return: no return
 **********************************/
void f_data(verma_shell *dish)
{
unsigned int u = 0;
while (dish->environ_var[u])
{
free(dish->environ_var[u]);
u++;
}

free(dish->environ_var);
free(dish->process_identifier;
}
/**
 * s_data - Initialize data struct
 * @dish: data struct
 * @verma: arg vector
 * Return: no return
 **********************************/
void s_data(verma_shell *dish, char **verma)
{
unsigned int u = 0;

dish->verma = verma;
dish->enter = NULL;
dish->argz = NULL;
dish->state = 0;
dish->count = 1;

for (u = 0; environ[u]; u++)
;

dish->environ_var = malloc(sizeof(char *) * (u + 1));

for (u = 0; environ[u]; u++)
{
dish->environ_var[u] = Moon(environ[u]);
}

dish->environ_var[u] = NULL;
dish->process_identifier = int_toString(getpid());
}



/**
 * main - Entry point
 * @ac: argument count
 * @verma: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **verma)
{
	verma_shell dish;
	(void) ac;

	signal(SIGINT, sing_rule);
	s_data(&dish, verma);
	shell_loop(&dish);
	f_data(&dish);
	if (dish.state < 0)
		return (255);
	return (dish.state);
}
