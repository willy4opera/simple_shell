#include "devshell.h"

/**
 * shl_help_env - Helper info for the builtin env
 * Return: void
 */
void shl_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, line_str(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, line_str(help));

}
/**
 * shl_help_setenv - Helper information for the builtin setenv
 * Return: Non
 */
void shl_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, line_str(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, line_str(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, line_str(help));
}
/**
 * shl_help_unsetenv - elp info for the builtin unseteenv
 * Return: void
 */
void shl_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, line_str(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, line_str(help));
}


/**
 * shl_help_general - Entry point for helper info for the help builtin
 * Return: void
 */
void shl_help_general(void)
{
	char *help = "shl_Shell$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, line_str(help));
	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, line_str(help));
	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, line_str(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, line_str(help));
	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, line_str(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, line_str(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, line_str(help));
}
/**
 * shl_help_exit - Helper info for the builtint exit
 * Return: void
 */
void shl_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, line_str(help));
	help = "Exits the shell with a stat of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, line_str(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, line_str(help));
}

