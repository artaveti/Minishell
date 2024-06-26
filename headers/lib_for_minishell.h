/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_for_minishell.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:56:38 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:55:55 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_FOR_MINISHELL_H
# define LIB_FOR_MINISHELL_H

# include <stdio.h> // readline();
# include <stdlib.h> // exit();
# include <readline/readline.h>// readline();
# include <readline/history.h> // readline();
# include <unistd.h> // execve();
# include <signal.h> // signal();
# include <fcntl.h> // open();
# include <dirent.h> // opendir();
# include <limits.h>// builtin exit();
# include <termios.h> // tcgetattr(); tcsetattr();
# include <sys/ioctl.h> // ???
# include <errno.h> // errno;

# define START 100
# define WHITESPACES " \t\r\n\v\f"
# define WHITESPACES_WITHOUT_SPACE_RL "\t\r\n\v\f" // without space
# define END_OF_DOLLAR_SIGN "~!@#%%^*-=+[]{}:,./\'\"?"
# define NOT_WORD_CHARS " \t\r\n\v\f\'\"<>|"
# define WRONG_SIGN_EXPORT "~!@#%%^*-+[]{}:,./\'\"?"
# define FIRST_CHECK_PWD 0
# define NOT_FIRST_CHECK_PWD 1
# define BUILTIN_EXIT 0
# define BUILTIN_RETURN 1
# define ONLY_ONE_BUILTIN 1
# define EXIT_ERROR_NO_FILE_OR_DIRECTORY 1
# define EXIT_HEREDOC_SIGINT 1
# define EXIT_ERROR_PERM_DEN 1
# define EXIT_ERROR_HEREDOC_QUANT 2
# define EXIT_ERROR_NAME_IS_DIR 126
# define EXIT_ERROR_PERM_DEN_EXEC_FILE 126
# define EXIT_ERROR_CMD_NOT_FOUND 127
# define EXIT_ERROR_NO_FILE_OR_DIR 127
# define EXIT_ERROR_SIGINT 130
# define EXIT_ERROR_SIGQUIT 131
# define EXIT_ERROR_SYNTAX 258
# define WRONG_NAME_EXPORT "export"
# define WRONG_NAME_UNSET "unset"
# define PRINT_EXIT "exit\n"
# define ERROR_ARGC_QUANT "No arguments should be passed to the program\n"
# define ERROR_ENVP_GETCWD_CANT_ACCESS "shell-init: error retrieving \
current directory: getcwd: cannot access parent directories: \
No such file or directory\n"
# define ERROR_JWD_GETCWD_CANT_ACCESS "job-working-directory: error \
retrieving current directory: getcwd: cannot access parent directories: \
No such file or directory\n"
# define ERROR_PWD_GETCWD_CANT_ACCESS "pwd: error retrieving current \
directory: getcwd: cannot access parent directories: \
No such file or directory\n"
# define ERROR_CD_GETCWD_CANT_ACCESS "chdir: error retrieving current \
directory: getcwd: cannot access parent directories: \
No such file or directory\n"
# define ERROR_CD_HOME_DIR "minishell: cd: HOME not set\n"
# define ERROR_CD_NO_FILE_OR_DIR "minishell: cd: %s:\
No such file or directory\n"
# define ERROR_HEREDOC_QUANT "minishell: maximum here-document count \
exceeded\n" //// exit from bash
# define ERROR_MANY_ARG "minishell: exit: too many arguments\n"
# define ERROR_NUM_ARG_REQ "minishell: exit: %s: numeric argument required\n"
# define ERROR_REDIR "minishell"
# define ERROR_SYNTAX_QUOTES "minishell: syntax error unclosed quotes\n"
# define ERROR_SYNTAX_TOKEN "minishell: syntax error near unexpected \
token `%s'\n"
# define ERROR_CMD_NOT_FOUND "minishell: %s: command not found\n"
# define ERROR_ENV "env: Too many arguments\n"
# define ERROR_IS_DIR "minishell: %s: is a directory\n"
# define ERROR_NO_FILE_OR_DIR "minishell: %s: No such file or directory\n"
# define ERROR_PERM_DEN "minishell: %s: Permission denied\n"
# define ERROR_FOR_EXPORT "minishell: export: `%s': not a valid identifier\n"
# define ERROR_SHLVL "minishell: warning: shell level (%lld) too high, \
resetting to 1\n"
# define ERROR_WRONG_NAME "minishell: %s: `%s': not a valid identifier\n"
# define ERROR_RES_NOT_ENOUGH "minishell: fork:\
Resource temporarily unavailable\n"


