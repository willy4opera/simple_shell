#include "devshell.h"

/**
 * shl_exec_line - finds builtins and commands
 *
 * @shl_data_shll: data relevant (arg_cli)
 * Return: 1 on success.
 */
int shl_exec_line(shll_data_t *shl_data_shll)
{
	int (*builtin)(shll_data_t *shl_data_shll);

	if (shl_data_shll->arg_cli[0] == NULL)
		return (1);

	builtin = shl_get_builtin(shl_data_shll->arg_cli[0]);

	if (builtin != NULL)
		return (builtin(shl_data_shll));

	return (shl_cmd_exec(shl_data_shll));
}
