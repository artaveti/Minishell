/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_strlen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:07:12 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:07:30 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

size_t	ft_strlen(const	char *s)
{
	size_t	i;

	i = 0;
	if (!s || s == NULL)
		return (0);
	if (!s[0])
		return (0);
	while (s[i])
		i++;
	return (i);
}
