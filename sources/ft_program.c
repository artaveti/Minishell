/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_program.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:26:57 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:30:13 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_set_null_for_prog(t_for_prog *prog);

void	ft_program(t_token_list *token_list, t_token_list *heredoc_list,
			t_environment_list **envp_list, t_term_and_work_dir *term)
{
	t_for_prog	prog;
	int			return_num;

	return_num = 0;
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
	ft_running_program(&prog, envp_list, term);
	ft_close_pipe_fd(prog.fd_arr_pipe, prog.fd_quant_pipe);
	ft_close_pipe_fd(prog.fd_arr_heredoc, prog.fd_quant_heredoc);
	ft_waitpid_for_prog(&prog);
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
