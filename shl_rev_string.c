#include "devshell.h"

/**
 * shl_rev_string - reverses a string.
 * @strng: cli_inpt string.
 * Return: void.
 */
void shl_rev_string(char *strng)
{
	int count = 0, cnt, num1;
	char *str, temp;

	while (count >= 0)
	{
		if (strng[count] == '\0')
			break;
		count++;
	}
	str =  strng;

	for (cnt = 0; cnt < (count - 1); cnt++)
	{
		for (num1 = count + 1; num1 > 0; num1--)
		{
			temp = *(str + num1);
			*(str + num1) = *(str + (num1 - 1));
			*(str + (num1 - 1)) = temp;
		}
	}
}