int	g_exit_status_msh;

typedef struct s_term_and_work_dir
{
	struct termios	termios;
	unsigned long	num;
	char			*pwd_str_in_term;
}	t_term_and_work_dir;

typedef enum s_type_of_token
{
	SEP, //0
	Q_SINGLE, //1
	Q_DOUBLE, //2
	REDIR_INT, //3
	REDIR_OUT, //4
	REDIR_APPEND, //5
	HEREDOC, //6
	PIPE, //7
	WORD, //8
	HEREDOC_W, //9
	HEREDOC_Q_S, //10
	HEREDOC_Q_D, //11
}	t_type_of_token;

typedef struct s_environment_list
{
	int							envp_flag;
	char						**name_and_value;
	struct s_environment_list	*next;
}	t_environment_list;

typedef struct s_token_list
{
	int						type;
	char					*value;
	struct s_token_list		*next;
}	t_token_list;

typedef struct s_for_prog
{
	t_token_list	*redir_list;
	char			**envp_for_execve;
	char			**path_arr;
	char			***argv_for_execve;
	int				index;
	int				fd_quant_heredoc;
	int				fd_quant_pipe;
	int				**fd_arr_pipe;
	int				**fd_arr_heredoc;
	int				*pid_arr;
	int				check_builtin;
	char			**pwd_str;
}	t_for_prog;

typedef struct s_for_fork
{
	pid_t	pid;
	int		fd_out;
	char	**prog_paths;
}	t_for_fork;

typedef struct s_for_export
{
	char	*before_equal;
	char	*after_equal;
	int		flag_for_equal;
	int		flag_for_plus;
}	t_for_export;

//libft
void				*ft_memmove(void	*dst, const void	*src,
						size_t	len);
