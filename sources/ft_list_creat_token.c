/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_creat_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:14:47 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:15:42 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

t_token_list	*ft_list_creat_token(void)
{
	t_token_list	*start;

	start = malloc(sizeof(t_token_list));
	start->type = START;
	start->value = NULL;
	start->next = NULL;
	return (start);
}
