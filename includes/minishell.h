#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFF_SIZE      4096

# define PROMPT "minishell> "

# include <string.h>

// data model
typedef struct s_env
{
	struct s_env *next;
	struct s_env *prev;
	char *name;
	char *value;
} t_env;

typedef struct s_sh
{
	t_env *env;
	struct s_sh *mock;
	char **last_environ;
	char *prompt;
	size_t len_prompt;
	int last_command_ret;
	char **last_command;
	int exit;
} t_sh;

typedef struct s_be
{
	int ignore;
	int unet;
	int set;
	int null;
	int cmd;
} t_be;


void str_clear(char *str);

void buf_init(char *buf, int len);

char *triple_join(char *s1, char *s2, char *s3);

int tab_len(char **tab);

void tab_free(char **tab);

void ft_remove_endline(char *str);

int is_only_endline(char *buf);

int is_only_spaces(char *buf);

void display_prompt(t_sh *shell);

void display_command_not_found(char *command);

int make_exploitable(char **command, char **last_environ);

int strlen_until_char(char *str, char c);

char **override_last_environ(t_sh *shell);

char **build_tab_environ(t_env *env);

void clean_program(t_sh *shell);

int pass_str_to_exec(const char **str, t_sh *shell, char **mock_environ, int mock);

int manage_builtins(char **command, t_sh *shell);

void builtin_env(char **command, t_sh *shell);

void builtin_unsetenv(char **command, t_sh *shell);

void builtin_setenv(char **command, t_sh *shell);

void manage_interpretor(char **command, t_sh *shell);

void builtin_exit(char **command, t_sh *shell);

void builtin_getenv(char **command, t_sh *shell);

char *get_env_value(char *name, t_env *env);

void builtin_cd(char **command, t_sh *shell);

void ft_setenv(char *name, char *value, t_sh *shell);

void convert_chars(char *str);

t_env *create_env_link(t_env *env, char *environ_entry);

t_sh *create_shell_from(char **environ_tab);

t_sh *create_shell_props(void);

t_env *manage_empty_environ(void);

int is_ignore_arg(char *arg);

int is_null_arg(char *arg);

int have_unsets(char **command);

int is_only_env(char **command);

int have_null(char **command);

int have_ignore(char **command);

int have_setenv(char **command);

int is_setenv(char *arg);

int have_command(char **command);

int is_benv_errors(t_be *benv);

void display_environ(char **to_display, int end_line);

void display_only_setenv(char **command, int end_line);

int is_benv_do_nothing(t_be *benv);

void run_under_no_environ(char **ptr, t_sh *shell);

void run_under_new_environ(char **command, t_sh *shell);

t_env *get_start(t_env *env);

void delete_list(t_env **env);

void display_not_such(char *who, char *where);

char **get_mock_environ(char **command);

t_env *upsert_link(t_env *env, char *environ_entry);

#endif
