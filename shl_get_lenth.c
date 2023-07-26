#include "devshell.h"

/**
 * shl_get_lenth - Get the len of a num
 * @n: type int number.
 * Return: Len of a number.
 */
int shl_get_lenth(int n)
{
	unsigned int num1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		num1 = n * -1;
	}
	else
	{
		num1 = n;
	}
	while (num1 > 9)
	{
		lenght++;
		num1 = num1 / 10;
	}

	return (lenght);
}
/**
 * shl_get_itos - func converts int to string.
 * @n: type int number
 * Return: String.
 */
char *shl_get_itos(int n)
{
	unsigned int num1;
	int lenght = shl_get_lenth(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		num1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (num1 % 10) + '0';
		num1 = num1 / 10;
		lenght--;
	}
	while (num1 > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @ strng: cli_inpt string.
 * Return: integer.
 */
int _atoi(char *strng)
{
	unsigned int count = 0, size = 0, un_int = 0, p_num = 1, m_n = 1, cnt;

	while (*(strng + count) != '\0')
	{
		if (size > 0 && (*(strng + count) < '0' || *(strng + count) > '9'))
			break;

		if (*(strng + count) == '-')
			p_num *= -1;

		if ((*(strng + count) >= '0') && (*(strng + count) <= '9'))
		{
			if (size > 0)
				m_n *= 10;
			size++;
		}
		count++;
	}

	for (cnt = count - size; cnt < count; cnt++)
	{
		un_int = un_int + ((*(strng + cnt) - 48) * m_n);
		m_n /= 10;
	}
	return (un_int * p_num);
}

