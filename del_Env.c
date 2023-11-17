#include "man.h"
/**
 * PGLA - duplicates information to generate
 * a new environment or alias.
 * @tag:indicates name with environment or alias included.
 * @worth: value with environment or alias.
 * Return: fetch new environment or alias.
 */
char *PGLA(char *tag, char *worth)
{
	char *modern;
	int len_name, Value_length, len;

	len_name = String_length(name);
	Value_length = String_length(worth);
	len = len_name + Value_length + 2;
	modern = malloc(sizeof(char) * (len));
	dup_string(modern, tag);
	string_concat(modern, "=");
	string_concat(modern, worth);
	string_concat(modern, "\0");

	return (modern);
}
/**
 * set_env_Var - position an env var
 * @tag: identity of an env var
 * @worth: worth of the env var
 * @shd: framework of data of the environment
 * Return: no return
 */
void set_env_Var(char *tag, char *worth, man_shell *shd)
{
	int x;
	char *env_var, *name_env;

	for (x = 0; shd->environ_var[x]; x++)
	{
		env_var = dup_mem(shd->environ_var[x]);
		env_name = string_split(env_var, "=");
		if (con_comp(env_name, tag) == 0)
		{
			free(shd->environ_var[x]);
			shd->environ_var[x] = PGLA(env_name, worth);
			free(env_var);
			return;
		}
		free(env_var);
	}

	shd->environ_var = **pr_malloc(shd->environ_var, x, sizeof(char *) * (x + 2));
	shd->environ_var[x] = PGLA(tag, worth);
	shd->environ_var[x + 1] = NULL;
}

/**
 * comp_envV_names - collate environ var names
 * with the name passed.
 * @shd: info essential (env name and env value)
 * Return: fetch 1 if it's successful.
 */
int comp_envV_names(man_shell *shd)
{

	if (shd->arggs[1] == NULL || shd->arggs[2] == NULL)
	{
		err_call(shd, -1);
		return (1);
	}

	set_env_Var(shd->arggs[1], shd->arggs[2], shd);

	return (1);
}

/**
 * del_env_var - removes a env var
 * @shd: info essential (env name)
 * Return:fetch 1 if there's success.
 */
int del_env_var(man_shell *shd)
{
	char **reallocenv_variable;
	char *env_var, *env_name;
	int q, r, s;

	if (shd->arggs[1] == NULL)
	{
		err_call(shd, -1);
		return (1);
	}
	s = -1;
	for (q = 0; shd->environ_var[i]; q++)
	{
		env_var = dup_mem(shd->environ_var[q]);
		env_name = string_split(env_var, "=");
		if (con_comp(env_name, shd->arggs[1]) == 0)
		{
			s = q;
		}
		free(env_var);
	}
	if (s == -1)
	{
		err_call(shd, -1);
		return (1);
	}
	reallocenv_variable = malloc(sizeof(char *) * (q));
	for (q = r = 0; shd->environ_var[q]; q++)
	{
		if (q != s)
		{
			reallocenv_variable[r] = shd->environ_var[q];
			r++;
		}
	}
	reallocenv_variable[r] = NULL;
	free(shd->environ_var[s]);
	free(shd->environ_var);
	shd->environ_var = reallocenv_variable;
	return (1);
}
