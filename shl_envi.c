#include "devshell.h"

/**
 * cmp_env_name - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @cmd_nm: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *cmd_nm)
{
	int count;

	for (count = 0; nenv[count] != '='; count++)
	{
		if (nenv[count] != cmd_nm[count])
		{
			return (0);
		}
	}

	return (count + 1);
}

/**
 * _getenv - get an environment variable
 * @cmd_nm: name of the environment variable
 * @envr_var: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *cmd_nm, char **envr_var)
{
	char *ptr_env;
	int count, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* shl_env is declared in the header file */
	for (count = 0; envr_var[count]; count++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(envr_var[count], cmd_nm);
		if (mov)
		{
			ptr_env = envr_var[count];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @shl_data_shll: data relevant.
 * Return: 1 on success.
 */
int _env(shll_data_t *shl_data_shll)
{
	int count, j;

	for (count = 0; shl_data_shll->envr_var[count]; count++)
	{

		for (j = 0; shl_data_shll->envr_var[count][j]; j++)
			;

		write(STDOUT_FILENO, shl_data_shll->envr_var[count], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shl_data_shll->stat = 0;

	return (1);
}
