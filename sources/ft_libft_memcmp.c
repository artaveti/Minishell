/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_memcmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:03:21 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:03:26 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t	n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = s1;
	str2 = s2;
	i = 0;
	while (i < n)
	{
		if (*str1 == *str2)
		{
			str1++;
			str2++;
			i++;
		}
		else
			return (*str1 - *str2);
	}
	return (0);
}
