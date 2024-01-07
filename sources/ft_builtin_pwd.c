/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:48:28 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 13:49:08 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_pwd(t_for_prog *prog)
{
	if (prog->pwd_str[0] == NULL)
	{
		printf(ERROR_PWD_GETCWD_CANT_ACCESS);
		if (prog->check_builtin == BUILTIN_EXIT)
			exit(EXIT_FAILURE);
		g_exit_status_msh = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", prog->pwd_str[0]);
		if (prog->check_builtin == BUILTIN_EXIT)
			exit(EXIT_SUCCESS);
		g_exit_status_msh = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	return (0);
}
