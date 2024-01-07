/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:23:18 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:25:56 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_printf_double_arr(char **double_arr)
{
	int	i;

	i = 0;
	while (double_arr[i] != NULL)
	{
		printf("I[%d](%s)\n", i, double_arr[i]);
		i++;
	}
	return ;
}

void	ft_printf_triple_arr(char ***triple_arr)
{
	int	i;

	i = 0;
	while (triple_arr[i] != NULL)
	{
		printf("Index[%d]:\n", i);
		ft_printf_double_arr(triple_arr[i]);
		i++;
	}
	return ;
}
