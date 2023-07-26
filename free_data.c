#include "devshell.h"

/**
 * free_data - free all data structure
 * @shl_data_shll: data structure
 * Return: void
 */
void free_data(shll_data_t *shl_data_shll)
{
	unsigned int count;

	for (count = 0; shl_data_shll->envr_var[count]; count++)
	{
		free(shl_data_shll->envr_var[count]);
	}

	free(shl_data_shll->envr_var);
	free(shl_data_shll->shell_pid);
}

/**
 * set_data - Init data structure
 * @shl_data_shll: data structure
 * @arg_var: arg vector
 * Return: void
 */
void set_data(shll_data_t *shl_data_shll, char **arg_var)
{
	unsigned int count;

	shl_data_shll->arg_var = arg_var;
	shl_data_shll->cli_inpt = NULL;
	shl_data_shll->arg_cli = NULL;
	shl_data_shll->stat = 0;
	shl_data_shll->ln_cntr = 1;

	for (count = 0; environ[count]; count++)
		;

	shl_data_shll->envr_var = malloc(sizeof(char *) * (count + 1));

	for (count = 0; environ[count]; count++)
	{
		shl_data_shll->envr_var[count] = shl_strdup(environ[count]);
	}

	shl_data_shll->envr_var[count] = NULL;
	shl_data_shll->shell_pid = shl_get_itos(getpid());
}

/**
 * main - Entry point
 * @ac: argument count
 * @arg_var: argument vector
 * Return: 0 on success.
 */
int main(int ac, char **arg_var)
{
	shll_data_t shl_data_shll;
	(void) ac;

	signal(SIGINT, shl_get_sigint);
	set_data(&shl_data_shll, arg_var);
	shl_loop_shell(&shl_data_shll);
	free_data(&shl_data_shll);
	if (shl_data_shll.stat < 0)
		return (255);
	return (shl_data_shll.stat);
}

