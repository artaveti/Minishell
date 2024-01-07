/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:20:34 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:21:30 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_list_length_for_token(t_token_list *list)
{
	int				i;
	t_token_list	*tmp;

	if (!list || list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

int	ft_list_length_for_environment(t_environment_list *list)
{
	int					i;
	t_environment_list	*tmp;

	if (!list || list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}
