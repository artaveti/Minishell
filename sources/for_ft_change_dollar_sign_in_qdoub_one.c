/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_ft_change_dollar_sign_in_qdoub_one.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:47:27 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:40:53 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_change_dollar_in_splitted_qdoub(char ***splitted_str,
			t_environment_list *envp_list)
{
	int		i;
	char	*tmp_for_splitted;
	char	**tmp_splitted_str;

	tmp_splitted_str = *splitted_str;
	i = 0;
	while (tmp_splitted_str[i] != NULL)
	{
		tmp_for_splitted = ft_change_dollar_sign_in_word(tmp_splitted_str[i],
				envp_list);
		free(tmp_splitted_str[i]);
		tmp_splitted_str[i] = tmp_for_splitted;
		i++;
	}
	tmp_for_splitted = NULL;
	return ;
}

int	ft_count_spaces_for_joined_after_change(char *string)
{
	int	i;
	int	space_count;

	i = 0;
	space_count = 0;
	while (string[i] != '\0')
	{
		if (string[i] == ' ')
			space_count++;
		i++;
	}
	return (space_count);
}

int	ft_count_chars_for_joined_after_change(char **splitted_str)
{
	int	i;
	int	chars_count;

	i = 0;
	chars_count = 0;
	while (splitted_str[i] != NULL)
	{
		chars_count += ft_strlen(splitted_str[i]);
		i++;
	}
	return (chars_count);
}
