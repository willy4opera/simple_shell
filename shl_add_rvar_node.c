#include "devshell.h"

/**
 * shl_add_rvar_node - adds a variable at the end a shllvar_t list.
 * @head: head of the linked list.
 * @lvar: leng of the variable.
 * @var_val: value of the variable.
 * @lval: leng of the value.
 * Return: head address.
 */
shllvar_t *shl_add_rvar_node(shllvar_t **head, int lvar, char *var_val, int lval)
{
	shllvar_t *nw, *temp;

	nw = malloc(sizeof(shllvar_t));
	if (nw == NULL)
		return (NULL);

	nw->var_lent = lvar;
	nw->var_val = var_val;
	nw->value_length = lval;

	nw->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = nw;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nw;
	}

	return (*head);
}

/**
 * shl_dev_var_list - free a shllvar_t list
 * @head: head of the linked list.
 * Return: void.
 */
void shl_dev_var_list(shllvar_t **head)
{
	shllvar_t *temp;
	shllvar_t *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

