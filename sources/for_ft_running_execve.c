/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_running_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:14:56 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/08 17:47:06 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_dup2_stdin(t_token_list *redir_list, int **heredoc_pipe,
		int fd_out, int only_one_builtin);
int	ft_dup2_stdout(t_token_list *redir_list,
		int fd_out, int only_one_builtin);

void	ft_change_stdin_stdout_fd_pipe(int **fd_arr, int fd_quant_pipe, int i)
{
	int	i_mid;

	if (fd_arr == NULL)
		return ;
	i_mid = i / 2;
	if (i == 0)
		dup2(fd_arr[i][1], STDOUT_FILENO);
	else if (i == fd_quant_pipe)
		dup2(fd_arr[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(fd_arr[i_mid][0], STDIN_FILENO);
		dup2(fd_arr[i][1], STDOUT_FILENO);
	}
	return ;
}

int	ft_change_stdin_stdout_fd_redir(t_token_list *redir_list, int fd_out,
			int **heredoc_pipe, int only_one_builtint)
{
	int	return_num;

	return_num = 0;
	if (redir_list == NULL)
		return (return_num);
	if (redir_list->type == START)
		redir_list = redir_list->next;
	while (redir_list != NULL && redir_list->type != START)
	{
		return_num = ft_dup2_stdin(redir_list, heredoc_pipe,
				fd_out, only_one_builtint);
		if (return_num > 0)
			return (return_num);
		return_num = ft_dup2_stdout(redir_list, fd_out, only_one_builtint);
		if (return_num > 0)
			return (return_num);
		redir_list = redir_list->next;
	}
	return (return_num);
}

int	ft_dup2_stdin(t_token_list *redir_list, int **heredoc_pipe,
		int fd_out, int only_one_builtin)
{
	int	num_for_atoi;
	int	fd_redir_int;

	if (redir_list->type == REDIR_INT)
	{
		fd_redir_int = open(redir_list->value, O_RDONLY, 0644);
		if (fd_redir_int < 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			printf(ERROR_NO_FILE_OR_DIR, redir_list->value);
			if (only_one_builtin != ONLY_ONE_BUILTIN)
				exit(EXIT_ERROR_NO_FILE_OR_DIRECTORY);
			g_exit_status_msh = EXIT_ERROR_NO_FILE_OR_DIRECTORY;
			return (EXIT_ERROR_NO_FILE_OR_DIRECTORY);
		}
		dup2(fd_redir_int, STDIN_FILENO);
		close(fd_redir_int);
	}
	else if (redir_list->type == HEREDOC)
	{
		num_for_atoi = ft_atoi(redir_list->value);
		dup2(heredoc_pipe[num_for_atoi][0], STDIN_FILENO);
	}
	return (0);
}

int	ft_dup2_stdout(t_token_list *redir_list, int fd_out, int only_one_builtin)
{
	int	fd_redir_out_or_append;

	fd_redir_out_or_append = 0;
	if (redir_list->type == REDIR_OUT || redir_list->type == REDIR_APPEND)
	{		
		if (redir_list->type == REDIR_OUT)
			fd_redir_out_or_append = open(redir_list->value, O_RDWR | O_TRUNC, 0644);
		else if (redir_list->type == REDIR_APPEND)
			fd_redir_out_or_append = open(redir_list->value, O_RDWR | O_APPEND, 0644);
		if (fd_redir_out_or_append < 0)
		{
			dup2(fd_out, STDOUT_FILENO);
			printf(ERROR_PERM_DEN, redir_list->value);
			if (only_one_builtin != ONLY_ONE_BUILTIN)
				exit(EXIT_ERROR_PERM_DEN);
			g_exit_status_msh = EXIT_ERROR_PERM_DEN;
			return (EXIT_ERROR_PERM_DEN);
		}
			dup2(fd_redir_out_or_append, STDOUT_FILENO);
			close(fd_redir_out_or_append);
	}
	return (0);
}



// int	ft_dup2_stdout(t_token_list *redir_list, int fd_out, int only_one_builtin)
// {
// 	int	fd_redir_out;
// 	int	fd_redir_append;

// 	if (redir_list->type == REDIR_OUT)
// 	{
// 		fd_redir_out = open(redir_list->value, O_RDWR | O_TRUNC, 0644);
// 		if (fd_redir_out < 0)
// 		{
// 			dup2(fd_out, STDOUT_FILENO);
// 			printf(ERROR_PERM_DEN, redir_list->value);
// 			if (only_one_builtin != ONLY_ONE_BUILTIN)
// 				exit(EXIT_ERROR_PERM_DEN);
// 			g_exit_status_msh = EXIT_ERROR_PERM_DEN;
// 			return (EXIT_ERROR_PERM_DEN);
// 		}
// 		dup2(fd_redir_out, STDOUT_FILENO);
// 		close(fd_redir_out);
// 	}
// 	else if (redir_list->type == REDIR_APPEND)
// 	{
// 		fd_redir_append = open(redir_list->value, O_RDWR | O_APPEND, 0644);
// 		if (fd_redir_append < 0)
// 		{
// 			dup2(fd_out, STDOUT_FILENO);
// 			printf(ERROR_PERM_DEN, redir_list->value);
// 			if (only_one_builtin != ONLY_ONE_BUILTIN)
// 				exit(EXIT_ERROR_PERM_DEN);
// 			g_exit_status_msh = EXIT_ERROR_PERM_DEN;
// 			return (EXIT_ERROR_PERM_DEN);
// 		}
// 		dup2(fd_redir_append, STDOUT_FILENO);
// 		close(fd_redir_append);
// 	}
// 	return (0);
// }
