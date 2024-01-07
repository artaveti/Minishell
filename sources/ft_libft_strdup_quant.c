/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_strdup_quant.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:05:41 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:05:44 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_strdup_quant(const char	*str, size_t quant)
{
	char	*dup;
	size_t	i;

	dup = malloc(sizeof(char) * (quant + 1));
	if (!dup)
		return (0);
	i = 0;
	while (i < quant)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
