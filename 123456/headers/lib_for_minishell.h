
#ifndef LIB_FOR_MINISHELL_H
# define LIB_FOR_MINISHELL_H

#include <stdio.h> //readline();
#include <stdlib.h> //exit();
#include <readline/readline.h> //readline();
#include <readline/history.h> //readline();
#include <unistd.h> //execve();

typedef enum s_type_of_token
{
    SEP,
    Q_SINGLE,
    Q_DOUBLE,
    REDIR_INT,
    REDIR_OUT,
    REDIR_APPEND,
    HEREDOC,
    PIPE,
    AND,
    OR,
    PAR_LEFT,
    PAR_RIGHT,
    WORD,
} t_type_of_token;

typedef struct s_token_list
{
    int type;
    char *value;
    struct s_token_list *next;
} t_token_list;

//libft
char	**ft_split(char const	*s, char c);
char	*ft_strchr(const char	*s, int c);
size_t	ft_strlen(const	char *s);
size_t	ft_strncmp(const char	*s1, const char	*s2, size_t	n);
char	*ft_strjoin(char const	*s1, char const	*s2);
char	*ft_strjoin_space(char const	*s1, char const	*s2);
size_t	ft_strl_spc(const	char *s);
//from pipex
char	**ft_make_path_arr(char	**envp);
void	ft_execve_firstfork(char **path_arr, char **argv, char **envp);
char	**ft_prog_names_join(char	**path_arr, char	*prog_name);
//minishell
char *ft_readline(void);
void ft_lexer(char *rl, t_token_list *token_list);

//token
void ft_is_token_sep(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_single_quote(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_double_quote(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_redir_int_heredoc(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_redir_out_append(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_pipe(int *i, char *input_str, t_token_list *token_list);
void ft_is_token_word(int *i, char *input_str, t_token_list *token_list);
//list
void	        ft_lstadd_back(t_token_list	**lst, t_token_list	*new);
t_token_list	*ft_lstlast(t_token_list	*lst);
void	        ft_lstiter_printf(t_token_list	*token_list,	int (f)(const char *, ...));

#endif