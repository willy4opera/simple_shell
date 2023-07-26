#include "devshell.h"

/**
 * shl_get_sigint - Handle the crtl + c call in prompt
 * @signal_h: Signal handler
 */
void shl_get_sigint(int signal_h)
{
	(void)signal_h;
	write(STDOUT_FILENO, "\nshl_Shell$ ", 5);
}
