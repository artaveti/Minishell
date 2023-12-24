
#include "lib_for_minishell.h"

void	ft_kill(t_for_prog *prog)
{
	int	i;

    i = 0;
	while (i < prog->fd_quant_pipe + 1)
	{
        printf("(%d)\n", prog->pid_arr[i]);
        kill(prog->pid_arr[i], SIGKILL);
        i++;
	}
	return ;
}