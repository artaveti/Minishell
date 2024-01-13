/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:35:26 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:57:46 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_sigint_new_line(int sig_num)
{
	(void)sig_num;
	g_exit_status_msh = 1;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_heredoc(int sig_num)
{
	(void)sig_num;
	printf("\n");
	exit(EXIT_HEREDOC_SIGINT);
}
