/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_free_for_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:16:11 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:17:58 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_list_free_for_token(t_token_list **list)
{
	t_token_list	*tmp;
	t_token_list	*next;
	int				i;

	i = 0;
	tmp = *list;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	*list = NULL;
	return ;
}



        // if (tmp->type == WORD
        //     || tmp->type == REDIR_INT
        //     || tmp->type == REDIR_OUT
        //     || tmp->type == REDIR_APPEND
        //     || tmp->type == HEREDOC
        //     || tmp->type == HEREDOC_W
        //     || tmp->type == HEREDOC_Q_S
        //     || tmp->type == HEREDOC_Q_D)
        //         free(tmp->value);
