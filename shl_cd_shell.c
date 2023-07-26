#include "devshell.h"

/**
 * shl_cd_shell - changes current directory
 *
 * @shl_data_shll: data relevant
 * Return: 1 on success
 */
int shl_cd_shell(shll_data_t *shl_data_shll)
{
	char *dir;
	int home1, home2, is_dash;

	dir = shl_data_shll->arg_cli[1];

	if (dir != NULL)
	{
		home1 = comprs_str("$HOME", dir);
		home2 = comprs_str("~", dir);
		is_dash = comprs_str("--", dir);
	}

	if (dir == NULL || !home1 || !home2 || !is_dash)
	{
		shl_cdir_home(shl_data_shll);
		return (1);
	}

	if (comprs_str("-", dir) == 0)
	{
		shl_cd_previous(shl_data_shll);
		return (1);
	}

	if (comprs_str(".", dir) == 0 || comprs_str("..", dir) == 0)
	{
		shl_cd_dot(shl_data_shll);
		return (1);
	}

	shl_cd_to(shl_data_shll);

	return (1);
}
