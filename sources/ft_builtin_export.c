/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:18:57 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/14 18:36:21 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_print_for_export(t_environment_list *envp, t_for_prog *prog,
		char **array_of_strings);
int	ft_check_name_for_export(char *str);

void	ft_export(t_environment_list **envp, t_for_prog *prog,
		char **array_of_strings, int fd_out)
{
	int	i;
	int	flag_for_export;

	if (ft_print_for_export(*envp, prog, array_of_strings) == 0)
		return ;
	i = 1;
	flag_for_export = EXIT_SUCCESS;
	while (array_of_strings[i] != NULL)
	{
		dup2(fd_out, STDOUT_FILENO);
		if (ft_check_name_for_export(array_of_strings[i]) == 1)
			flag_for_export = EXIT_FAILURE;
		else
			ft_check_and_add_to_environment(envp, array_of_strings[i]);
		i++;
	}
	g_exit_status_msh = flag_for_export;
	if (prog->check_builtin == BUILTIN_EXIT)
		exit(g_exit_status_msh);
	return ;
}

int	ft_print_for_export(t_environment_list *envp, t_for_prog *prog,
		char **array_of_strings)
{
	t_environment_list	*tmp;

	if (array_of_strings[1] == NULL)
	{
		tmp = envp;
		while (tmp != NULL)
		{
			if (tmp->envp_flag == 0)
				printf("declare -x %s\n", tmp->name_and_value[0]);
			else if (tmp->envp_flag == 1)
				printf("declare -x %s=\"%s\"\n", tmp->name_and_value[0],
					tmp->name_and_value[1]);
			tmp = tmp->next;
		}
		if (prog->check_builtin == BUILTIN_EXIT)
			exit(EXIT_SUCCESS);
		g_exit_status_msh = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	return (1);
}

int	ft_check_name_for_export(char *str)
{
	int	i;

	if (!str || str == NULL || str[0] == '\0')
		return (1);
	if (ft_isnum(str[0]) || str[0] == '+' || str[0] == '=')
	{
		printf(ERROR_FOR_EXPORT, str);
		return (1);
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (0);
		if ((ft_strchr(WRONG_SIGN_EXPORT, str[i])) && str[i] != '\0')
		{
			printf(ERROR_FOR_EXPORT, str);
			return (1);
		}
		i++;
	}
	return (0);
}
