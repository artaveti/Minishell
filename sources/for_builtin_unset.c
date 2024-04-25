/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudzilo <ksudzilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:33:31 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/14 17:56:53 by ksudzilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_wrong_name(char *name, char *command)
{
	int	len;
	int	i;

	if (!(name[0] == '_' || ft_isalpha(name[0]))
		|| !name || !(*name) || name == NULL)
	{
		printf(ERROR_WRONG_NAME, command, name);
		return (1);
	}
	len = ft_strlen(name);
	i = 0;
	while (i < len)
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			printf(ERROR_WRONG_NAME, command, name);
			return (1);
		}
		i++;
	}
	return (0);
}
