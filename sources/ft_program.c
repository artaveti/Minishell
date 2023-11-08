
#include "lib_for_minishell.h"

void ft_program(t_token_list *token_list, t_environment_list *envp_list)
{
    t_for_prog prog;

    ft_creat_heredoc(token_list);
    ft_creat_for_program(&prog, token_list, envp_list);
    ft_running_with_pipes(&prog, envp_list);
    ft_close_fd(prog.fd_arr, prog.fd_quant);
    ft_waitpid_for_prog(&prog);
    ft_free_for_prog(&prog);
    return ;
}
