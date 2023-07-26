#include "devshell.h"

/**
 * shl_strdup - duplicates a str in heap memory.
 * @strng: Type char pointer str
 * Return: duplicated str
 */
char *shl_strdup(const char *strng)
{
	char *nw;
	size_t len;

	len = line_str(strng);
	nw = malloc(sizeof(char) * (len + 1));
	if (nw == NULL)
		return (NULL);
	shl_memcpy(nw,  strng, len + 1);
	return (nw);
}

/**
 * line_str - Returns the len of a string.
 * @strng: Type char pointer
 * Return: Always 0.
 */
int line_str(const char *strng)
{
	int len;

	for (len = 0;  strng[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * shl_cmp_chars - compare chars of strings
 * @str: cli_inpt string.
 * @dlim: delimiter.
 * Return: 1 if are equals else 0
 */
int shl_cmp_chars(char str[], const char *dlim)
{
	unsigned int count, num1, num2;

	for (count = 0, num2 = 0; str[count]; count++)
	{
		for (num1 = 0; dlim[num1]; num1++)
		{
			if (str[count] == dlim[num1])
			{
				num2++;
				break;
			}
		}
	}
	if (count == num2)
		return (1);
	return (0);
}

/**
 * shl_strtok - splits a string by some delimiter.
 * @str: cli_inpt string.
 * @dlim: delimiter.
 * Return: string splited.
 */
char *shl_strtok(char str[], const char *dlim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int count, bool;

	if (str != NULL)
	{
		if (shl_cmp_chars(str, dlim))
			return (NULL);
		splitted = str; /*Store first address*/
		count = line_str(str);
		str_end = &str[count]; /*Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop finding the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (count = 0; dlim[count]; count++)
		{
			if (*splitted == dlim[count])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != dlim*/
			bool = 1;
	}
	if (bool == 0) /*Str == dlim*/
		return (NULL);
	return (str_start);
}

/**
 * shl_isdigit - defines if string passed is a number
 * @strng: cli_inpt string
 * Return: 1 if string is a number. 0 in other case.
 */
int shl_isdigit(const char *strng)
{
	unsigned int count;

	for (count = 0;  strng[count]; count++)
	{
		if (strng[count] < 48 ||  strng[count] > 57)
			return (0);
	}
	return (1);
}
