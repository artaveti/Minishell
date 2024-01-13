/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:51:45 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 16:52:59 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_running_for_only_one_builtin(t_environment_list **envp_list,
			t_for_prog *prog, t_token_list *tmp_redir_list)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (ft_change_stdin_stdout_fd_redir(tmp_redir_list, fd_out,
			prog->fd_arr_heredoc, ONLY_ONE_BUILTIN) > 0)
	{
		ft_close_pipe_fd(prog->fd_arr_heredoc, prog->fd_quant_heredoc);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		return ;
	}
	ft_close_pipe_fd(prog->fd_arr_heredoc, prog->fd_quant_heredoc);
	ft_running_builtin(envp_list, prog,
		prog->argv_for_execve[prog->index], fd_out);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	return ;
}

void	ft_running_builtin(t_environment_list **envp_list, t_for_prog *prog,
			char **array_of_strings, int fd_out)
{
	if (!ft_strncmp(array_of_strings[0], "echo", 5))
		ft_echo(array_of_strings, prog);
	else if (!ft_strncmp(array_of_strings[0], "cd", 3))
		ft_cd(envp_list, prog, array_of_strings, fd_out);
	else if (!ft_strncmp(array_of_strings[0], "pwd", 4))
		ft_pwd(prog);
	else if (!ft_strncmp(array_of_strings[0], "export", 7))
		ft_export(envp_list, prog, array_of_strings, fd_out);
	else if (!ft_strncmp(array_of_strings[0], "unset", 6))
		ft_unset(envp_list, prog, array_of_strings, fd_out);
	else if (!ft_strncmp(array_of_strings[0], "env", 4))
		ft_env(envp_list, prog, array_of_strings, fd_out);
	else if (!ft_strncmp(array_of_strings[0], "exit", 5))
		ft_exit(prog, array_of_strings, fd_out);
	return ;
}
