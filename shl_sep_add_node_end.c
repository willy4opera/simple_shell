#include "devshell.h"

/**
 * shl_sep_add_node_end - adds separator found at the end ofstrngls_sp.
 * @head: head of linked list
 * @sep: separator found (; | &)
 * Return: head address.
 */
strngls_sp *shl_sep_add_node_end(strngls_sp **head, char sep)
{
	strngls_sp *nw, *temp;

	nw = malloc(sizeof(strngls_sp));
	if (nw == NULL)
		return (NULL);

	nw->she_sept = sep;
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
 * shl_free_sep_list - free a strngls_sp
 * @head: head of the linked list.
 * Return: void
 */
void shl_free_sep_list(strngls_sp **head)
{
	strngls_sp *temp;
	strngls_sp *curr;

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

/**
 * shl_add_line_node_end - returns commandline at the end.
 * of a list_t
 * @head: head of the linked list
 * @cmd_line: commandline.
 * Return: address of the head.
 */
list_t *shl_add_line_node_end(list_t **head, char *cmd_line)
{
	list_t *nw, *temp;

	nw = malloc(sizeof(list_t));
	if (nw == NULL)
		return (NULL);

	nw->cmd_line = cmd_line;
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
 * shl_free_line_list - frees a list_t
 * @head: head of the linked list.
 * Return: void
 */
void shl_free_line_list(list_t **head)
{
	list_t *temp;
	list_t *curr;

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

