#include "devshell.h"

/**
 * shl_bg_lne - assigns the line var for shl_get_line
 * @liner_ptr: Buffer that store the cli_inpt str
 * @buffer: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */
void shl_bg_lne(char **liner_ptr, size_t *n, char *buffer, size_t j)
{

	if (*liner_ptr == NULL)
	{
		if  (j > BUFFER_SIZE)
			*n = j;

		else
			*n = BUFFER_SIZE;
		*liner_ptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFFER_SIZE)
			*n = j;
		else
			*n = BUFFER_SIZE;
		*liner_ptr = buffer;
	}
	else
	{
		strng_copy(*liner_ptr, buffer);
		free(buffer);
	}
}
/**
 * shl_get_line - Read inpt from stream
 * @liner_ptr: buffer that stores the cli_inpt
 * @n: size of liner_ptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t shl_get_line(char **liner_ptr, size_t *n, FILE *stream)
{
	int count;
	static ssize_t cli_inpt;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (cli_inpt == 0)
		fflush(stream);
	else
		return (-1);
	cli_inpt = 0;

	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		count = read(STDIN_FILENO, &t, 1);
		if (count == -1 || (count == 0 && cli_inpt == 0))
		{
			free(buffer);
			return (-1);
		}
		if (count == 0 && cli_inpt != 0)
		{
			cli_inpt++;
			break;
		}
		if (cli_inpt >= BUFFER_SIZE)
			buffer = shl_realloc(buffer, cli_inpt, cli_inpt + 1);
		buffer[cli_inpt] = t;
		cli_inpt++;
	}
	buffer[cli_inpt] = '\0';
	shl_bg_lne(liner_ptr, n, buffer, cli_inpt);
	retval = cli_inpt;
	if (count != 0)
		cli_inpt = 0;
	return (retval);
}
