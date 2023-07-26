#include "devshell.h"

/**
 * shl_char_swap - swaps | and & to non-printed char
 * @cli_inpt: cli_inpt string
 * @bool: type of swap
 * Return: swapped string
 */
char *shl_char_swap(char *cli_inpt, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; cli_inpt[i]; i++)
		{
			if (cli_inpt[i] == '|')
			{
				if (cli_inpt[i + 1] != '|')
					cli_inpt[i] = 16;
				else
					i++;
			}

			if (cli_inpt[i] == '&')
			{
				if (cli_inpt[i + 1] != '&')
					cli_inpt[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; cli_inpt[i]; i++)
		{
			cli_inpt[i] = (cli_inpt[i] == 16 ? '|' : cli_inpt[i]);
			cli_inpt[i] = (cli_inpt[i] == 12 ? '&' : cli_inpt[i]);
		}
	}
	return (cli_inpt);
}

/**
 * nds_ad - add separators and command lines in the lists
 * @head_s: head of she_sept list
 * @head_l: head of command lines list
 * @cli_inpt: cli_inpt string
 * Return: no return
 */
void nds_ad(strngls_sp **head_s, list_t **head_l, char *cli_inpt)
{
	int i;
	char *cmd_line;

	cli_inpt = shl_char_swap(cli_inpt, 0);

	for (i = 0; cli_inpt[i]; i++)
	{
		if (cli_inpt[i] == ';')
			shl_sep_add_node_end(head_s, cli_inpt[i]);

		if (cli_inpt[i] == '|' || cli_inpt[i] == '&')
		{
			shl_sep_add_node_end(head_s, cli_inpt[i]);
			i++;
		}
	}

	cmd_line = shl_strtok(cli_inpt, ";|&");
	do {
		cmd_line = shl_char_swap(cmd_line, 1);
		shl_add_line_node_end(head_l, cmd_line);
		cmd_line = shl_strtok(NULL, ";|&");
	} while (cmd_line != NULL);

}

/**
 * nxgn - go to the next command cmd_line stored
 * @list_s: she_sept list
 * @list_l: command cmd_line list
 * @shl_data_shll: data structure
 * Return: no return
 */
void nxgn(strngls_sp **list_s, list_t **list_l, shll_data_t *shl_data_shll)
{
	int loop_sep;
	strngls_sp *ls_s;
	list_t *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shl_data_shll->stat == 0)
		{
			if (ls_s->she_sept == '&' || ls_s->she_sept == ';')
				loop_sep = 0;
			if (ls_s->she_sept == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->she_sept == '|' || ls_s->she_sept == ';')
				loop_sep = 0;
			if (ls_s->she_sept == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * cmd_split - splits command lines according to
 * the separators ;, | and &, and executes them
 * @shl_data_shll: data structure
 * @cli_inpt: cli_inpt string
 * Return: 0 to exit, 1 to continue
 */
int cmd_split(shll_data_t *shl_data_shll, char *cli_inpt)
{

	strngls_sp *head_s, *list_s;
	list_t *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	nds_ad(&head_s, &head_l, cli_inpt);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shl_data_shll->cli_inpt = list_l->cmd_line;
		shl_data_shll->arg_cli = shl_split_line(shl_data_shll->cli_inpt);
		loop = shl_exec_line(shl_data_shll);
		free(shl_data_shll->arg_cli);

		if (loop == 0)
			break;

		nxgn(&list_s, &list_l, shl_data_shll);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	shl_free_sep_list(&head_s);
	shl_free_line_list(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * shl_split_line - tokenizes the cli_inpt string
 * @cli_inpt: cli_inpt string.
 * Return: string splitted.
 */
char **shl_split_line(char *cli_inpt)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = shl_strtok(cli_inpt, TOKEN_DLIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOKEN_BUFFER_SIZE;
			tokens = shl_reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = shl_strtok(NULL, TOKEN_DLIM);
		tokens[i] = token;
	}

	return (tokens);

}

