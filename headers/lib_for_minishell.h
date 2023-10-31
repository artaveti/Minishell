
#ifndef LIB_FOR_MINISHELL_H
# define LIB_FOR_MINISHELL_H

#include <stdio.h> // readline();
#include <stdlib.h> // exit();
#include <readline/readline.h>// readline();
#include <readline/history.h> // readline();
#include <unistd.h> // execve();
#include <termios.h>
# include <fcntl.h> // open();

# define START 100
# define WHITESPACES " \t\r\n\v"
# define END_OF_DOLLAR_SIGN "~!@#%%^*-=+[]{}:,./\'?"
# define NOT_WORD_CHARS " \t\r\n\v\'\"<>|"
# define ERROR_SYNTAX "minishell: syntax error near unexpected token `%s'\n"
# define ERROR_COMMAND "minishell: %s: command not found\n"

int exit_status;

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
    // AND,
    // OR,
    // PAR_LEFT,
    // PAR_RIGHT,
    WORD_REDIR, //9
} t_type_of_token;

typedef struct s_environment_list
{
    char **name_and_value;
    struct s_environment_list *next;
} t_environment_list;

typedef struct s_token_list
{
    int type;
    char *value;
    struct s_token_list *next;
} t_token_list;

//libft
void	*ft_memmove(void	*dst, const void	*src, size_t	len); /////
int     ft_memcmp(const void	*s1, const void	*s2, size_t	n); /////
size_t	ft_strlen(const	char *s); /////
size_t	ft_strncmp(const char	*s1, const char	*s2, size_t	n); /////
size_t	ft_strl_spc(const	char *s); /////
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize); /////
char	**ft_split(char const	*s, char c); /////
char	*ft_strchr(const char	*s, int c); /////
char	*ft_strjoin(char const	*s1, char const	*s2); /////
char	*ft_itoa(int n); /////
char	*ft_strjoin_space(char const	*s1, char const	*s2); /////
char	*ft_strdup(const char	*s1); /////

//readline
char *ft_readline(void); /////

//from pipex
void	ft_execve_firstfork(char **path_arr, t_token_list **list, char **envp);
char	**ft_prog_names_join(char	**path_arr, char	*prog_name);

//environment list
t_environment_list   *ft_list_creat_environment(char *envp[]); /////
t_environment_list	*ft_list_last_for_environment(t_environment_list	*list); /////
void	             ft_list_add_back_for_environment(t_environment_list	**list, t_environment_list	*list_for_add); /////
void                 ft_list_iter_printf_for_environment(t_environment_list	*list, int (f)(const char *, ...)); /////
int                  ft_list_length_for_environment(t_environment_list *list);

//token list
t_token_list        *ft_list_creat_start_of_token(void); /////
t_token_list	    *ft_list_last_for_token(t_token_list	*list); /////
void	            ft_list_add_back_for_token(t_token_list	**list, t_token_list	*new_list); /////
void	            ft_list_iter_printf_for_token(t_token_list	*list,	int (f)(const char *, ...)); /////
void                ft_list_free_for_token(t_token_list **list); /////
int                 ft_list_length_for_token(t_token_list *list);

//lexer
void ft_lexer(char *rl, t_token_list *token_list); /////
void ft_is_token_sep(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_single_quote(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_double_quote(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_redir_int_heredoc(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_redir_out_append(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_pipe(int *i, char *input_str, t_token_list *token_list); /////
void ft_is_token_word(int *i, char *input_str, t_token_list *token_list); /////

//parser
void ft_parser(t_token_list **token_list, t_environment_list *envp_list);
char *ft_change_dollar_sign_in_word(char *string, t_environment_list *envp_list);
char *ft_change_dollar_sign_in_q_double(char *string, t_environment_list *envp_list);

//execve
char    **ft_creat_envp_for_execve(t_environment_list *envp_list);
void    ft_execve(t_token_list *token_list, t_environment_list *envp_list);
char	**ft_make_path_argv_for_execve(char	**envp);
int     ft_fd_quant(t_token_list *token_list);
void	ft_fd_close(int **fd, int fd_quant);
void    ft_fork(char **path_arr, int **fd_arr, int fd_quant, char ***argv_for_execve, t_token_list *redir_list, char **envp_for_execve);

//free
void ft_free_double_pointer_array(char ***array);
void ft_free_double_pointer_int(int ***array, int fd_quant);
void ft_free_triple_pointer_array(char ****array);

//for printf
void ft_printf_double_arr(char **double_arr);
void ft_printf_triple_arr(char ***triple_arr);

#endif