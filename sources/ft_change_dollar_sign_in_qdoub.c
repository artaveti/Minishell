/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_dollar_sign_in_qdoub.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:52:04 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 13:52:08 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_change_dollar_sign_in_qdoub(char *string,
			t_environment_list *envp_list)
{
	char	**splitted_str;
	char	*joined_after_change;
	int		space_quant;
	int		char_quant;

	splitted_str = ft_split(string, ' ');
	ft_change_dollar_in_splitted_qdoub(&splitted_str, envp_list);
	space_quant = ft_count_spaces_for_joined_after_change(string);
	char_quant = ft_count_chars_for_joined_after_change(splitted_str);
	joined_after_change = ft_creat_joined_after_change(string, splitted_str,
			space_quant + char_quant);
	ft_free_double_pointer_array(&splitted_str);
	return (joined_after_change);
}
