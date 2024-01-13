/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_lexer_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:30:45 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 12:33:31 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_is_token_redir_int_heredoc(int *i, char *input_str,
			t_token_list *token_list)
{
	char			redir_int;
	t_token_list	*tmp;

	redir_int = '<';
	if (input_str[*i] == redir_int)
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = REDIR_INT;
		tmp->value = NULL;
		tmp->next = NULL;
		*i = *i + 1;
		if (input_str[*i] == redir_int)
		{
			tmp->type = HEREDOC;
			tmp->value = NULL;
			*i = *i + 1;
		}
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void	ft_is_token_redir_out_append(int *i, char *input_str,
			t_token_list *token_list)
{
	char			redir_out;
	t_token_list	*tmp;

	redir_out = '>';
	if (input_str[*i] == redir_out)
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = REDIR_OUT;
		tmp->value = NULL;
		tmp->next = NULL;
		*i = *i + 1;
		if (input_str[*i] == redir_out)
		{
			tmp->type = REDIR_APPEND;
			tmp->value = NULL;
			*i = *i + 1;
		}
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}
