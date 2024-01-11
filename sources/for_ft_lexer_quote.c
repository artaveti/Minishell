/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_lexer_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:28:35 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/10 20:37:12 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void ft_set_chars_of_word(t_token_list	*tmp, char *input_str, char	quote, int *j);

void	ft_is_token_single_quote(int *i, char *input_str,
			t_token_list *token_list)
{
	t_token_list	*tmp;
	char			single_quote;
	int				j;

	single_quote = '\'';
	if (input_str[*i] == single_quote)
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = Q_SINGLE;
		*i = *i + 1;
		j = *i;
		while (input_str[*i] != single_quote && input_str[*i] != '\0')
			*i = *i + 1;
		tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
		ft_set_chars_of_word(tmp, input_str, single_quote, &j);
		tmp->next = NULL;
		if (input_str[*i] == single_quote)
			*i = *i + 1;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void	ft_is_token_double_quote(int *i, char *input_str,
			t_token_list *token_list)
{
	t_token_list	*tmp;
	char			double_quote;
	int				j;

	double_quote = '\"';
	if (input_str[*i] == double_quote)
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = Q_DOUBLE;
		*i = *i + 1;
		j = *i;
		while (input_str[*i] != double_quote && input_str[*i] != '\0')
			*i = *i + 1;
		tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
		ft_set_chars_of_word(tmp, input_str, double_quote, &j);
		tmp->next = NULL;
		if (input_str[*i] == double_quote)
			*i = *i + 1;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void ft_set_chars_of_word(t_token_list	*tmp, char *input_str, char	quote, int *j)
{
	int	k;
	k = 0;
	while (input_str[*j] != quote && input_str[*j] != '\0')
	{
		tmp->value[k] = input_str[*j];
		k++;
		*j = *j + 1;
	}
	tmp->value[k] = '\0';
	return ;
}