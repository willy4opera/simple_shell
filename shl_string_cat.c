#include "devshell.h"

/**
 * strng_cat - concatenate two strings
 * @destination: char pointer the destination of the copied str
 * @source: const char pointer the source of str
 * Return: the destination
 */
char *strng_cat(char *destination, const char *source)
{
	int count;
	int j;

	for (count = 0; destination[count] != '\0'; count++)
		;

	for (j = 0; source[j] != '\0'; j++)
	{
		destination[count] = source[j];
		count++;
	}

	destination[count] = '\0';
	return (destination);
}
/**
 * *strng_copy - Copies the string pointed to by source.
 * @destination: Type char pointer the destination of the copied str
 * @source: Type char pointer the source of str
 * Return: the destination.
 */
char *strng_copy(char *destination, char *source)
{

	size_t a;

	for (a = 0; source[a] != '\0'; a++)
	{
		destination[a] = source[a];
	}
	destination[a] = '\0';

	return (destination);
}
/**
 * comprs_str - Function that compares two strings.
 * @string1: type str compared
 * @string2: type str compared
 * Return: Always 0.
 */
int comprs_str(char *string1, char *string2)
{
	int count;

	for (count = 0; string1[count] == string2[count] && string1[count]; count++)
		;

	if (string1[count] > string2[count])
		return (1);
	if (string1[count] < string2[count])
		return (-1);
	return (0);
}
/**
 * sh_chtost - locates a character in a string,
 * @strng: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *sh_chtost(char *strng, char c)
{
	unsigned int count = 0;

	for (; *(strng + count) != '\0'; count++)
		if (*(strng + count) == c)
			return (strng + count);
	if (*(strng + count) == c)
		return (strng + count);
	return ('\0');
}
/**
 * shl_strspn - gets the leng of a prefix substring.
 * @strng: initial segment.
 * @accept: accepted bytes.
 * Return: the number of accepted bytes.
 */
int shl_strspn(char *strng, char *accept)
{
	int count, j, bool;

	for (count = 0; *(strng + count) != '\0'; count++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(strng + count) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (count);
}
