#include "devshell.h"

/**
 * shl_helper - Help info for the builtin help.
 * Return: void
 */
void shl_helper(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, line_str(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, line_str(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, line_str(help));
}
/**
 * shl_helper_al - Help info for the builtin alias.
 * Return: void
 */
void shl_helper_al(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, line_str(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, line_str(help));
}
/**
 * shl_helper_cd - Help info the builtin alias.
 * Return: void
 */
void shl_helper_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, line_str(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, line_str(help));
}

