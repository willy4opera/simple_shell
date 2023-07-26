#include "devshell.h"

/**
 * shl_get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*shl_get_builtin(char *cmd))(shll_data_t *)
{
	btstruct_t builtin[] = {
		{ "env", _env },
		{ "exit", shell_exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", shl_cd_shell },
		{ "help", shl_get_help },
		{ NULL, NULL }
	};
	int count;

	for (count = 0; builtin[count].cmd_nm; count++)
	{
		if (comprs_str(builtin[count].cmd_nm, cmd) == 0)
			break;
	}

	return (builtin[count].d_pointr_f);
}
