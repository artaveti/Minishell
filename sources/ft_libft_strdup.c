/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:06:00 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:06:05 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_strdup(const char	*s1)
{
	char	*dup;

	if (!s1 || s1 == NULL)
		return (NULL);
	dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	return (dup);
}
