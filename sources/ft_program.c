
#include "lib_for_minishell.h"

void ft_set_null_for_prog(t_for_prog *prog);

void ft_program(t_token_list *token_list, t_token_list *heredoc_list, t_environment_list **envp_list, t_term *term)
{
    t_for_prog prog;

    ft_set_null_for_prog(&prog);
    if (ft_creat_for_program(&prog, token_list, heredoc_list, envp_list) == 1)
    {
        term->termios.c_lflag = term->num;
        tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
        ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
        ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
        ft_free_for_prog(&prog);
        return ;
    }
    ft_running_program(&prog, envp_list, term);
    ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
    ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
    ft_waitpid_for_prog(&prog);
    ft_free_for_prog(&prog);
    return ;
}



void ft_set_null_for_prog(t_for_prog *prog)
{
    prog->redir_list = NULL;
    prog->envp_for_execve = NULL;
    prog->path_arr = NULL;
    prog->argv_for_execve = NULL;
    prog->fd_quant_heredoc = 0;
    prog->fd_quant_pipe = 0;
    prog->fd_arr_pipe = NULL;
    prog->fd_arr_heredoc = NULL;
    prog->pid_arr = NULL;
    prog->check_builtin = 0;
    return ;
}
