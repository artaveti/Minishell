/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_running_program.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 20:02:13 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:46:09 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_set_at_start_for_ft_running_program(t_term_and_work_dir *term,
			int *i);
void	ft_change_tmp_redir_list(t_token_list **tmp_redir_list);
int		ft_fork(t_token_list *tmp_redir_list, t_environment_list **envp_list,
			t_for_prog *prog, int i);

void	ft_running_program(t_for_prog *prog, t_environment_list **envp_list,
			t_term_and_work_dir *term, int *flag_for_kill_child_processes)
{
	t_token_list	*tmp_redir_list;
	int				i;

	tmp_redir_list = prog->redir_list;
	ft_set_at_start_for_ft_running_program(term, &i);
	while (prog->argv_for_execve[i] != NULL)
	{
		prog->index = i;
		ft_change_tmp_redir_list(&tmp_redir_list);
		if (prog->fd_quant_pipe == 0)
			ft_check_if_builtin_run(envp_list, prog, tmp_redir_list,
				STDOUT_FILENO);
		if (prog->check_builtin == BUILTIN_EXIT)
		{
			if (ft_fork(tmp_redir_list, envp_list, prog, i) == 1)
			{
				*flag_for_kill_child_processes = -1;
				return ;
			}
		}
		if (tmp_redir_list != NULL && tmp_redir_list->type == START)
			tmp_redir_list = tmp_redir_list->next;
		i++;
	}
	return ;
}

void	ft_set_at_start_for_ft_running_program(t_term_and_work_dir *term,
			int *i)
{
	*i = 0;
	term->termios.c_lflag = term->num;
	tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
	return ;
}

void	ft_change_tmp_redir_list(t_token_list **tmp_redir_list)
{
	while (*tmp_redir_list != NULL)
	{
		if ((*tmp_redir_list)->type == START)
			break ;
		*tmp_redir_list = (*tmp_redir_list)->next;
	}
	return ;
}

int	ft_fork(t_token_list *tmp_redir_list, t_environment_list **envp_list,
		t_for_prog *prog, int i)
{
	t_for_fork	fk;

	fk.pid = fork();
	if (ft_check_if_pid_less_than_null(prog, &fk, i) == 1)
		return (1);
	if (fk.pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		fk.fd_out = dup(STDOUT_FILENO);
		ft_change_and_close_fd_in_fork(tmp_redir_list, prog, &fk, i);
		ft_check_is_name_dir_or_file(&fk, prog, i);
		ft_check_if_builtin_run(envp_list, prog, NULL, fk.fd_out);
		if (prog->argv_for_execve[i][0] == NULL)
			exit(EXIT_SUCCESS);
		if (prog->pwd_str[0] == NULL)
			printf(ERROR_JWD_GETCWD_CANT_ACCESS);
		ft_execve(&fk, prog, i);
		dup2(fk.fd_out, STDOUT_FILENO);
		printf(ERROR_CMD_NOT_FOUND, prog->argv_for_execve[i][0]);
		exit(EXIT_ERROR_CMD_NOT_FOUND);
	}
	prog->pid_arr[i] = fk.pid;
	return (0);
}
