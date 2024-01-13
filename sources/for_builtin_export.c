/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:46:06 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 15:34:05 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_creat_last_part_of_word_for_export(char *string, char *symbols);
int		ft_for_export_change_environment(t_environment_list **envp,
			t_for_export *exp);
void	ft_for_export_add_new_for_environment(t_environment_list **envp,
			char *str);

void	ft_check_and_add_to_environment(t_environment_list **envp, char *str)
{
	t_for_export	exp;

	exp.before_equal = NULL;
	exp.after_equal = NULL;
	exp.flag_for_equal = ft_char_find('=', str);
	exp.flag_for_plus = 0;
	if (exp.flag_for_equal == 1)
	{
		if (*(ft_strchr(str, '=') - 1) == '+')
			exp.flag_for_plus = 1;
		if (exp.flag_for_plus == 1)
			exp.before_equal = ft_creat_first_part_of_word(str, "+");
		else
			exp.before_equal = ft_creat_first_part_of_word(str, "=");
		exp.after_equal = ft_creat_last_part_of_word_for_export(str, "=");
	}
	else
		exp.before_equal = ft_strdup(str);
	if (ft_for_export_change_environment(envp, &exp) == 1)
		return ;
	free(exp.before_equal);
	free(exp.after_equal);
	ft_for_export_add_new_for_environment(envp, str);
	return ;
}

char	*ft_creat_last_part_of_word_for_export(char *string, char *symbols)
{
	char	*last_part;
	int		i;

	i = 0;
	while (string[i] != '\0')
	{
		if (ft_strchr(symbols, string[i]))
		{
			last_part = ft_strdup(&string[i + 1]);
			return (last_part);
		}
		i++;
	}
	return (NULL);
}

int	ft_for_export_change_environment(t_environment_list **envp,
		t_for_export *exp)
{
	t_environment_list	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->name_and_value[0], exp->before_equal,
				ft_strlen(exp->before_equal) + 1))
		{
			if (ft_for_export_check_equal_and_plus(tmp, exp) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_for_export_add_new_for_environment(t_environment_list **envp,
		char *str)
{
	t_environment_list	*tmp_new;

	tmp_new = ft_list_new_for_environment(str);
	ft_list_add_back_for_environment(envp, tmp_new);
	return ;
}
