#include "devshell.h"

/**
 * shl_comment_check - deletes comments from the input
 * @in: input string
 * Return: input without comments
 */
char *shl_comment_check(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = shl_realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shl_loop_shell - Loop of shell
 * @shl_data_shll: data relevant (av, input, args)
 * Return: no return.
 */
void shl_loop_shell(shll_data_t *shl_data_shll)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "Dev$ ", 5);
		input = shl_rd_line(&i_eof);
		if (i_eof != -1)
		{
			input = shl_comment_check(input);
			if (input == NULL)
				continue;

			if (shl_check_syntax_error(shl_data_shll, input) == 1)
			{
				shl_data_shll->stat = 2;
				free(input);
				continue;
			}
			input = shl_rep_var(input, shl_data_shll);
			loop = cmd_split(shl_data_shll, input);
			shl_data_shll->ln_cntr += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

