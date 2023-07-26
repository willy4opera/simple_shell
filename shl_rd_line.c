#include "devshell.h"

/**
 * shl_rd_line - reads cli_inpt string.
 * @i_eof: returns envr_val of getline function.
 * Return: cli_inpt string.
 */
char *shl_rd_line(int *i_eof)
{
	char *cli_inpt = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&cli_inpt, &bufsize, stdin);

	return (cli_inpt);
}
