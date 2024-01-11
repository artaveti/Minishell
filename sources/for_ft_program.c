/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_program.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:03:58 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 20:32:57 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_creat_file(t_token_list *redir_list);
void	ft_check_file_creating(t_token_list *redir_list, int *flag_for_break);
void	ft_if_sigquit_or_sigint_print(int signal_flag);
void	ft_malloc_and_set_zero_for_prog_pid_arr(t_for_prog *prog);

int	ft_creat_for_program(t_for_prog *prog, t_token_list *token_list,
			t_token_list *heredoc_list, t_environment_list **envp_list)
{
	int	return_num;

	return_num = 0;
	prog->envp_for_execve = ft_creat_envp_for_execve(*envp_list);
	prog->path_arr = ft_creat_path_argv_for_execve(prog->envp_for_execve);
	prog->fd_quant_heredoc = ft_fd_quant(token_list, HEREDOC);
	prog->fd_quant_pipe = ft_fd_quant(token_list, PIPE);
	prog->fd_arr_pipe = ft_creat_and_open_pipes(prog->fd_quant_pipe);
	prog->fd_arr_heredoc = ft_creat_and_open_pipes(prog->fd_quant_heredoc);
	signal(SIGINT, SIG_IGN);
	return_num = ft_input_to_heredoc(heredoc_list, *envp_list,
			prog->fd_arr_heredoc);
	if (return_num == EXIT_HEREDOC_SIGINT)
		return (EXIT_HEREDOC_SIGINT);
	prog->redir_list = ft_creat_redir_list_for_execve(token_list);
	ft_creat_file(prog->redir_list);
	prog->argv_for_execve = ft_creat_argv_for_execve(token_list,
			prog->fd_quant_pipe);
	ft_malloc_and_set_zero_for_prog_pid_arr(prog);
	prog->check_builtin = BUILTIN_EXIT;
	return (return_num);
}

void	ft_creat_file(t_token_list *redir_list)
{
	int flag_for_break;

	flag_for_break = 0;
	while (redir_list != NULL)
	{
		if (redir_list->type == START)
			flag_for_break = 0;
		if (flag_for_break == 0)
			ft_check_file_creating(redir_list, &flag_for_break);
		redir_list = redir_list->next;
	}
	return ;
}

			void ft_check_file_creating(t_token_list *redir_list, int *flag_for_break)
			{
				int fd_num;
				
				if (redir_list->type == REDIR_OUT)
				{
					fd_num = open(redir_list->value, O_CREAT | O_TRUNC, 0644);
					if (fd_num < 0)
						*flag_for_break = 1;
					close(fd_num);
				}
				else if (redir_list->type == REDIR_APPEND)
				{
					fd_num = open(redir_list->value, O_CREAT, 0644);
					if (fd_num < 0)
						*flag_for_break = 1;
					close(fd_num);
				}
				else if (redir_list->type == REDIR_INT)
				{
					fd_num = open(redir_list->value, O_RDONLY, 0644);
					if (fd_num < 0)
						*flag_for_break = 1;
					close(fd_num);
				}		
				return ;
			}

void	ft_waitpid_for_prog(t_for_prog *prog)
{
	int	i;
	int	status;
	int	signal_flag;

	if (prog->check_builtin == BUILTIN_RETURN)
		return ; //// this if for right exit number
	signal(SIGINT, SIG_IGN);
	signal_flag = 0;
	i = 0;
	while (i < prog->fd_quant_pipe + 1)
	{
		waitpid(prog->pid_arr[i], &status, 0);
		WIFEXITED(status);
		g_exit_status_msh = WEXITSTATUS(status);
		if(status == SIGQUIT)
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

void ft_if_sigquit_or_sigint_print(int signal_flag)
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

void ft_malloc_and_set_zero_for_prog_pid_arr(t_for_prog *prog)
{
	int i;
	
	prog->pid_arr = (int *)malloc(sizeof(int) * (prog->fd_quant_pipe + 1));
	i = 0;
	while(i < prog->fd_quant_pipe + 1)
	{
		prog->pid_arr[i] = 0;
		i++;
	}
	return ;
}



    // if(signal_flag == SIGQUIT)
    // {
    //     g_exit_status_msh = 131;
    //     printf("Quit: %d\n", SIGQUIT);
    // }
    // else if (signal_flag == SIGINT)
    // {
    //     g_exit_status_msh = 130;
    //     printf("\n");
	//     rl_redisplay();
    // }
	
		// if(status == SIGQUIT)
		//      signal_flag = SIGQUIT;
		// else if (status == SIGINT)
		//      signal_flag = SIGINT;



    // if (prog->fd_quant_pipe == 0 && prog->argv_for_execve[1] == NULL)
    // {
    //     if (!ft_strncmp(prog->argv_for_execve[0][0], "echo", 5)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "cd", 3)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "pwd", 4)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "export", 7)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "unset", 6)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "env", 4)
    //      || !ft_strncmp(prog->argv_for_execve[0][0], "exit", 5))
    //     return ;
    // } // this if for right exit number
	