/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_builtin_cd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:05:21 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 17:14:45 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

t_environment_list	*find_node_by_name(t_environment_list *envp, char *name)
{
	while (envp != NULL)
	{
		if (envp->name_and_value != NULL && !ft_strncmp(
				envp->name_and_value[0], name, ft_strlen(name) + 1))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

void	change_node_by_name(t_environment_list **envp, char *name, char *value)
{
	t_environment_list	*current;

	current = *envp;
	while (current != NULL)
	{
		if (streq(current->name_and_value[0], name) != 0)
		{
			free(current->name_and_value[1]);
			current->name_and_value[1] = ft_strdup(value);
			if (current->envp_flag == 2)
				return ;
			current->envp_flag = 1;
			return ;
		}
		current = current->next;
	}
	return ;
}

int	streq(char *s1, char *s2)
{
	int	i;

	i = 0;
	if ((!s1 || !(*s1) || !s2 || !(*s2)) || (ft_strlen(s1) != ft_strlen(s2)))
		return (0);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
