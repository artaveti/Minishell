
#include "lib_for_minishell.h"

void ft_creat_for_program(t_for_prog *prog, t_token_list *token_list, t_environment_list **envp_list)
{
    // ft_list_iter_printf_environment(*envp_list, printf);
    prog->envp_for_execve = ft_creat_envp_for_execve(*envp_list);
    prog->path_arr = ft_creat_path_argv_for_execve(prog->envp_for_execve);
    prog->fd_quant = ft_fd_quant(token_list);
    prog->fd_arr = ft_make_and_open_pipes(prog->fd_quant);
    prog->redir_list = ft_creat_redir_list_for_execve(token_list);
    prog->argv_for_execve = ft_creat_argv_for_execve(token_list, prog->fd_quant);
    prog->pid_arr = (int *)malloc(sizeof(int) * (prog->fd_quant + 1));
    return ;
}



void	ft_close_pipe_fd(int **fd, int fd_quant)
{
	int	i;

	i = 0;
	while (i < fd_quant)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	return ;
}



void ft_waitpid_for_prog(t_for_prog *prog)
{
    int i;
    int status;

    i = 0;
    while (i < prog->fd_quant + 1)
    {
        //printf("prog->pid_arr[I][%d](%d)\n", i, prog->pid_arr[i]);
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
    ft_free_double_pointer_int(&prog->fd_arr, prog->fd_quant);
    free(prog->pid_arr);
    ft_free_triple_pointer_array(&prog->argv_for_execve);
    ft_list_free_for_token(&prog->redir_list);
    return ;
}
