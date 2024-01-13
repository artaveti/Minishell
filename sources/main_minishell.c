/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:51:15 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:57:34 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_environment_list	*envp_list;
	t_token_list		*token_list;
	t_token_list		*heredoc_list;

	(void)argv;
	ft_check_argc_quant(argc);
	envp_list = ft_list_creat_environment(envp);
	token_list = ft_list_creat_token();
	heredoc_list = ft_list_creat_token();
	g_exit_status_msh = 0;
	ft_loop(token_list, heredoc_list, envp_list);
	ft_list_free_for_envp_list(&envp_list);
	exit(g_exit_status_msh);
}
