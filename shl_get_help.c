#include "devshell.h"

/**
 * shl_get_help - retrieves help messages according builtin
 * @shl_data_shll: data structure (arg_cli and cli_inpt)
 * Return: 0
 */
int shl_get_help(shll_data_t *shl_data_shll)
{

	if (shl_data_shll->arg_cli[1] == 0)
		shl_help_general();
	else if (comprs_str(shl_data_shll->arg_cli[1], "setenv") == 0)
		shl_help_env();
	else if (comprs_str(shl_data_shll->arg_cli[1], "env") == 0)
		shl_help_env();
	else if (comprs_str(shl_data_shll->arg_cli[1], "unsetenv") == 0)
		shl_help_unsetenv();
	else if (comprs_str(shl_data_shll->arg_cli[1], "help") == 0)
		shl_helper();
	else if (comprs_str(shl_data_shll->arg_cli[1], "exit") == 0)
		shl_help_exit();
	else if (comprs_str(shl_data_shll->arg_cli[1], "cd") == 0)
		shl_helper_cd();
	else if (comprs_str(shl_data_shll->arg_cli[1], "alias") == 0)
		shl_helper();
	else
		write(STDERR_FILENO, shl_data_shll->arg_cli[0],
				line_str(shl_data_shll->arg_cli[0]));

	shl_data_shll->stat = 0;
	return (1);
}

