#include "devshell.h"

/**
 * shl_memcpy - copies info between void pointers.
 * @new_ptr: dest pointer.
 * @ptr: source pointer.
 * @size: size of the nw pointer.
 * Return: no return.
 */
void shl_memcpy(void *new_ptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)new_ptr;
	unsigned int count;

	for (count = 0; count < size; count++)
		char_newptr[count] = char_ptr[count];
}

/**
 * shl_realloc - realloc a memory block.
 * @ptr: pointer to mem previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: nw size, in bytes, of the new memory block.
 * Return: ptr.
 * if new_size == old_size,returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *shl_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		shl_memcpy(new_ptr, ptr, new_size);
	else
		shl_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}

/**
 * shl_reallocdp - realloc a memory block of a double pointer
 * @ptr: double pointer to the mem previously allocated
 * @old_size: size, in bytes, of the allocated space of ptr
 * @new_size: new size, in bytes, of the new memory block
 * Return: ptr
 * if new_size == old_size, returns ptr without changes
 * if malloc fails, returns NULL.
 */
char **shl_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **new_ptr;
	unsigned int count;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (count = 0; count < old_size; count++)
		new_ptr[count] = ptr[count];

	free(ptr);

	return (new_ptr);
}

