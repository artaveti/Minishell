/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_strchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:04:57 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:05:17 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_strchr(const char	*s, int c)
{
	if (!s || !*s)
		return (NULL);
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// char	*ft_strchr(const char	*s, int c)
// {
// 	int i;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] || s[i] == (char)c)
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	return (NULL);
// }
