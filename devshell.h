#ifndef _DEVALX_
#define _DEVALX_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 128
#define TOKEN_DLIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @arg_var: argument vector
 * @cli_inpt: command line written by the user
 * @arg_cli: tokens of the command line
 * @stat: last stat of the shell
 * @ln_cntr: lines ln_cntr
 * @envr_var: environment variable
 * @shell_pid: process ID of the shell
 */
typedef struct data
{
	char **arg_var;
	char *cli_inpt;
	char **arg_cli;
	int stat;
	int ln_cntr;
	char **envr_var;
	char *shell_pid;
} shll_data_t;

/**
 * struct spt_list - single linked list
 * @she_sept: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct spt_list
{
	char she_sept;
	struct spt_list *next;
} strngls_sp;

/**
 * struct ln_ls_string - single linked list
 * @cmd_line: command cmd_line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct ln_ls_string
{
	char *cmd_line;
	struct ln_ls_string *next;
} list_t;

/**
 * struct sn_link_list - single linked list
 * @var_lent: leng of the variable
 * @var_val: value of the variable
 * @value_length: leng of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct sn_link_list
{
	int var_lent;
	char *var_val;
	int value_length;
	struct sn_link_list *next;
} shllvar_t;

/**
 * struct builtin_struct - Builtin struct for command args.
 * @cmd_nm: The cmd_nm of the command builtin count.e cd, exit, env
 * @d_pointr_f: data type pointer function.
 */
typedef struct builtin_struct
{
	char *cmd_nm;
	int (*d_pointr_f)(shll_data_t *shl_data_shll);
} btstruct_t;

/* shl_aux_list.c */
strngls_sp *shl_sep_add_node_end(strngls_sp **head, char sep);
void shl_free_sep_list(strngls_sp **head);
list_t *shl_add_line_node_end(list_t **head, char *cmd_line);
void shl_free_line_list(list_t **head);

/* shl_aux_lists2.c */
shllvar_t *shl_add_rvar_node(shllvar_t **head, int lvar, char *var, int lval);
void shl_dev_var_list(shllvar_t **head);

/* shl_aux_str functions */
char *strng_cat(char *destination, const char *source);
char *strng_copy(char *destination, char *source);
int comprs_str(char *string1, char *string2);
char *sh_chtost(char *strng, char c);
int shl_strspn(char *strng, char *accept);

/* shl_aux_mem.c */
void shl_memcpy(void *new_ptr, const void *ptr, unsigned int size);
void *shl_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **shl_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* shl_aux_str2.c */
char *shl_strdup(const char *strng);
int line_str(const char *strng);
int shl_cmp_chars(char str[], const char *dlim);
char *shl_strtok(char str[], const char *dlim);
int shl_isdigit(const char *strng);

/* shl_aux_str3.c */
void shl_rev_string(char *strng);

/* shl_check_syntax_error.c */
int shl_repeated_char(char *cli_inpt, int count);
int shl_error_sep(char *cli_inpt, int count, char last);
int shl_first_char(char *cli_inpt, int *count);
void err_sntx(shll_data_t *shl_data_shll, char *cli_inpt, int count, int bool);
int shl_check_syntax_error(shll_data_t *shl_data_shll, char *cli_inpt);

/* shl_shell_loop.c */
char *shl_comment_check(char *in);
void shl_loop_shell(shll_data_t *shl_data_shll);

/* shl_rd_line.c */
char *shl_rd_line(int *i_eof);

/* shl_split.c */
char *shl_char_swap(char *cli_inpt, int bool);
void nds_ad(strngls_sp **head_s, list_t **head_l, char *cli_inpt);
void nxgn(strngls_sp **list_s, list_t **list_l, shll_data_t *shl_data_shll);
int cmd_split(shll_data_t *shl_data_shll, char *cli_inpt);
char **shl_split_line(char *cli_inpt);

/* shl_rep_var.c */
void shl_check_env(shllvar_t **h, char *in, shll_data_t *data);
int shl_check_vars(shllvar_t **h, char *in, char *st, shll_data_t *data);
char *inpu_rplc(shllvar_t **head, char *cli_inpt, char *new_input, int nlen);
char *shl_rep_var(char *cli_inpt, shll_data_t *shl_data_shll);

/* shl_get_line.c */
void shl_bg_lne(char **liner_ptr, size_t *n, char *buffer, size_t j);
ssize_t shl_get_line(char **liner_ptr, size_t *n, FILE *stream);

/* shl_exec_line */
int shl_exec_line(shll_data_t *shl_data_shll);

/* shl_cmd_exec.c */
int shl_is_cdir(char *fpath, int *count);
char *shl_cmd_loc(char *cmd, char **envr_var);
int shl_is_executable(shll_data_t *shl_data_shll);
int shl_chk_err_cmd(char *dir, shll_data_t *shl_data_shll);
int shl_cmd_exec(shll_data_t *shl_data_shll);

/* shl_env1.c */
char *_getenv(const char *cmd_nm, char **envr_var);
int _env(shll_data_t *shl_data_shll);

/* shl_env2.c */
char *copy_info(char *cmd_nm, char *envr_val);
void set_env(char *cmd_nm, char *envr_val, shll_data_t *shl_data_shll);
int _setenv(shll_data_t *shl_data_shll);
int _unsetenv(shll_data_t *shl_data_shll);

/* cd.c */
void shl_cd_dot(shll_data_t *shl_data_shll);
void shl_cd_to(shll_data_t *shl_data_shll);
void shl_cd_previous(shll_data_t *shl_data_shll);
void shl_cdir_home(shll_data_t *shl_data_shll);

/* shl_cd_shell.c */
int shl_cd_shell(shll_data_t *shl_data_shll);

/* shl_get_builtin */
int (*shl_get_builtin(char *cmd))(shll_data_t *shl_data_shll);

/* shl_exit.c */
int shell_exit(shll_data_t *shl_data_shll);

/* shl_aux_stdlib.c */
int shl_get_lenth(int n);
char *shl_get_itos(int n);
int _atoi(char *strng);

/* shl_aux_error1.c */
char *cd_stcat(shll_data_t *, char *, char *, char *);
char *shl_cd_get_error(shll_data_t *shl_data_shll);
char *shl_error_nf(shll_data_t *shl_data_shll);
char *shl_exit_shell_on_error(shll_data_t *shl_data_shll);

/* shl_aux_error2.c */
char *shl_error_get_alias(char **arg_cli);
char *shl_error_env(shll_data_t *shl_data_shll);
char *shl_error_syntax(char **arg_cli);
char *shl_error_permission(char **arg_cli);
char *shl_error_path(shll_data_t *shl_data_shll);


/* shl_get_error.c */
int shl_get_error(shll_data_t *shl_data_shll, int eval);

/* shl_get_sigint.c */
void shl_get_sigint(int signal_h);

/* shl_aux_help.c */
void shl_help_env(void);
void shl_help_setnv(void);
void shl_help_unsetenv(void);
void shl_help_general(void);
void shl_help_exit(void);

/* shl_help2.c */
void shl_helper(void);
void shl_helper_al(void);
void shl_helper_cd(void);

/* shl_get_help.c */
int shl_get_help(shll_data_t *shl_data_shll);

#endif
