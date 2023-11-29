
#include "lib_for_minishell.h"

void ft_program(t_token_list *token_list, t_token_list *heredoc_list, t_environment_list **envp_list)
{
    t_for_prog prog;

    ft_creat_for_program(&prog, token_list, heredoc_list, envp_list);
    ft_running_program(&prog, envp_list);
    ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
    ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
    ft_waitpid_for_prog(&prog);
    ft_free_for_prog(&prog);
    return ;
}
