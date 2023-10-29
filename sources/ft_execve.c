
#include "lib_for_minishell.h"

int ft_fd_quant(t_token_list *token_list);
int	**ft_make_and_open_pipes(int fd_quant);
char **ft_creat_arr_for_execve(t_token_list *token_list, int fd_quant);
t_token_list *ft_creat_redir_list(t_token_list *token_list);
void ft_is_token_redir_int_out_heredoc_redir_append_pipe_execve(t_token_list *token_list, t_token_list *redir_list);

void ft_execve(t_token_list *token_list, t_environment_list *envp_list, char **envp_for_execve, char **path_arr)
{
    int fd_quant;
    int **fd_arr;
    char **arr_for_execve;
    t_token_list *redir_list;

    (void)token_list;
    (void)envp_list;
    (void)envp_for_execve;
    (void)path_arr;
    
    fd_quant = ft_fd_quant(token_list);
    fd_arr = ft_make_and_open_pipes(fd_quant);
    arr_for_execve = ft_creat_arr_for_execve(token_list, fd_quant);
    redir_list = ft_creat_redir_list(token_list);
    //ft_list_iter_printf_for_token(redir_list, printf);
    //ft_printf_double_arr(arr_for_execve);
    ft_free_double_pointer_array(&arr_for_execve);
    ft_free_double_pointer_int(&fd_arr, fd_quant);
    ft_list_free_for_token(&redir_list);
    return ;
    //creat **token_list_redir; arr_for_execve[i] and token_list_redir[i] for every fork 
}



int ft_fd_quant(t_token_list *token_list)
{
    int fd_quant;

    fd_quant = 0;
    while(token_list != NULL)
    {
        if (token_list->type == PIPE)
            fd_quant++;
        token_list = token_list->next;
    }
    return(fd_quant);
}



int	**ft_make_and_open_pipes(int fd_quant)
{
	int	i;
	int	**fd_arr;

    if (fd_quant == 0)
        return (NULL);
	i = 0;
	fd_arr = (int **)malloc(sizeof(int *) * (fd_quant));
	if (!fd_arr)
	{
		perror("Can't allocate memory in ft_make_and_open_pipes()");
		exit(EXIT_FAILURE);
	}
	while (i < fd_quant)
	{
		fd_arr[i] = (int *)malloc(sizeof(int) * 2);
		if (!fd_arr[i])
		{
			perror("Can't allocate memory in ft_make_and_open_pipes()");
			exit(EXIT_FAILURE);
		}
		if ((pipe(fd_arr[i]) < 0))
			perror("Can't create pipes");
		i++;
	}
	return (fd_arr);
}



char **ft_creat_arr_for_execve(t_token_list *token_list, int fd_quant)
{   
    char **arr_for_execve;
    char *tmp_string;
    char *tmp_for_arr;
    int i;

    arr_for_execve = (char **)malloc(sizeof(char *) * (fd_quant + 2));
    i = 0;
    while(i < fd_quant + 1)
    {
        arr_for_execve[i] = ft_strdup("");
        i++;
    }
    i = 0;
    while (token_list != NULL)
    {
        if (token_list->type == WORD)
        {
            tmp_string = ft_strjoin(token_list->value, " ");
            tmp_for_arr = arr_for_execve[i];
            arr_for_execve[i] = ft_strjoin(arr_for_execve[i], tmp_string);
            free(tmp_string);
            free(tmp_for_arr);
        }
        else if (token_list->type == PIPE)
            i++;
        token_list = token_list->next;
    }
    i++;
    arr_for_execve[i] = NULL;
    return (arr_for_execve);
}



t_token_list *ft_creat_redir_list(t_token_list *token_list)
{   
    t_token_list *redir_list;

    redir_list = (t_token_list *)malloc(sizeof(t_token_list));
    redir_list->type = START;
    redir_list->value = NULL;
    redir_list->next = NULL;
    while (token_list != NULL)
    {
        ft_is_token_redir_int_out_heredoc_redir_append_pipe_execve(token_list, redir_list);
        token_list = token_list->next;
    }
    return (redir_list);
}



void ft_is_token_redir_int_out_heredoc_redir_append_pipe_execve(t_token_list *token_list, t_token_list *redir_list)
{
    t_token_list *tmp;

    if (token_list->type == REDIR_INT)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_INT;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == REDIR_OUT)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_OUT;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == HEREDOC)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = HEREDOC;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == REDIR_APPEND)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = REDIR_APPEND;
        tmp->value = ft_strdup(token_list->value);
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    else if (token_list->type == PIPE)
    {
        tmp = (t_token_list *)malloc(sizeof(t_token_list));
        tmp->type = PIPE;
        tmp->value = "|";
        tmp->next = NULL;
        ft_list_add_back_for_token(&redir_list, tmp);
    }
    return ;
}

