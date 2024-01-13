/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_program_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:04:02 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:42:31 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_if_sigquit_or_sigint_print(int signal_flag);

void	ft_kill_child_processes(t_for_prog *prog)
{
	int	i;
	int	kill_num;

	i = 0;
	while (prog->pid_arr[i] != -1)
	{
		kill_num = kill(prog->pid_arr[i], SIGKILL);
		i++;
	}
	printf(ERROR_RES_NOT_ENOUGH);
	return ;
}

void	ft_waitpid_for_prog(t_for_prog *prog)
{
	int	i;
	int	status;
	int	signal_flag;

	if (prog->check_builtin == BUILTIN_RETURN)
		return ;
	signal(SIGINT, SIG_IGN);
	signal_flag = 0;
	i = 0;
	while (i < prog->fd_quant_pipe + 1)
	{
		waitpid(prog->pid_arr[i], &status, 0);
		WIFEXITED(status);
		g_exit_status_msh = WEXITSTATUS(status);
		if (status == SIGQUIT)
			g_exit_status_msh = EXIT_ERROR_SIGQUIT;
		else if (status == SIGINT)
			g_exit_status_msh = EXIT_ERROR_SIGINT;
		if (status == SIGINT)
			signal_flag = SIGINT;
		i++;
	}
	ft_if_sigquit_or_sigint_print(signal_flag);
	return ;
}

void	ft_if_sigquit_or_sigint_print(int signal_flag)
{
	if (g_exit_status_msh == EXIT_ERROR_SIGQUIT)
		printf("Quit: %d\n", SIGQUIT);
	if (signal_flag == SIGINT)
	{
		printf("\n");
		rl_redisplay();
	}
	return ;
}

void	ft_free_for_prog(t_for_prog *prog)
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
