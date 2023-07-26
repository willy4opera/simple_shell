#include "devshell.h"

/**
 * shl_check_env - checks if variable is an env variable
 * @h: linked list head
 * @in: input string
 * @data: data structure
 * Return: void
 */
void shl_check_env(shllvar_t **h, char *in, shll_data_t *data)
{
	int row, chrr, numb, list_v;
	char **_envrr;

	_envrr = data->envr_var;
	for (row = 0; _envrr[row]; row++)
	{
		for (numb = 1, chrr = 0; _envrr[row][chrr]; chrr++)
		{
			if (_envrr[row][chrr] == '=')
			{
				list_v = line_str(_envrr[row] + chrr + 1);
				shl_add_rvar_node(h, numb, _envrr[row] + chrr + 1, list_v);
				return;
			}

			if (in[numb] == _envrr[row][chrr])
				numb++;
			else
				break;
		}
	}

	for (numb = 0; in[numb]; numb++)
	{
		if (in[numb] == ' ' || in[numb] == '\t' || in[numb]
				== ';' || in[numb] == '\n')
			break;
	}

	shl_add_rvar_node(h, numb, NULL, 0);
}

/**
 * shl_check_vars - check if the typed variable is $$ or $?
 * @h: linked list head
 * @in: input string
 * @st: last stat of the Shell
 * @data: data structure
 * Return: void
 */
int shl_check_vars(shllvar_t **h, char *in, char *st, shll_data_t *data)
{
	int i, lst, lpd;

	lst = line_str(st);
	lpd = line_str(data->shell_pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				shl_add_rvar_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				shl_add_rvar_node(h, 2, data->shell_pid, lpd), i++;
			else if (in[i + 1] == '\n')
				shl_add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				shl_add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				shl_add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				shl_add_rvar_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				shl_add_rvar_node(h, 0, NULL, 0);
			else
				shl_check_env(h, in + i, data);
		}
	}

	return (i);
}

/**
 * inpu_rplc - replaces string to variables
 * @head: head of the linked list
 * @cli_inpt: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *inpu_rplc(shllvar_t **head, char *cli_inpt, char *new_input, int nlen)
{
	shllvar_t *indx;
	int i, numb, k;

	indx = *head;
	for (numb = i = 0; i < nlen; i++)
	{
		if (cli_inpt[numb] == '$')
		{
			if (!(indx->var_lent) && !(indx->value_length))
			{
				new_input[i] = cli_inpt[numb];
				numb++;
			}
			else if (indx->var_lent && !(indx->value_length))
			{
				for (k = 0; k < indx->var_lent; k++)
					numb++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->value_length; k++)
				{
					new_input[i] = indx->var_val[k];
					i++;
				}
				numb += (indx->var_lent);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = cli_inpt[numb];
			numb++;
		}
	}

	return (new_input);
}

/**
 * shl_rep_var - calls func to replace string into vars
 * @cli_inpt: input string
 * @shl_data_shll: data structure
 * Return: replaced string
 */
char *shl_rep_var(char *cli_inpt, shll_data_t *shl_data_shll)
{
	shllvar_t *head, *indx;
	char *stat, *new_input;
	int olen, nlen;

	stat = shl_get_itos(shl_data_shll->stat);
	head = NULL;

	olen = shl_check_vars(&head, cli_inpt, stat, shl_data_shll);

	if (head == NULL)
	{
		free(stat);
		return (cli_inpt);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->value_length - indx->var_lent);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';


	new_input = inpu_rplc(&head, cli_inpt, new_input, nlen);

	free(cli_inpt);
	free(stat);
	shl_dev_var_list(&head);

	return (new_input);
}

