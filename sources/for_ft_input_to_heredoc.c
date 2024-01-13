/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_input_to_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:54:45 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:41:42 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_lexer_for_heredoc(char *input_str, t_token_list *string_list);
void	ft_parser_change_dollar_for_heredoc(t_token_list **list,
			t_environment_list *envp_list);
void	ft_is_token_sep_for_heredoc(int *i, char *input_str,
			t_token_list *token_list);
void	ft_is_token_word_for_heredoc(int *i, char *input_str,
			t_token_list *token_list);

void	ft_change_string_for_heredoc(char **heredoc_line,
			t_environment_list *envp_list)
{
	t_token_list	*string_list;
	t_token_list	*tmp_list;
	char			*tmp_string;

	string_list = ft_list_creat_token();
	ft_lexer_for_heredoc(*heredoc_line, string_list);
	ft_parser_change_dollar_for_heredoc(&string_list, envp_list);
	free(*heredoc_line);
	*heredoc_line = ft_strdup("");
	tmp_list = string_list->next;
	while (tmp_list != NULL)
	{
		tmp_string = *heredoc_line;
		*heredoc_line = ft_strjoin(*heredoc_line, tmp_list->value);
		free(tmp_string);
		tmp_list = tmp_list->next;
	}
	ft_list_free_for_token(&string_list->next);
	free(string_list);
	return ;
}

void	ft_lexer_for_heredoc(char *input_str, t_token_list *string_list)
{
	int	i;

	i = 0;
	if (input_str == NULL)
		return ;
	while (input_str[i] != '\0')
	{
		ft_is_token_sep_for_heredoc(&i, input_str, string_list);
		ft_is_token_word_for_heredoc(&i, input_str, string_list);
	}
	return ;
}

void	ft_parser_change_dollar_for_heredoc(t_token_list **list,
			t_environment_list *envp_list)
{
	t_token_list	*tmp;
	char			*tmp_string;

	if (list[0]->next == NULL)
		return ;
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			tmp_string = ft_change_dollar_sign_in_word(tmp->value, envp_list);
			free(tmp->value);
			tmp->value = tmp_string;
		}
		tmp = tmp->next;
	}
	tmp_string = NULL;
	return ;
}

void	ft_is_token_sep_for_heredoc(int *i, char *input_str,
			t_token_list *token_list)
{
	t_token_list	*tmp;

	if (ft_strchr(WHITESPACES, input_str[*i]))
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = SEP;
		tmp->value = ft_strdup(" ");
		tmp->next = NULL;
		*i = *i + 1;
		ft_list_add_back_for_token(&token_list, tmp);
	}
	return ;
}

void	ft_is_token_word_for_heredoc(int *i, char *input_str,
			t_token_list *token_list)
{
	t_token_list	*tmp;
	int				j;
	int				k;

	if (!ft_strchr(WHITESPACES, input_str[*i]))
	{
		tmp = (t_token_list *)malloc(sizeof(t_token_list));
		tmp->type = WORD;
		j = *i;
		while (!ft_strchr(WHITESPACES, input_str[*i]) && input_str[*i] != '\0')
			*i = *i + 1;
		tmp->value = (char *)malloc(sizeof(char) * (*i - j + 1));
		k = 0;
		while (!ft_strchr(WHITESPACES, input_str[j]))
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
