/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin_export_ft_for_export_change_env        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:34:45 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/11 15:33:35 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_for_export_check_equal_and_plus(t_environment_list *tmp,
		t_for_export *exp)
{
	if (exp->flag_for_equal == 1 && exp->flag_for_plus == 1)
	{
		ft_for_export_if_equal_and_plus(tmp, exp);
		return (1);
	}
	else if (exp->flag_for_equal == 1 && exp->flag_for_plus == 0)
	{
		ft_for_export_if_equal_not_plus(tmp, exp);
		return (1);
	}
	else
	{
		ft_for_export_if_not_equal_not_plus(tmp, exp);
		return (1);
	}
	return (0);
}

void	ft_for_export_if_equal_and_plus(t_environment_list *tmp,
		t_for_export *exp)
{
	char	*tmp_str;

	tmp_str = NULL;
	if (tmp->name_and_value[1] == NULL)
		tmp->name_and_value[1] = ft_strdup(exp->after_equal);
	else
	{
		tmp_str = tmp->name_and_value[1];
		tmp->name_and_value[1] = ft_strjoin(tmp->name_and_value[1],
				exp->after_equal);
		free(tmp_str);
	}
	tmp->envp_flag = 1;
	free(exp->before_equal);
	free(exp->after_equal);
	return ;
}

void	ft_for_export_if_equal_not_plus(t_environment_list *tmp,
			t_for_export *exp)
{
	free(tmp->name_and_value[1]);
	tmp->name_and_value[1] = ft_strdup(exp->after_equal);
	tmp->envp_flag = 1;
	free(exp->before_equal);
	free(exp->after_equal);
	return ;
}

void	ft_for_export_if_not_equal_not_plus(t_environment_list *tmp,
			t_for_export *exp)
{
	if (!ft_strncmp(tmp->name_and_value[0], "OLDPWD", 7)
		|| !ft_strncmp(tmp->name_and_value[0], "PWD", 4))
	{
		tmp->envp_flag = 0;
		if (tmp->name_and_value[1] != NULL)
			tmp->envp_flag = 1;
	}
	free(exp->before_equal);
	return ;
}
