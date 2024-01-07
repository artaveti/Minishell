/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_last.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:20:11 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:20:16 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

t_environment_list	*ft_list_last_for_environment(t_environment_list	*list)
{
	t_environment_list	*last;

	if (!list)
		return (0);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_token_list	*ft_list_last_for_token(t_token_list	*list)
{
	t_token_list	*last;

	if (!list)
		return (0);
	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}
