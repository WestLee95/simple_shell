#include "man.h"
/**
 * free_data_struct - releases data architecture
 * @shd: data architecture
 * Return:don't fetch
 **********************************/
void free_data_struct(man_shell *shd)
{
unsigned int a = 0;
while (shd->env_variable[a])
{
free(shd->env_variable[a]);
a++;
}

free(shd->env_variable);
free(shd->p_id);
}
/**
 * s_data - declare data framework.
 * @shd: data framework.
 * @man: argument vector.
 * Return: don't fetch.
 **********************************/
void s_data(man_shell *shd, char **man)
{
unsigned int a = 0;

shd->man = man;
shd->enter = NULL;
shd->arggs = NULL;
shd->state = 0;
shd->countter = 1;

for (a = 0; environ[a]; a++)
;

shd->environ_var = malloc(sizeof(char *) * (a + 1));

for (a = 0; environ[a]; a++)
{
shd->environ_var[a] = dup_mem(environ[a]);
}

shd->environ_var[a] = NULL;
shd->p_id = int_toString(getpid());
}



/**
 * main - entrance point
 * @ac: arg counter
 * @man: arg Vect
 * Return: fetch 0 when it succeeds.
 */
int main(int ac, char **man)
{
	man_shell shd;
	(void) ac;

	signal(SIGINT, sing_line);
	s_data(&shd, man);
	loop_shell(&shd);
	free_data_struct(&shd);
	if (shd.state < 0)
		return (255);
	return (shd.state);
}
