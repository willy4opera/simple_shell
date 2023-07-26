#include "devshell.h"

/**
 * shl_cd_dot - changes to the parent directory
 *
 * @shl_data_shll: data relevant (shl_env)
 *
 * Return: no return
 */
void shl_cd_dot(shll_data_t *shl_data_shll)
{
	char pwd[PATH_MAX];
	char *dir, *shl_cp_pwd, *strk_pswd;

	getcwd(pwd, sizeof(pwd));
	shl_cp_pwd = shl_strdup(pwd);
	set_env("OLDPWD", shl_cp_pwd, shl_data_shll);
	dir = shl_data_shll->arg_cli[1];
	if (comprs_str(".", dir) == 0)
	{
		set_env("PWD", shl_cp_pwd, shl_data_shll);
		free(shl_cp_pwd);
		return;
	}
	if (comprs_str("/", shl_cp_pwd) == 0)
	{
		free(shl_cp_pwd);
		return;
	}
	strk_pswd = shl_cp_pwd;
	shl_rev_string(strk_pswd);
	strk_pswd = shl_strtok(strk_pswd, "/");
	if (strk_pswd != NULL)
	{
		strk_pswd = shl_strtok(NULL, "\0");

		if (strk_pswd != NULL)
			shl_rev_string(strk_pswd);
	}
	if (strk_pswd != NULL)
	{
		chdir(strk_pswd);
		set_env("PWD", strk_pswd, shl_data_shll);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", shl_data_shll);
	}
	shl_data_shll->stat = 0;
	free(shl_cp_pwd);
}

/**
 * shl_cd_to - changes to a directory given
 * by the user
 *
 * @shl_data_shll: data relevant (directories)
 * Return: no return
 */
void shl_cd_to(shll_data_t *shl_data_shll)
{
	char pwd[PATH_MAX];
	char *dir, *shl_cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = shl_data_shll->arg_cli[1];
	if (chdir(dir) == -1)
	{
		shl_get_error(shl_data_shll, 2);
		return;
	}

	shl_cp_pwd = shl_strdup(pwd);
	set_env("OLDPWD", shl_cp_pwd, shl_data_shll);

	cp_dir = shl_strdup(dir);
	set_env("PWD", cp_dir, shl_data_shll);

	free(shl_cp_pwd);
	free(cp_dir);

	shl_data_shll->stat = 0;

	chdir(dir);
}

/**
 * shl_cd_previous - changes to the previous directory
 *
 * @shl_data_shll: data relevant (shl_env)
 * Return: no return
 */
void shl_cd_previous(shll_data_t *shl_data_shll)
{
	char pwd[PATH_MAX];
	char *p_psswd, *old_psswd, *shl_cp_pwd, *cp_oldpasswd;

	getcwd(pwd, sizeof(pwd));
	shl_cp_pwd = shl_strdup(pwd);

	old_psswd = _getenv("OLDPWD", shl_data_shll->envr_var);

	if (old_psswd == NULL)
		cp_oldpasswd = shl_cp_pwd;
	else
		cp_oldpasswd = shl_strdup(old_psswd);

	set_env("OLDPWD", shl_cp_pwd, shl_data_shll);

	if (chdir(cp_oldpasswd) == -1)
		set_env("PWD", shl_cp_pwd, shl_data_shll);
	else
		set_env("PWD", cp_oldpasswd, shl_data_shll);

	p_psswd = _getenv("PWD", shl_data_shll->envr_var);

	write(STDOUT_FILENO, p_psswd, line_str(p_psswd));
	write(STDOUT_FILENO, "\n", 1);

	free(shl_cp_pwd);
	if (old_psswd)
		free(cp_oldpasswd);

	shl_data_shll->stat = 0;

	chdir(p_psswd);
}

/**
 * shl_cdir_home - changes to home directory
 *
 * @shl_data_shll: data relevant (shl_env)
 * Return: no return
 */
void shl_cdir_home(shll_data_t *shl_data_shll)
{
	char *p_psswd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_psswd = shl_strdup(pwd);

	home = _getenv("HOME", shl_data_shll->envr_var);

	if (home == NULL)
	{
		set_env("OLDPWD", p_psswd, shl_data_shll);
		free(p_psswd);
		return;
	}

	if (chdir(home) == -1)
	{
		shl_get_error(shl_data_shll, 2);
		free(p_psswd);
		return;
	}

	set_env("OLDPWD", p_psswd, shl_data_shll);
	set_env("PWD", home, shl_data_shll);
	free(p_psswd);
	shl_data_shll->stat = 0;
}
