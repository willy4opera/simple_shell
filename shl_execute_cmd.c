#include "devshell.h"

/**
 * shl_is_cdir - checks ":" if is in the current directory.
 * @fpath: type char pointer char.
 * @count: type int pointer of index.
 * Return: 1 if the fpath is searchable in the cd, 0 otherwise.
 */
int shl_is_cdir(char *fpath, int *count)
{
	if (fpath[*count] == ':')
		return (1);

	while (fpath[*count] != ':' && fpath[*count])
	{
		*count += 1;
	}

	if (fpath[*count])
		*count += 1;

	return (0);
}

/**
 * shl_cmd_loc - locates a command
 *
 * @cmd: command name
 * @envr_var: environment variable
 * Return: location of the command.
 */
char *shl_cmd_loc(char *cmd, char **envr_var)
{
	char *fpath, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, count;
	struct stat st;

	fpath = _getenv("fpath", envr_var);
	if (fpath)
	{
		ptr_path = shl_strdup(fpath);
		len_cmd = line_str(cmd);
		token_path = shl_strtok(ptr_path, ":");
		count = 0;
		while (token_path != NULL)
		{
			if (shl_is_cdir(fpath, &count))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = line_str(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			strng_copy(dir, token_path);
			strng_cat(dir, "/");
			strng_cat(dir, cmd);
			strng_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = shl_strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * shl_is_executable - determines if is an executable
 *
 * @shl_data_shll: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int shl_is_executable(shll_data_t *shl_data_shll)
{
	struct stat st;
	int count;
	char *cli_inpt;

	cli_inpt = shl_data_shll->arg_cli[0];
	for (count = 0; cli_inpt[count]; count++)
	{
		if (cli_inpt[count] == '.')
		{
			if (cli_inpt[count + 1] == '.')
				return (0);
			if (cli_inpt[count + 1] == '/')
				continue;
			else
				break;
		}
		else if (cli_inpt[count] == '/' && count != 0)
		{
			if (cli_inpt[count + 1] == '.')
				continue;
			count++;
			break;
		}
		else
			break;
	}
	if (count == 0)
		return (0);

	if (stat(cli_inpt + count, &st) == 0)
	{
		return (count);
	}
	shl_get_error(shl_data_shll, 127);
	return (-1);
}

/**
 * shl_chk_err_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @shl_data_shll: data structure
 * Return: 1 if there is an error, 0 if not
 */
int shl_chk_err_cmd(char *dir, shll_data_t *shl_data_shll)
{
	if (dir == NULL)
	{
		shl_get_error(shl_data_shll, 127);
		return (1);
	}

	if (comprs_str(shl_data_shll->arg_cli[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			shl_get_error(shl_data_shll, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shl_data_shll->arg_cli[0], X_OK) == -1)
		{
			shl_get_error(shl_data_shll, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * shl_cmd_exec - executes command lines
 *
 * @shl_data_shll: data relevant (args and cli_inpt)
 * Return: 1 on success.
 */
int shl_cmd_exec(shll_data_t *shl_data_shll)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = shl_is_executable(shl_data_shll);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = shl_cmd_loc(shl_data_shll->arg_cli[0], shl_data_shll->envr_var);
		if (shl_chk_err_cmd(dir, shl_data_shll) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = shl_cmd_loc(shl_data_shll->arg_cli[0], shl_data_shll->envr_var);
		else
			dir = shl_data_shll->arg_cli[0];
		execve(dir + exec, shl_data_shll->arg_cli, shl_data_shll->envr_var);
	}
	else if (pd < 0)
	{
		perror(shl_data_shll->arg_var[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shl_data_shll->stat = state / 256;
	return (1);
}
