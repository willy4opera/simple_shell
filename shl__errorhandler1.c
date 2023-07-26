#include "devshell.h"

/**
 * cd_stcat - function that concatenates the message for cd error
 *
 * @shl_data_shll: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: ln_cntr lines
 * Return: error message
 */
char *cd_stcat(shll_data_t *shl_data_shll, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	strng_copy(error, shl_data_shll->arg_var[0]);
	strng_cat(error, ": ");
	strng_cat(error, ver_str);
	strng_cat(error, ": ");
	strng_cat(error, shl_data_shll->arg_cli[0]);
	strng_cat(error, msg);
	if (shl_data_shll->arg_cli[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shl_data_shll->arg_cli[1][1];
		illegal_flag[2] = '\0';
		strng_cat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		strng_cat(error, shl_data_shll->arg_cli[1]);
	}

	strng_cat(error, "\n");
	strng_cat(error, "\0");
	return (error);
}

/**
 * shl_cd_get_error - error message for cd command in get_cd
 * @shl_data_shll: data relevant (directory)
 * Return: Error message
 */
char *shl_cd_get_error(shll_data_t *shl_data_shll)
{
	int leng, len_id;
	char *error, *ver_str, *msg;

	ver_str = shl_get_itos(shl_data_shll->ln_cntr);
	if (shl_data_shll->arg_cli[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = line_str(shl_data_shll->arg_cli[1]);
	}

	leng = line_str(shl_data_shll->arg_var[0]) + line_str(shl_data_shll->arg_cli[0]);
	leng += line_str(ver_str) + line_str(msg) + len_id + 5;
	error = malloc(sizeof(char) * (leng + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = cd_stcat(shl_data_shll, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * shl_error_nf - generic error message for command not found
 * @shl_data_shll: data relevant (ln_cntr, arguments)
 * Return: Error message
 */
char *shl_error_nf(shll_data_t *shl_data_shll)
{
	int leng;
	char *error;
	char *ver_str;

	ver_str = shl_get_itos(shl_data_shll->ln_cntr);
	leng = line_str(shl_data_shll->arg_var[0]) + line_str(ver_str);
	leng += line_str(shl_data_shll->arg_cli[0]) + 16;
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
	strng_cat(error, ": not found\n");
	strng_cat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * shl_exit_shell_on_error - generic error message for exit in get_exit
 * @shl_data_shll: data relevant (ln_cntr, arguments)
 *
 * Return: Error message
 */
char *shl_exit_shell_on_error(shll_data_t *shl_data_shll)
{
	int leng;
	char *error;
	char *ver_str;

	ver_str = shl_get_itos(shl_data_shll->ln_cntr);
	leng = line_str(shl_data_shll->arg_var[0]) + line_str(ver_str);
	leng += line_str(shl_data_shll->arg_cli[0]) +
		line_str(shl_data_shll->arg_cli[1]) + 23;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	strng_copy(error, shl_data_shll->arg_var[0]);
	strng_cat(error, ": ");
	strng_cat(error, ver_str);
	strng_cat(error, ": ");
	strng_cat(error, shl_data_shll->arg_cli[0]);
	strng_cat(error, ": Illegal number: ");
	strng_cat(error, shl_data_shll->arg_cli[1]);
	strng_cat(error, "\n\0");
	free(ver_str);

	return (error);
}
