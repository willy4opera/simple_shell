#include "devshell.h"

/**
 * shell_exit - exits the shell
 *
 * @shl_data_shll: data relevant (stat and args)
 * Return: 0 on success.
 */
int shell_exit(shll_data_t *shl_data_shll)
{
	unsigned int u_stat;
	int chk_dgt;
	int Len_of_str;
	int Num;

	if (shl_data_shll->arg_cli[1] != NULL)
	{
		u_stat = _atoi(shl_data_shll->arg_cli[1]);
		chk_dgt = shl_isdigit(shl_data_shll->arg_cli[1]);
		Len_of_str = line_str(shl_data_shll->arg_cli[1]);
		Num = u_stat > (unsigned int)INT_MAX;
		if (!chk_dgt || Len_of_str > 10 || Num)
		{
			shl_get_error(shl_data_shll, 2);
			shl_data_shll->stat = 2;
			return (1);
		}
		shl_data_shll->stat = (u_stat % 256);
	}
	return (0);
}
