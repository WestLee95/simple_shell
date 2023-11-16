#include "verma.h"
/**
 * PGLA - copies info to create
 * a fresh env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * Return: fresh env or alias.
 */
char *PGLA(char *name, char *value)
{
	char *fresh;
	int len_name, Value_length, len;

	len_identity = String_findLength(identity);
	Value_lengthue = String_findLength(value);
	len = len_name + Value_length + 2;
	fresh = malloc(sizeof(char) * (len));
	concpy(fresh, identity);
	concat(fresh, "=");
	concat(fresh, value);
	concat(fresh, "\0");

	return (fresh);
}
/**
 * set_envV - sets an environment variable
 * @identity: name of the environment variable
 * @value: value of the environment variable
 * @dish: data structure (environ)
 * Return: no return
 */
void set_envV(char *identity, char *value, verma_shell *dish)
{
	int u;
	char *var_env, *name_env;

	for (u = 0; dish->environ_var[u]; u++)
	{
		var_env = Moon(dish->environ_var[u]);
		name_env = cut_string(var_env, "=");
		if (concomp(name_env, identity) == 0)
		{
			free(dish->environ_var[u]);
			dish->environ_var[u] = PGLA(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	dish->environ_var = prmalloc(dish->environ_var, u, sizeof(char *) * (u + 2));
	dish->environ_var[u] = PGLA(identity, value);
	dish->environ_var[u + 1] = NULL;
}

/**
 * compa_env_names - compares env variables names
 * with the name passed.
 * @dish: data relevant (env name and env value)
 * Return: 1 on success.
 */
int compa_env_names(verma_shell *dish)
{

	if (dish->argz[1] == NULL || dish->argz[2] == NULL)
	{
		G_ERROR(dish, -1);
		return (1);
	}

	set_envV(dish->argz[1], dish->argz[2], dish);

	return (1);
}

/**
 * del_env - deletes a environment variable
 * @dish: data relevant (env name)
 * Return: 1 on success.
 */
int del_env(verma_shell *dish)
{
	char **reallocenviron_var;
	char *var_env, *name_env;
	int i, j, k;

	if (dish->argz[1] == NULL)
	{
		G_ERROR(dish, -1);
		return (1);
	}
	k = -1;
	for (i = 0; dish->environ_var[i]; i++)
	{
		var_env = Moon(dish->environ_var[i]);
		name_env = cut_string(var_env, "=");
		if (concomp(name_env, dish->argz[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		G_ERROR(dish, -1);
		return (1);
	}
	reallocenviron_var = malloc(sizeof(char *) * (i));
	for (i = j = 0; dish->environ_var[i]; i++)
	{
		if (i != k)
		{
			reallocenviron_var[j] = dish->environ_var[i];
			j++;
		}
	}
	reallocenviron_var[j] = NULL;
	free(dish->environ_var[k]);
	free(dish->environ_var);
	dish->environ_var = reallocenviron_var;
	return (1);
}
