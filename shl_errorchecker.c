#include "devshell.h"

/**
 * shl_repeated_char - counts the repetitions of a char
 *
 * @cli_inpt: cli_inpt string
 * @count: index
 * Return: repetitions
 */
int shl_repeated_char(char *cli_inpt, int count)
{
	if (*(cli_inpt - 1) == *cli_inpt)
		return (shl_repeated_char(cli_inpt - 1, count + 1));

	return (count);
}

/**
 * shl_error_sep - finds syntax errors
 *
 * @cli_inpt: cli_inpt string
 * @count: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int shl_error_sep(char *cli_inpt, int count, char last)
{
	int cnt;

	cnt = 0;
	if (*cli_inpt == '\0')
		return (0);

	if (*cli_inpt == ' ' || *cli_inpt == '\t')
		return (shl_error_sep(cli_inpt + 1, count + 1, last));

	if (*cli_inpt == ';')
		if (last == '|' || last == '&' || last == ';')
			return (count);

	if (*cli_inpt == '|')
	{
		if (last == ';' || last == '&')
			return (count);

		if (last == '|')
		{
			cnt = shl_repeated_char(cli_inpt, 0);
			if (cnt == 0 || cnt > 1)
				return (count);
		}
	}

	if (*cli_inpt == '&')
	{
		if (last == ';' || last == '|')
			return (count);

		if (last == '&')
		{
			cnt = shl_repeated_char(cli_inpt, 0);
			if (cnt == 0 || cnt > 1)
				return (count);
		}
	}

	return (shl_error_sep(cli_inpt + 1, count + 1, *cli_inpt));
}

/**
 * shl_first_char - finds index of the first char
 *
 * @cli_inpt: cli_inpt string
 * @count: index
 * Return: 1 if there is an error. 0 in other case.
 */
int shl_first_char(char *cli_inpt, int *count)
{

	for (*count = 0; cli_inpt[*count]; *count += 1)
	{
		if (cli_inpt[*count] == ' ' || cli_inpt[*count] == '\t')
			continue;

		if (cli_inpt[*count] == ';' || cli_inpt[*count] == '|' ||
				cli_inpt[*count] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 *err_sntx - prints when a syntax error is found
 *
 * @shl_data_shll: data structure
 * @cli_inpt: cli_inpt string
 * @count: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void err_sntx(shll_data_t *shl_data_shll,
		char *cli_inpt, int count, int bool)
{
	char *message, *message2, *message3, *error, *ln_cntr;
	int leng;

	if (cli_inpt[count] == ';')
	{
		if (bool == 0)
			message = (cli_inpt[count + 1] == ';' ? ";;" : ";");
		else
			message = (cli_inpt[count - 1] == ';' ? ";;" : ";");
	}

	if (cli_inpt[count] == '|')
		message = (cli_inpt[count + 1] == '|' ? "||" : "|");

	if (cli_inpt[count] == '&')
		message = (cli_inpt[count + 1] == '&' ? "&&" : "&");

	message2 = ": Syntax error: \"";
	message3 = "\" unexpected\n";
	ln_cntr = shl_get_itos(shl_data_shll->ln_cntr);
	leng = line_str(shl_data_shll->arg_var[0]) + line_str(ln_cntr);
	leng += line_str(message) + line_str(message2) + line_str(message3) + 2;

	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(ln_cntr);
		return;
	}
	strng_copy(error, shl_data_shll->arg_var[0]);
	strng_cat(error, ": ");
	strng_cat(error, ln_cntr);
	strng_cat(error, message2);
	strng_cat(error, message);
	strng_cat(error, message3);
	strng_cat(error, "\0");

	write(STDERR_FILENO, error, leng);
	free(error);
	free(ln_cntr);
}

/**
 * shl_check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @shl_data_shll: data structure
 * @cli_inpt: cli_inpt string
 * Return: 1 if there is an error. 0 in other case
 */
int shl_check_syntax_error(shll_data_t *shl_data_shll, char *cli_inpt)
{
	int begin = 0;
	int f_char = 0;
	int count = 0;

	f_char = shl_first_char(cli_inpt, &begin);
	if (f_char == -1)
	{
		err_sntx(shl_data_shll, cli_inpt, begin, 0);
		return (1);
	}

	count = shl_error_sep(cli_inpt + begin, 0, *(cli_inpt + begin));
	if (count != 0)
	{
		err_sntx(shl_data_shll, cli_inpt, begin + count, 1);
		return (1);
	}

	return (0);
}
