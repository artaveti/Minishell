/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_parser_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:44:58 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 13:03:06 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_parser_third_change_quotes_to_word(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;

	(void)envp_list;
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->type == Q_SINGLE || tmp->type == Q_DOUBLE)
			tmp->type = WORD;
		tmp = tmp->next;
	}
	return ;
}

void	ft_parser_fourth_join_w(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;
	char			*tmp_string;

	(void)envp_list;
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD && tmp->next != NULL && tmp->next->type == WORD)
		{
			tmp_string = tmp->next->value;
			tmp->next->value = ft_strjoin(tmp->value, tmp->next->value);
			free(tmp_string);
			tmp->type = SEP;
			free(tmp->value);
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_parser_fifth_change_redir_value(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;

	(void)envp_list;
	tmp = *list;
	while (tmp != NULL)
	{
		if ((tmp->type == REDIR_INT
				|| tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND) //// || tmp->type == HEREDOC)
			&& tmp->next != NULL
			&& tmp->next->type == WORD)
		{
			tmp->value = ft_strdup(tmp->next->value);
			free(tmp->next->value);
			tmp->next->type = SEP;
			tmp->next->value = NULL;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_parser_sixth_change_heredoc_value(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;
	int				i;
	char			*num_str;

	(void)envp_list;
	tmp = *list;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC
			&& tmp->next != NULL
			&& tmp->next->type == WORD)
		{
			num_str = ft_itoa(i);
			tmp->value = ft_strdup(num_str);
			free(tmp->next->value);
			tmp->next->type = SEP;
			tmp->next->value = NULL;
			free(num_str);
			i++;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_parser_remove_sep_from_list(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*previous;
	t_token_list	*tmp;

	(void)envp_list;
	previous = *list;
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (tmp->type == SEP)
		{
			previous->next = tmp->next;
			free(tmp);
			tmp = previous->next;
		}
		else
		{
			previous = previous->next;
			tmp = previous->next;
		}
	}
	return ;
}
