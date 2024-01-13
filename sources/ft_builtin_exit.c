/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:40:32 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 18:48:36 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int	ft_atoi_for_long_long(char *str, long long *result);
int	ft_for_exit_atoi_check_sign_of_num(char *str, int *minus);
int	ft_for_exit_check_atoires(t_for_prog *prog,
		char **array_of_strings, int atoi_res);

void	ft_exit(t_for_prog *prog, char **array_of_strings, int fd_out)
{
	long long	exit_atoi;
	int			atoi_res;

	dup2(fd_out, STDOUT_FILENO);
	if (array_of_strings[1] == NULL)
	{
		if (prog->check_builtin == BUILTIN_RETURN)
			printf(PRINT_EXIT);
		exit(g_exit_status_msh);
	}
	exit_atoi = 0;
	atoi_res = ft_atoi_for_long_long(array_of_strings[1], &exit_atoi);
	if (ft_for_exit_check_atoires(prog, array_of_strings, atoi_res) == 1)
		return ;
	else
	{
		if (prog->check_builtin == BUILTIN_RETURN)
			printf(PRINT_EXIT);
		if (exit_atoi >= 0)
			g_exit_status_msh = exit_atoi % 256;
		else
			g_exit_status_msh = 256 + exit_atoi % 256;
		exit(g_exit_status_msh);
	}
	return ;
}

int	ft_atoi_for_long_long(char *str, long long *result)
{
	unsigned long long	num;
	unsigned long long	min;
	int					minus;

	num = 0;
	min = 9223372036854775808ULL;
	minus = 1;
	while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (ft_for_exit_atoi_check_sign_of_num(str, &minus) == 1)
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		if ((minus == 1 && num > LLONG_MAX) || (minus == -1 && num > min))
			return (0);
		str++;
	}
	if (*str != '\0')
		return (0);
	*result = num * minus;
	return (1);
}

int	ft_for_exit_atoi_check_sign_of_num(char *str, int *minus)
{
	if (*str == '-')
	{
		*minus = *minus * -1;
		return (1);
	}
	else if (*str == '+')
		return (1);
	return (0);
}

int	ft_for_exit_check_atoires(t_for_prog *prog,
		char **array_of_strings, int atoi_res)
{
	if (atoi_res == 1 && array_of_strings[2] != NULL)
	{
		if (prog->check_builtin == BUILTIN_RETURN)
			printf(PRINT_EXIT);
		printf(ERROR_MANY_ARG);
		g_exit_status_msh = EXIT_FAILURE;
		return (1);
	}
	else if (atoi_res == 0)
	{
		if (prog->check_builtin == BUILTIN_RETURN)
			printf(PRINT_EXIT);
		printf(ERROR_NUM_ARG_REQ, array_of_strings[1]);
		g_exit_status_msh = 255;
		exit(g_exit_status_msh);
	}
	return (0);
}
