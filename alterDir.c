#include "verma.h"
/**
 * Change_Dir - changes to the parent directory
 * @dish: the data relevant (environ)
 * Return: no return
 */
void Change_Dir(verma_shell *dish)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = Moon(pwd);
	set_envV("OLDPWD", cp_pwd, dish);
	d = dish->argz[1];
	if (concomp(".", d) == 0)
	{
		set_envV("PWD", cp_pwd, dish);
		free(cp_pwd);
		return;
	}
	if (concomp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	AssistString(cp_strtok_pwd);
	cp_strtok_pwd = cut_string(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = cut_string(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			AssistString(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_envV("PWD", cp_strtok_pwd, dish);
	}
	else
	{
		chdir("/");
		set_envV("PWD", "/", dish);
	}
	dish->state = 0;
	free(cp_pwd);
}

/**
 * ChaneDir_usr - changes to a dir given by user
 * @dish: data relevant (directories)
 * Return: no return
 */
void ChaneDir_usr(verma_shell *dish)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = dish->argz[1];
	if (chdir(d) == -1)
	{
		G_ERROR(dish, 2);
		return;
	}

	cp_pwd = Moon(pwd);
	set_envV("OLDPWD", cp_pwd, dish);

	cp_dir = Moon(d);
	set_envV("PWD", cp_dir, dish);

	free(cp_pwd);
	free(cp_dir);

	dish->state = 0;

	chdir(d);
}
/**
 * alterDir_prev - changes to the previous directory
 * @dish: data relevant (environ)
 * Return: no return
 */
void alterDir_prev(verma_shell *dish)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = Moon(pwd);

	p_oldpwd = obtainenv("OLDPWD", dish->environ_var);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = Moon(p_oldpwd);

	set_envV("OLDPWD", cp_pwd, dish);

	if (chdir(cp_oldpwd) == -1)
		set_envV("PWD", cp_pwd, dish);
	else
		set_envV("PWD", cp_oldpwd, dish);

	p_pwd = obtainenv("PWD", dish->environ_var);

	write(STDOUT_FILENO, p_pwd, String_findLength(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	dish->state = 0;

	chdir(p_pwd);
}

/**
 * alterDir_ - changes to home directory
 * @dish: data relevant (environ)
 * Return: no return
 */
void alterDir_(verma_shell *dish)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = Moon(pwd);

	home = obtainenv("HOME", dish->environ_var);

	if (home == NULL)
	{
		set_envV("OLDPWD", p_pwd, dish);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		G_ERROR(dish, 2);
		free(p_pwd);
		return;
	}

	set_envV("OLDPWD", p_pwd, dish);
	set_envV("PWD", home, dish);
	free(p_pwd);
	dish->state = 0;
}
