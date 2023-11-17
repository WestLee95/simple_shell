#include "man.h"
/**
 * ChangeDirectory - convert to the parent directory
 * @shd: the data essential (environment)
 * Return: don't return
 */
void ChangeDirectory(man_shell *shd)
{
	char pwd[PATH_MAX];
	char *k, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = dup_mem(pwd);
	set_env_Var("OLDPWD", cp_pwd, shd);
	d = shd->arggs[1];
	if (con_comp(".", d) == 0)
	{
		set_env_Var("PWD", cp_pwd, shd);
		free(cp_pwd);
		return;
	}
	if (con_comp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	ReverseString(cp_strtok_pwd);
	cp_strtok_pwd = split_string(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = string_split(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			Rev_String(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env_Var("PWD", cp_strtok_pwd, shd);
	}
	else
	{
		chdir("/");
		set_env_Var("PWD", "/", shd);
	}
	shd->state = 0;
	free(cp_pwd);
}

/**
 * ChaneUser_dir - convert to a directory given by the user
 * @shd: data essential 
 * Return:do not return any value
 */
void ChaneUser_dir(man_shell *shd)
{
	char pwd[PATH_MAX];
	char *d, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	d = shd->arggs[1];
	if (chdir(d) == -1)
	{
		err_call(shd, 2);
		return;
	}

	cp_pwd = dup_mem(pwd);
	set_envV("OLDPWD", cp_pwd, shd);

	cp_dir = dup_mem(d);
	set_envV("PWD", cp_dir, shd);

	free(cp_pwd);
	free(cp_dir);

	shd->state = 0;

	chdir(d);
}
/**
 * changeDir_ToPrev - convert to the initial directory
 * @shd: data essential 
 * Return:  return no value
 */
void changeDir_ToPrev(man_shell *shd)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = dup_mem(pwd);

	p_oldpwd = get_env_var("OLDPWD", dsh->environ_var);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = dup_mem(p_oldpwd);

	set_envV("OLDPWD", cp_pwd, dsh);

	if (chdir(cp_oldpwd) == -1)
		set_envV("PWD", cp_pwd, dsh);
	else
		set_envV("PWD", cp_oldpwd, dsh);

	p_pwd = get_env_var("PWD", dsh->environ_var);

	write(STDOUT_FILENO, p_pwd, String_length(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shd->state = 0;

	chdir(p_pwd);
}

/**
 * ChangeDir_home - converts to root directory
 * @shd: data essential 
 * Return:  return no value
 */
void ChangeDir_home(man_shell *shd)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = Stardom(pwd);

	home = get_env_var("HOME", shd->environ_var);

	if (home == NULL)
	{
		set_env_Var("OLDPWD", p_pwd, shd);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		err_call(shd, 2);
		free(p_pwd);
		return;
	}

	set_env_Var("OLDPWD", p_pwd, shd);
	set_env_Var("PWD", home, shd);
	free(p_pwd);
	shd->status = 0;
}
