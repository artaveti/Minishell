/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:21:47 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 14:29:49 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_parser(t_token_list **list, t_environment_list *envp_list)
{
	if (list[0]->next == NULL)
		return ;
	ft_parser_first_change_dollar(list, envp_list);
	ft_parser_remove_if_word_only_null_char(list, envp_list);
	ft_parser_second_change_dollar(list, envp_list);
	ft_parser_third_change_quotes_to_word(list, envp_list);
	ft_parser_fourth_join_w(list, envp_list);
	ft_parser_remove_sep_from_list(list, envp_list);
	ft_parser_fifth_change_redir_value(list, envp_list);
	ft_parser_sixth_change_heredoc_value(list, envp_list);
	ft_parser_remove_sep_from_list(list, envp_list);
	return ;
}
