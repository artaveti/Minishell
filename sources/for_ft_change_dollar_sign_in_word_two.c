/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_change_dollar_sign_in_word_two.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:22:27 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 11:28:44 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_creat_first_part_of_word(char *string, char *symbols)
{
	char	*first_part;
	int		i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_strchr(symbols, string[i]))
		{
			first_part = ft_strdup_quant(string, i);
			return (first_part);
		}
		i++;
	}
	return (NULL);
}

void	ft_change_splitted_dollar(char ***splitted_dollar,
			t_environment_list **envp_list)
{
	t_environment_list	*tmp_env;
	char				**tmp_splitted;
	int					i;

	tmp_splitted = *splitted_dollar;
	i = 0;
	while (tmp_splitted[i] != NULL)
	{
		tmp_env = *envp_list;
		ft_change_dollar_in_string_of_splitted(tmp_env, &tmp_splitted[i]);
		i++;
	}
	return ;
}

void	ft_change_dollar_in_string_of_splitted(t_environment_list *tmp_env,
			char **string_from_splitted)
{
	char	*tmp_str;
	int		num_for_last;
	int		result;

	num_for_last = 0;
	result = 0;
	while (tmp_env != NULL)
	{
		if (tmp_env->next == NULL)
			num_for_last = 1;
		tmp_str = ft_change_dollar_sign_in_string(string_from_splitted,
				tmp_env->name_and_value, num_for_last, &result);
		if (result == 1)
		{
			free(*string_from_splitted);
			*string_from_splitted = ft_strdup(tmp_str);
			free(tmp_str);
			break ;
		}
		tmp_env = tmp_env->next;
	}
	return ;
}
