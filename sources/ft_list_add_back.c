/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:09:06 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:13:10 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_list_add_back_for_environment(t_environment_list	**list,
			t_environment_list *list_for_add)
{
	t_environment_list	*tmp;

	if (!list_for_add)
		return ;
	if (!*list)
	{
		*list = list_for_add;
		return ;
	}
	tmp = ft_list_last_for_environment(*list);
	tmp->next = list_for_add;
	return ;
}

void	ft_list_add_back_for_token(t_token_list	**list,
			t_token_list *list_for_add)
{
	t_token_list	*tmp;

	if (!list_for_add)
		return ;
	if (!*list)
	{
		*list = list_for_add;
		return ;
	}
	tmp = ft_list_last_for_token(*list);
	tmp->next = list_for_add;
	return ;
}
