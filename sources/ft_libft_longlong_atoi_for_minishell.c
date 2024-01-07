/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_longlong_atoi_for_minishell.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:02:07 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:02:11 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

long long	ft_longlong_atoi_for_minishell(const char *str)
{
	long long	num;
	long long	minus;

	if (str == NULL)
		return (0);
	num = 0;
	minus = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
	}
	if (*str != '\0' && !ft_isdigit(*str))
		return (0);
	return (num * minus);
}
