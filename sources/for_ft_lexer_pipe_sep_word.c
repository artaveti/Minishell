/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_lexer_pipe_sep_word.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:08:32 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 12:23:03 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_is_token_pipe(int *i, char *input_str, t_token_list *token_list)
{
	char			pipe;
	t_token_list	*tmp;

	pipe = '|';
	if (input_str[*i] == pipe)
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = PIPE;
		tmp->value = NULL;
		tmp->next = NULL;
		*i = *i + 1;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void	ft_is_token_sep(int *i, char *input_str, t_token_list *token_list)
{
	t_token_list	*tmp;

	if (ft_strchr(WHITESPACES, input_str[*i]))
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = SEP;
		tmp->value = NULL;
		tmp->next = NULL;
		while (ft_strchr(WHITESPACES, input_str[*i]) && input_str[*i] != '\0')
			*i = *i + 1;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void	ft_is_token_word(int *i, char *input_str, t_token_list *token_list)
{
	t_token_list	*tmp;
	int				j;
	int				k;

	if (!ft_strchr(NOT_WORD_CHARS, input_str[*i]))
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = WORD;
		j = *i;
		while (!ft_strchr(NOT_WORD_CHARS, input_str[*i])
			&& input_str[*i] != '\0')
			*i = *i + 1;
		tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
		k = 0;
		while (!ft_strchr(NOT_WORD_CHARS, input_str[j]))
		{
			tmp->value[k] = input_str[j];
			k++;
			j++;
		}
		tmp->value[k] = '\0';
		tmp->next = NULL;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}
