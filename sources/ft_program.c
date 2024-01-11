/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:26:57 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 21:10:25 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_set_null_for_prog(t_for_prog *prog);
void	ft_kill_and_waitpid(t_for_prog *prog, int flag_for_kill_child_processes);
void	ft_kill_child_processes(t_for_prog *prog);

void	ft_program(t_token_list *token_list, t_token_list *heredoc_list,
			t_environment_list **envp_list, t_term_and_work_dir *term)
{
	t_for_prog	prog;
	int			return_num;
	int			flag_for_kill_child_processes;

	return_num = 0;
	flag_for_kill_child_processes = 0;
	ft_set_null_for_prog(&prog);
	prog.pwd_str = &(term->pwd_str_in_term);
//printf("prog.pwd_str[0](%s)\n", prog.pwd_str[0]);
	return_num = ft_creat_for_program(&prog, token_list,
			heredoc_list, envp_list);
	if (return_num == EXIT_HEREDOC_SIGINT)
	{
		term->termios.c_lflag = term->num;
		tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
		ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
		ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
		ft_free_for_prog(&prog);
		return ;
	}
	ft_running_program(&prog, envp_list, term, &flag_for_kill_child_processes);
	ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
	ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
	ft_kill_and_waitpid(&prog, flag_for_kill_child_processes);
	ft_free_for_prog(&prog);
	return ;
}

void	ft_set_null_for_prog(t_for_prog *prog)
{
	prog->redir_list = NULL;
	prog->envp_for_execve = NULL;
	prog->path_arr = NULL;
	prog->argv_for_execve = NULL;
	prog->index = 0;
	prog->fd_quant_heredoc = 0;
	prog->fd_quant_pipe = 0;
	prog->fd_arr_pipe = NULL;
	prog->fd_arr_heredoc = NULL;
	prog->pid_arr = NULL;
	prog->check_builtin = 0;
	prog->pwd_str = NULL;
	return ;
}

void ft_kill_and_waitpid(t_for_prog *prog, int flag_for_kill_child_processes)
{
	if(flag_for_kill_child_processes == -1)
		ft_kill_child_processes(prog);
	ft_waitpid_for_prog(prog);
	if (flag_for_kill_child_processes == -1)
		g_exit_status_msh = EXIT_FAILURE;
	return ;
}

void ft_kill_child_processes(t_for_prog *prog)
{
	int i;
	int kill_num;
	
	i = 0;
	while(prog->pid_arr[i] != -1)
	{
		kill_num = kill(prog->pid_arr[i], SIGKILL);
		i++;
	}
	printf(ERRO_RES_NOT_ENOUGH);
	return ;
}