
#include "lib_for_minishell.h"

void ft_creat_file(t_token_list *redir_list);

void ft_creat_for_program(t_for_prog *prog, t_token_list *token_list, t_token_list *heredoc_list, t_environment_list **envp_list)
{
    prog->envp_for_execve = ft_creat_envp_for_execve(*envp_list);
    prog->path_arr = ft_creat_path_argv_for_execve(prog->envp_for_execve);
    prog->fd_quant_heredoc = ft_fd_quant(token_list, HEREDOC);
    prog->fd_quant_pipe = ft_fd_quant(token_list, PIPE);
    prog->fd_arr_heredoc = ft_creat_and_open_pipes(prog->fd_quant_heredoc);
    ft_input_to_heredoc(heredoc_list, *envp_list, prog->fd_arr_heredoc);
    prog->fd_arr_pipe = ft_creat_and_open_pipes(prog->fd_quant_pipe);
    prog->redir_list = ft_creat_redir_list_for_execve(token_list);
    ft_creat_file(prog->redir_list);
    prog->argv_for_execve = ft_creat_argv_for_execve(token_list, prog->fd_quant_pipe);
    prog->pid_arr = (int *)malloc(sizeof(int) * (prog->fd_quant_pipe + 1));
    return ;
}



void ft_waitpid_for_prog(t_for_prog *prog)
{
    int i;
    int status;

    i = 0;
    if (prog->fd_quant_pipe == 0 && prog->argv_for_execve[1] == NULL)
    {
        if (!ft_strncmp(prog->argv_for_execve[0][0], "env", 4)
         || !ft_strncmp(prog->argv_for_execve[0][0], "unset", 6))
        //  || !ft_strncmp(prog->argv_for_execve[0][0], "export", 7)
        return ;
    }
    while (i < prog->fd_quant_pipe + 1)
    {
        waitpid(prog->pid_arr[i], &status, 0);
        WIFEXITED(status);
        exit_status_msh = WEXITSTATUS(status);
        i++;
    }
    return ;
}



void ft_free_for_prog(t_for_prog *prog)
{
    ft_free_double_pointer_array(&prog->envp_for_execve);
    ft_free_double_pointer_array(&prog->path_arr);
    ft_free_double_pointer_int(&prog->fd_arr_pipe, prog->fd_quant_pipe);
    ft_free_double_pointer_int(&prog->fd_arr_heredoc, prog->fd_quant_heredoc);
    free(prog->pid_arr);
    ft_free_triple_pointer_array(&prog->argv_for_execve);
    ft_list_free_for_token(&prog->redir_list);
    return ;
}



void ft_creat_file(t_token_list *redir_list)
{
    int fd_num;
    
    while(redir_list != NULL)
    {
        if (redir_list->type == REDIR_OUT || redir_list->type == REDIR_APPEND)
        {
            fd_num = open(redir_list->value, O_CREAT, 0644);
            close(fd_num);
        }
        redir_list = redir_list->next;
    }
    return ;
}
