/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:06:23 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/14 18:38:57 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	for_ft_unset(t_environment_list **head, const char *name);
int		ft_unset_head_of_envp_list(t_environment_list **head,
			const char *name);
int		ft_for_unset_check_oldpwd_and_pwd(t_environment_list *current,
			const char *name);

void	ft_unset(t_environment_list **envp, t_for_prog *prog,
			char **array_of_strings, int fd_out)
{
	int	i;

	dup2(fd_out, STDOUT_FILENO);
	i = 1;
	while (array_of_strings[i] != NULL)
	{
		if (ft_wrong_name(array_of_strings[i], WRONG_NAME_UNSET))
		{
			if (prog->check_builtin == BUILTIN_EXIT)
				exit(EXIT_FAILURE);
			g_exit_status_msh = EXIT_FAILURE;
			return ;
		}
		for_ft_unset(envp, array_of_strings[i]);
		i++;
	}
	if (prog->check_builtin == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	g_exit_status_msh = EXIT_SUCCESS;
	return ;
}

void	for_ft_unset(t_environment_list **head, const char *name)
{
	t_environment_list	*current;
	t_environment_list	*prev;

	if (ft_unset_head_of_envp_list(head, name))
		return ;
	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->name_and_value[0], name,
				ft_strlen((*head)->name_and_value[0]) + 1) == 0)
		{
			if (ft_for_unset_check_oldpwd_and_pwd(current, name) == 1)
				return ;
			prev->next = current->next;
			free(current->name_and_value[0]);
			free(current->name_and_value[1]);
			free(current->name_and_value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
	return ;
}

int	ft_unset_head_of_envp_list(t_environment_list **head, const char *name)
{
	t_environment_list	*temp;

	if (*head == NULL)
		return (1);
	if (ft_strncmp((*head)->name_and_value[0], name,
			ft_strlen((*head)->name_and_value[0]) + 1) == 0)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->name_and_value[0]);
		free(temp->name_and_value[1]);
		free(temp->name_and_value);
		free(temp);
		return (1);
	}
	return (0);
}

int	ft_for_unset_check_oldpwd_and_pwd(t_environment_list *current,
			const char *name)
{
	if (!ft_strncmp(name, "OLDPWD", 7) || !ft_strncmp(name, "PWD", 4))
	{
		current->envp_flag = 2;
		return (1);
	}
	return (0);
}
