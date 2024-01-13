/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_iter_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:18:27 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:19:50 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_list_iter_printf_token(t_token_list	*list,
			int (f)(const char *, ...))
{
	t_token_list	*tmp;
	int				i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	f("========================================\n");
	while (tmp != NULL)
	{
		f("TOKEN_INDEX[%d]\n", i);
		f("TOKEN_TYPE:::%d\n", tmp->type);
		f("TOKEN_VALUE:::(%s)\n", tmp->value);
		f("TOKEN_NEXT:::%d\n", tmp->next > 0);
		f("\n");
		tmp = tmp->next;
		i++;
	}
	return ;
}

void	ft_list_iter_printf_environment(t_environment_list	*list,
			int (f)(const char *, ...))
{
	t_environment_list	*tmp;
	int					i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	f("========================================\n");
	while (tmp != NULL)
	{
		f("ENVP_INDEX[%d]\n", i);
		f("ENVP_NAME_AND_VALUE[0]:::%s\n", tmp->name_and_value[0]);
		f("ENVP_NAME_AND_VALUE[1]:::%s\n", tmp->name_and_value[1]);
		f("ENVP_FLAG:::%d\n", tmp->envp_flag);
		f("\n");
		tmp = tmp->next;
		i++;
	}
	return ;
}
