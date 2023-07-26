#include "devshell.h"

/**
 * shl_get_error - calls the error according the builtin, syntax or permission
 * @shl_data_shll: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int shl_get_error(shll_data_t *shl_data_shll, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = shl_error_env(shl_data_shll);
		break;
	case 126:
		error = shl_error_path(shl_data_shll);
		break;
	case 127:
		error = shl_error_nf(shl_data_shll);
		break;
	case 2:
		if (comprs_str("exit", shl_data_shll->arg_cli[0]) == 0)
			error = shl_exit_shell_on_error(shl_data_shll);
		else if (comprs_str("cd", shl_data_shll->arg_cli[0]) == 0)
			error = shl_cd_get_error(shl_data_shll);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, line_str(error));
		free(error);
	}

	shl_data_shll->stat = eval;
	return (eval);
}
