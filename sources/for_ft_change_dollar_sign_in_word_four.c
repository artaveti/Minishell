/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_change_dollar_sign_in_word_four.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:15:35 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:41:01 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_additional_for_if_first(char **str_for_dup, char **tmp_str,
			char **g_exit_status_msh_str, int *result);
void	ft_additional_for_if_second(char **name_and_value, char	**tmp_str,
			int *result);

char	*ft_change_dollar_sign_in_before_end_symb(char **before_end_symb,
			char **name_and_value, int num_for_last, int *result)
{
	char	*tmp_str;
	char	*str_for_dup;
	char	*g_exit_status_msh_str;

	tmp_str = *before_end_symb;
	if (tmp_str[1] == '\0')
	{
		tmp_str = ft_strdup("$");
		*result = 1;
	}
	else if (ft_strchr("?0123456789", tmp_str[1]) && tmp_str[1] != '\0')
		ft_additional_for_if_first(&str_for_dup, &tmp_str,
			&g_exit_status_msh_str, result);
	else if (!ft_memcmp(&tmp_str[1], name_and_value[0],
			ft_strlen(&tmp_str[1]) + 1))
	{
		ft_additional_for_if_second(name_and_value, &tmp_str, result);
		return (tmp_str);
	}
	else if (num_for_last == 1)
	{
		tmp_str = ft_strdup("");
		*result = 1;
	}
	return (tmp_str);
}

void	ft_additional_for_if_first(char **str_for_dup, char **tmp_str,
			char **g_exit_status_msh_str, int *result)
{
	*str_for_dup = ft_strdup(&tmp_str[0][2]);
	if (tmp_str[0][1] == '?')
	{
		*g_exit_status_msh_str = ft_itoa(g_exit_status_msh);
		*tmp_str = ft_strjoin(*g_exit_status_msh_str, *str_for_dup);
		free(*g_exit_status_msh_str);
	}
	else if (tmp_str[0][1] == '0')
		*tmp_str = ft_strjoin("minishell", *str_for_dup);
	else
		*tmp_str = ft_strdup(*str_for_dup);
	free(*str_for_dup);
	*result = 1;
	return ;
}

void	ft_additional_for_if_second(char **name_and_value, char	**tmp_str,
			int *result)
{
	if (name_and_value[1] == NULL)
	{
		*tmp_str = ft_strdup("");
		*result = 1;
	}
	else
	{
		*tmp_str = ft_strdup(name_and_value[1]);
		*result = 1;
	}
	return ;
}
