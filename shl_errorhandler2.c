#include "devshell.h"

/**
 * shl_error_env - error message for env in get_env.
 * @shl_data_shll: data relevant (ln_cntr, arguments)
 * Return: error message.
 */
char *shl_error_env(shll_data_t *shl_data_shll)
{
	int leng;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = shl_get_itos(shl_data_shll->ln_cntr);
	msg = ": Unable to add/remove from environment\n";
	leng = line_str(shl_data_shll->arg_var[0]) + line_str(ver_str);
	leng += line_str(shl_data_shll->arg_cli[0]) + line_str(msg) + 4;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	strng_copy(error, shl_data_shll->arg_var[0]);
	strng_cat(error, ": ");
	strng_cat(error, ver_str);
	strng_cat(error, ": ");
	strng_cat(error, shl_data_shll->arg_cli[0]);
	strng_cat(error, msg);
	strng_cat(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * shl_error_path - error message for fpath and failure denied permission.
 * @shl_data_shll: data relevant (ln_cntr, arguments).
 *
 * Return: The error string.
 */
char *shl_error_path(shll_data_t *shl_data_shll)
{
	int leng;
	char *ver_str;
	char *error;

	ver_str = shl_get_itos(shl_data_shll->ln_cntr);
	leng = line_str(shl_data_shll->arg_var[0]) + line_str(ver_str);
	leng += line_str(shl_data_shll->arg_cli[0]) + 24;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	strng_copy(error, shl_data_shll->arg_var[0]);
	strng_cat(error, ": ");
	strng_cat(error, ver_str);
	strng_cat(error, ": ");
	strng_cat(error, shl_data_shll->arg_cli[0]);
	strng_cat(error, ": Permission denied\n");
	strng_cat(error, "\0");
	free(ver_str);
	return (error);
}
