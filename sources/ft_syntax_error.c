/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:37:35 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:49:54 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_syntax_error_first_token(t_token_list **list);
int	ft_syntax_error_second_redirect_pipe(t_token_list **list);
int	ft_printf_for_syntax_error_redirect(t_token_list *tmp);

void	ft_syntax_error(t_token_list **list, int *error_num)
{
	if (*list == NULL)
		return ;
	if (*error_num > 0)
		return ;
	*error_num = ft_syntax_error_first_token(list);
	if (*error_num > 0)
		return ;
	*error_num = ft_syntax_error_second_redirect_pipe(list);
	return ;
}

int	ft_syntax_error_first_token(t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	if (tmp->type == PIPE)
	{
		printf(ERROR_SYNTAX_TOKEN, "|");
		return (EXIT_ERROR_SYNTAX);
	}
	return (0);
}

int	ft_syntax_error_second_redirect_pipe(t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		if ((tmp->type == REDIR_INT || tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
			&& tmp->value == NULL)
			return (ft_printf_for_syntax_error_redirect(tmp));
		else if (tmp->type == PIPE)
		{
			if (tmp->next == NULL)
			{
				printf(ERROR_SYNTAX_TOKEN, "newline");
				return (EXIT_ERROR_SYNTAX);
			}
			else if (tmp->next->type == PIPE)
			{
				printf(ERROR_SYNTAX_TOKEN, "|");
				return (EXIT_ERROR_SYNTAX);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_printf_for_syntax_error_redirect(t_token_list *tmp)
{
	if (tmp->next == NULL)
		printf(ERROR_SYNTAX_TOKEN, "newline");
	else if (tmp->next->type == REDIR_INT)
		printf(ERROR_SYNTAX_TOKEN, "<");
	else if (tmp->next->type == REDIR_OUT)
		printf(ERROR_SYNTAX_TOKEN, ">");
	else if (tmp->next->type == REDIR_APPEND)
		printf(ERROR_SYNTAX_TOKEN, ">>");
	else if (tmp->next->type == HEREDOC)
		printf(ERROR_SYNTAX_TOKEN, "<<");
	else if (tmp->next->type == PIPE)
		printf(ERROR_SYNTAX_TOKEN, "|");
	return (EXIT_ERROR_SYNTAX);
}

int	ft_syntax_error_quotes_quant(char *input_str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	if (!input_str || input_str == NULL)
		return (0);
	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (input_str[i] != '\0')
	{
		if (input_str[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (input_str[i] == '\"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (s_quote || d_quote)
	{
		printf(ERROR_SYNTAX_QUOTES);
		return (EXIT_ERROR_SYNTAX);
	}
	return (0);
}