int					ft_memcmp(const void	*s1, const void	*s2, size_t	n);
size_t				ft_strlen(const	char *s);
size_t				ft_strncmp(const char	*s1, const char	*s2, size_t	n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				**ft_split(char const	*s, char c);
char				*ft_strchr(const char	*s, int c);
char				*ft_strjoin(char const	*s1, char const	*s2);
int					ft_isdigit(int c);
int					ft_atoi(const char	*str);
long long			ft_longlong_atoi_for_minishell(const char *str);
char				*ft_itoa(int n);
char				*ft_strdup(const char	*s1);
char				*ft_strdup_quant(const char	*str, size_t quant);
void				ft_str_to_lowercase(char *str);
int					ft_isalpha(int symbol);
int					ft_isnum(int symbol);
int					ft_isalnum(int symbol);

//for_main
void				ft_check_argc_quant(int argc);
void				ft_loop(t_token_list *token_list,
						t_token_list *heredoc_list,
						t_environment_list *envp_list);

//readline
char				*ft_readline(t_term_and_work_dir *term, int *loop_stop_num);

//environment list
t_environment_list	*ft_list_creat_environment(char *envp[]);
t_environment_list	*ft_list_new_for_environment(char *string_from_envp);
t_environment_list	*ft_list_last_for_environment(t_environment_list	*list);
void				ft_list_add_back_for_environment(t_environment_list	**list,
						t_environment_list	*list_for_add);
int					ft_list_length_for_environment(t_environment_list *list);
void				ft_creat_or_change_shlvl_of_environment(
						t_environment_list **start_of_list);
void				ft_creat_or_change_pwd_of_environment(
						t_environment_list **start_of_list);
void				ft_creat_or_change_oldpwd_of_environment(
						t_environment_list **start_of_list);
void				ft_list_creat_by_name_for_environment(
						t_environment_list **start_of_list, int envp_flag,
						char *name, char *value);

//token list
t_token_list		*ft_list_creat_token(void);
t_token_list		*ft_list_last_for_token(t_token_list	*list);
void				ft_list_add_back_for_token(t_token_list	**list,
						t_token_list	*new_list);
void				ft_list_free_for_token(t_token_list **list);
int					ft_list_length_for_token(t_token_list *list);

//lexer
void				ft_lexer(char *rl, t_token_list *token_list);
void				ft_is_token_sep(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_single_quote(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_double_quote(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_redir_int_heredoc(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_redir_out_append(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_pipe(int *i, char *input_str,
						t_token_list *token_list);
void				ft_is_token_word(int *i, char *input_str,
						t_token_list *token_list);

//parser
void				ft_parser(t_token_list **token_list,
						t_environment_list *envp_list);
void				ft_parser_first_change_dollar(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_second_change_dollar(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_third_change_quotes_to_word(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_fourth_join_w(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_fifth_change_redir_value(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_sixth_change_heredoc_value(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_remove_sep_from_list(t_token_list **list,
						t_environment_list *envp_list);
void				ft_parser_remove_if_word_only_null_char(t_token_list **list,
						t_environment_list *envp_list);

//change dollar sign in word
char				*ft_change_dollar_sign_in_word(char *string,
						t_environment_list *envp_list);
int					ft_char_find(char c, char const	*string);
char				**ft_creat_splitted_dollar(char *string);
int					ft_symbol_quant_in_string(char *string, char symbol);
void				ft_creat_string_dollar_in_splitted(int i, char *string,
						char **splitted_dollar);
void				ft_join_splitted_after_change(char **joined_str,
						char **first_part, char **splitted_dollar);
char				*ft_creat_first_part_of_word(char *string, char *symbols);
void				ft_change_splitted_dollar(char ***splitted_dollar,
						t_environment_list **envp_list);
void				ft_change_dollar_in_string_of_splitted(
						t_environment_list *tmp_env,
						char **string_from_splitted);
char				*ft_change_dollar_sign_in_string(char **string,
						char **name_and_value, int num_for_last, int *result);
void				ft_creat_before_after_strings(int i, char **tmp_str,
						char **before_end_symb, char **after_end_symb);
char				*ft_change_dollar_sign_in_before_end_symb(
						char **before_end_symb, char **name_and_value,
						int num_for_last, int *result);
char				*ft_creat_last_part_of_word(char *string, char *symbols);

//change dollar sign in qdoub
char				*ft_change_dollar_sign_in_qdoub(char *string,
						t_environment_list *envp_list);
void				ft_change_dollar_in_splitted_qdoub(char ***splitted_str,
						t_environment_list *envp_list);
int					ft_count_spaces_for_joined_after_change(char *string);
int					ft_count_chars_for_joined_after_change(char **splitted_str);
char				*ft_creat_joined_after_change(char *string,
						char **splitted_str, int quant);
void				ft_additional_for_creat_joined_first(int *i, int *k,
						char *string, char *joined_after_change);
void				ft_additional_for_creat_joined_second(int *j, int *k,
						char **splitted_str, char *joined_after_change);

//syntax_error; heredoc_error
void				ft_syntax_error_quotes_quant(char *input_str,
						int *error_num);
void				ft_syntax_error(t_token_list **list, int *error_num);
void				ft_heredoc_quant_error(t_token_list **list, int *error_num);

//heredoc
void				ft_creat_token_for_heredoc(char *input_str,
						t_token_list *heredoc_list,
						t_environment_list *envp_list);
int					ft_input_to_heredoc(t_token_list *heredoc_list,
						t_environment_list *envp_list, int **fd_arr_heredoc);
void				ft_readline_for_heredoc(int type, char *string, int fd_num,
						t_environment_list *envp_list);
void				ft_change_string_for_heredoc(char **heredoc_line,
						t_environment_list *envp_list);

//program
void				ft_program(t_token_list *token_list,
						t_token_list *heredoc_list,
						t_environment_list **envp_list,
						t_term_and_work_dir *term);
int					ft_creat_for_program(t_for_prog *prog,
						t_token_list *token_list, t_token_list *heredoc_list,
						t_environment_list **envp_list);
char				**ft_creat_envp_for_execve(t_environment_list *envp_list);
char				**ft_creat_path_argv_for_execve(char	**envp);
t_token_list		*ft_creat_redir_list_for_execve(t_token_list *token_list);
char				***ft_creat_argv_for_execve(t_token_list *token_list,
						int fd_quant_pipe);
void				ft_kill_child_processes(t_for_prog *prog);
void				ft_waitpid_for_prog(t_for_prog *prog);
void				ft_free_for_prog(t_for_prog *prog);

//pipe
int					ft_fd_quant(t_token_list *token_list, int type);
int					**ft_creat_and_open_pipes(int fd_quant_pipe);
void				ft_close_pipe_fd(int **fd, int fd_quant_pipe);

//execve
void				ft_running_program(t_for_prog *prog,
						t_environment_list **envp_list,
						t_term_and_work_dir *term,
						int *flag_for_kill_child_processe);
void				ft_change_stdin_stdout_fd_pipe(int **fd_arr,
						int fd_quant_pipe, int i);
int					ft_change_stdin_stdout_fd_redir(t_token_list *redir_list,
						int fd_out, int **heredoc_pipe, int only_one_builtint);

//fork
int					ft_check_if_pid_less_than_null(t_for_prog *prog,
						t_for_fork *fk, int i);
void				ft_change_and_close_fd_in_fork(
						t_token_list *tmp_redir_list, t_for_prog *prog,
						t_for_fork *fk, int i);
void				ft_execve(t_for_fork *fk, t_for_prog *prog, int i);
void				ft_check_is_name_dir_or_file(t_for_fork *fk,
						t_for_prog *prog, int i);

//free
void				ft_free_double_pointer_array(char ***array);
void				ft_free_double_pointer_int(int ***array, int fd_quant_pipe);
void				ft_free_triple_pointer_array(char ****array);
void				ft_list_free_for_envp_list(t_environment_list **envp_list);

//printf
void				ft_list_iter_printf_token(t_token_list	*list,
						int (f)(const char *, ...));
void				ft_list_iter_printf_environment(t_environment_list	*list,
						int (f)(const char *, ...));
void				ft_printf_double_arr(char **double_arr);
void				ft_printf_triple_arr(char ***triple_arr);

//builtin
void				ft_echo(char **array_of_strings, t_for_prog *prog);
void				ft_cd(t_environment_list **envp, t_for_prog *prog,
						char **array_of_strings, int fd_out);
int					ft_pwd(t_for_prog *prog);
void				ft_export(t_environment_list **envp, t_for_prog *prog,
						char **array_of_strings, int fd_out);
void				ft_unset(t_environment_list **envp, t_for_prog *prog,
						char **array_of_strings, int fd_out);
void				ft_env(t_environment_list **envp, t_for_prog *prog,
						char **array_of_strings, int fd_out);
void				ft_exit(t_for_prog *prog, char **array_of_strings,
						int fd_out);
void				ft_check_if_builtin_run(t_environment_list **envp_list,
						t_for_prog *prog, t_token_list *tmp_redir_list,
						int fd_out);
void				ft_running_for_only_one_builtin(
						t_environment_list **envp_list, t_for_prog *prog,
						t_token_list *tmp_redir_list);
void				ft_running_builtin(t_environment_list **envp_list,
						t_for_prog *prog, char **array_of_strings, int fd_out);

//for builtin cd
t_environment_list	*find_node_by_name(t_environment_list *envp, char *name);
void				change_node_by_name(t_environment_list **envp, char *name,
						char *value);
int					streq(char *s1, char *s2);

//for builtin export
void				ft_check_and_add_to_environment(t_environment_list **envp,
						char *str);
int					ft_for_export_check_equal_and_plus(t_environment_list *tmp,
						t_for_export *exp);
void				ft_for_export_if_equal_and_plus(t_environment_list *tmp,
						t_for_export *exp);
void				ft_for_export_if_equal_not_plus(t_environment_list *tmp,
						t_for_export *exp);
void				ft_for_export_if_not_equal_not_plus(
						t_environment_list *tmp, t_for_export *exp);

//for builtin unset
int					ft_wrong_name(char	*name, char	*command);

//signal
void				ft_sigint_new_line(int sig_num);
void				ft_sigint_heredoc(int sig_num);

#endif
