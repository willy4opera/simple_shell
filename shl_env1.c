#include "devshell.h"

/**
 * copy_info - copies info to create
 * a nw env or alias
 * @cmd_nm: cmd_nm (env or alias)
 * @envr_val: value (env or alias)
 *
 * Return: nw env or alias.
 */
char *copy_info(char *cmd_nm, char *envr_val)
{
	char *nw;
	int len_name, len_value, len;

	len_name = line_str(cmd_nm);
	len_value = line_str(envr_val);
	len = len_name + len_value + 2;
	nw = malloc(sizeof(char) * (len));
	strng_copy(nw, cmd_nm);
	strng_cat(nw, "=");
	strng_cat(nw, envr_val);
	strng_cat(nw, "\0");

	return (nw);
}

/**
 * set_env - sets an environment variable
 *
 * @cmd_nm: name of the environment variable
 * @envr_val: envr_val of the environment variable
 * @shl_data_shll: data structure (shl_env)
 * Return: no return
 */
void set_env(char *cmd_nm, char *envr_val, shll_data_t *shl_data_shll)
{
	int count;
	char *var_env, *name_env;

	for (count = 0; shl_data_shll->envr_var[count]; count++)
	{
		var_env = shl_strdup(shl_data_shll->envr_var[count]);
		name_env = shl_strtok(var_env, "=");
		if (comprs_str(name_env, cmd_nm) == 0)
		{
			free(shl_data_shll->envr_var[count]);
			shl_data_shll->envr_var[count] = copy_info(name_env, envr_val);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shl_data_shll->envr_var = shl_reallocdp(shl_data_shll->envr_var,
			count, sizeof(char *) * (count + 2));
	shl_data_shll->envr_var[count] = copy_info(cmd_nm, envr_val);
	shl_data_shll->envr_var[count + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @shl_data_shll: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(shll_data_t *shl_data_shll)
{

	if (shl_data_shll->arg_cli[1] == NULL || shl_data_shll->arg_cli[2] == NULL)
	{
		shl_get_error(shl_data_shll, -1);
		return (1);
	}

	set_env(shl_data_shll->arg_cli[1], shl_data_shll->arg_cli[2],
			shl_data_shll);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @shl_data_shll: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(shll_data_t *shl_data_shll)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int count, j, k;

	if (shl_data_shll->arg_cli[1] == NULL)
	{
		shl_get_error(shl_data_shll, -1);
		return (1);
	}
	k = -1;
	for (count = 0; shl_data_shll->envr_var[count]; count++)
	{
		var_env = shl_strdup(shl_data_shll->envr_var[count]);
		name_env = shl_strtok(var_env, "=");
		if (comprs_str(name_env, shl_data_shll->arg_cli[1]) == 0)
		{
			k = count;
		}
		free(var_env);
	}
	if (k == -1)
	{
		shl_get_error(shl_data_shll, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (count));
	for (count = j = 0; shl_data_shll->envr_var[count]; count++)
	{
		if (count != k)
		{
			realloc_environ[j] = shl_data_shll->envr_var[count];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(shl_data_shll->envr_var[k]);
	free(shl_data_shll->envr_var);
	shl_data_shll->envr_var = realloc_environ;
	return (1);
}
