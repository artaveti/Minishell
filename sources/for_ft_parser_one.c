/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_parser_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:43:04 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 12:44:18 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_change_char_from_the_last(char *string, char symbol);

void	ft_parser_first_change_dollar(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;
	char			*tmp_string;

	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			tmp_string = ft_change_dollar_sign_in_word(tmp->value, envp_list);
			free(tmp->value);
			tmp->value = tmp_string;
		}
		else if (tmp->type == Q_DOUBLE)
		{
			tmp_string = ft_change_dollar_sign_in_qdoub(tmp->value, envp_list);
			free(tmp->value);
			tmp->value = tmp_string;
		}
		tmp = tmp->next;
	}
	tmp_string = NULL;
	return ;
}

void	ft_parser_second_change_dollar(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;
	char			*tmp_string;

	(void)envp_list;
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD
			&& tmp->next != NULL
			&& (tmp->next->type == Q_SINGLE
				|| tmp->next->type == Q_DOUBLE))
		{
			tmp_string = ft_change_char_from_the_last(tmp->value, '$');
			free(tmp->value);
			tmp->value = tmp_string;
		}
		tmp = tmp->next;
	}
	tmp_string = NULL;
	return ;
}

char	*ft_change_char_from_the_last(char *string, char symbol)
{
	size_t	i;
	char	*tmp_string;

	if (ft_strlen(string) == 0)
	{
		tmp_string = ft_strdup("");
		return (tmp_string);
	}
	i = ft_strlen(string) - 1;
	while (i != 0)
	{
		if (string[i] == symbol)
			string[i] = '\0';
		else
			break ;
		i--;
	}
	if (string[i] == symbol)
		string[i] = '\0';
	tmp_string = ft_strdup(string);
	return (tmp_string);
}
