/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_argc_quant.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:56:07 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 13:56:12 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_check_argc_quant(int argc)
{
	if (argc > 1)
	{
		printf(ERROR_ARGC_QUANT);
		exit(EXIT_FAILURE);
	}
	return ;
}
