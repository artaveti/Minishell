/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_creat_or_change_pwd_and_oldpwd_of_envir        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:53:25 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:40:41 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_change_pwd_of_environment(t_environment_list *tmp_list,
		char *working_dir);

void	ft_creat_or_change_pwd_of_environment(
			t_environment_list **start_of_list)
{
	t_environment_list	*tmp_list;
	char				*working_dir;

	working_dir = getcwd(NULL, 0);
	tmp_list = *start_of_list;
	while (tmp_list != NULL)
	{
		if (ft_change_pwd_of_environment (tmp_list, working_dir) == 1)
			return ;
		tmp_list = tmp_list->next;
	}
	if (working_dir == NULL)
	{
		printf(ERROR_ENVP_GETCWD_CANT_ACCESS);
		return ;
	}
	ft_list_creat_by_name_for_environment(start_of_list, 1, "PWD", working_dir);
	free(working_dir);
	return ;
}

int	ft_change_pwd_of_environment(t_environment_list *tmp_list,
		char *working_dir)
{
	if (!ft_strncmp(tmp_list->name_and_value[0], "PWD", 4))
	{
		if (working_dir == NULL)
		{
			printf(ERROR_ENVP_GETCWD_CANT_ACCESS);
			return (1);
		}
		else
		{
			tmp_list->envp_flag = 1;
			free(tmp_list->name_and_value[1]);
			tmp_list->name_and_value[1] = ft_strdup(working_dir);
			free(working_dir);
		}
		return (1);
	}
	return (0);
}

void	ft_creat_or_change_oldpwd_of_environment(
			t_environment_list **start_of_list)
{
	t_environment_list	*tmp_list;

	tmp_list = *start_of_list;
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(tmp_list->name_and_value[0], "OLDPWD", 7))
		{
			tmp_list->envp_flag = 0;
			free(tmp_list->name_and_value[1]);
			tmp_list->name_and_value[1] = NULL;
			return ;
		}
		tmp_list = tmp_list->next;
	}
	ft_list_creat_by_name_for_environment(start_of_list, 0, "OLDPWD", NULL);
	return ;
}

void	ft_list_creat_by_name_for_environment(
			t_environment_list **start_of_list, int envp_flag,
			char *name, char *value)
{
	t_environment_list	*tmp_pwd;

	tmp_pwd = (t_environment_list *)malloc(sizeof(t_environment_list));
	tmp_pwd->name_and_value = (char **)malloc(sizeof(char *) * 3);
	tmp_pwd->envp_flag = envp_flag;
	tmp_pwd->name_and_value[0] = ft_strdup(name);
	tmp_pwd->name_and_value[1] = ft_strdup(value);
	tmp_pwd->name_and_value[2] = NULL;
	tmp_pwd->next = NULL;
	ft_list_add_back_for_environment(start_of_list, tmp_pwd);
	return ;
}
