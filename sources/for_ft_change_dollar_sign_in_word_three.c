/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_change_dollar_sign_in_word_three.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:03:10 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 16:21:04 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_change_dollar_sign_in_string(char **string, char **name_and_value,
			int num_for_last, int *result)
{
	char	*tmp_str;
	char	*before_end_symb;
	char	*after_end_symb;
	int		i;

	tmp_str = *string;
	before_end_symb = NULL;
	after_end_symb = NULL;
	i = 1;
	while (!(ft_strchr(END_OF_DOLLAR_SIGN, tmp_str[i])) && tmp_str[i] != '\0')
		i++;
	ft_creat_before_after_strings(i, &tmp_str, &before_end_symb,
		&after_end_symb);
	tmp_str = before_end_symb;
	before_end_symb = ft_change_dollar_sign_in_before_end_symb(
			&before_end_symb, name_and_value, num_for_last, result);
	if (*result == 1)
	{
		free(tmp_str);
		tmp_str = ft_strjoin(before_end_symb, after_end_symb);
	}
	free(before_end_symb);
	free(after_end_symb);
	return (tmp_str);
}

void	ft_creat_before_after_strings(int i, char **tmp_str,
			char **before_end_symb, char **after_end_symb)
{
	if (tmp_str[0][i] == '\0')
	{
		*before_end_symb = ft_strdup(*tmp_str);
		*after_end_symb = ft_strdup("");
	}
	else
	{
		*before_end_symb = ft_creat_first_part_of_word(*tmp_str,
				END_OF_DOLLAR_SIGN);
		*after_end_symb = ft_creat_last_part_of_word(*tmp_str,
				END_OF_DOLLAR_SIGN);
		if (before_end_symb[0][1] == '\0' && after_end_symb[0][0] == '?')
		{
			free(*before_end_symb);
			*before_end_symb = ft_strdup("$?");
			*tmp_str = *after_end_symb;
			*after_end_symb = ft_strdup(*after_end_symb + 1);
			free(*tmp_str);
		}
	}
	return ;
}

char	*ft_creat_last_part_of_word(char *string, char *symbols)
{
	char	*last_part;
	int		string_len;
	int		i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_strchr(symbols, string[i]))
		{
			string_len = ft_strlen(string);
			last_part = ft_strdup_quant(&string[i], string_len - i);
			return (last_part);
		}
		i++;
	}
	return (NULL);
}

