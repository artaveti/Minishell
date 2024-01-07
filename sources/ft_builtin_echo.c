/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:25:40 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 13:42:11 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int		n_set(char *str, int *suppress_nl);
void	ft_print_for_echo(char **array_of_strings, int *flag_word, int *i);

void	ft_echo(char **array_of_strings, t_for_prog *prog)
{
	int	i;
	int	suppress_nl;
	int	flag_word;
	int	flag_set;

	suppress_nl = 0;
	flag_word = 0;
	flag_set = 0;
	i = 1;
	while (array_of_strings[i] != NULL)
	{
		if (ft_strlen(array_of_strings[i]) >= 2
			&& n_set(array_of_strings[i], &suppress_nl)
			&& !flag_word)
		{
			flag_set = suppress_nl;
			i++;
		}
		else
		{
			if (!flag_set)
				suppress_nl = 0;
			ft_print_for_echo(array_of_strings, &flag_word, &i);
			i++;
		}
	}
	if (!suppress_nl)
		write(STDOUT_FILENO, "\n", 1);
	if (prog->check_builtin == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	g_exit_status_msh = 0;
	return ;
}

int	n_set(char *str, int *suppress_nl)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
		{
			*suppress_nl = 1;
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	ft_print_for_echo(char **array_of_strings, int *flag_word, int *i)
{
	*flag_word = 1;
	write(STDOUT_FILENO, array_of_strings[*i], ft_strlen(array_of_strings[*i]));
	if (array_of_strings[*i + 1])
		write(STDOUT_FILENO, " ", 1);
	return ;
}
