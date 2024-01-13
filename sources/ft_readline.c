/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:30:27 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 21:45:56 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_readline(t_term_and_work_dir *term, int *loop_stop_num)
{
	char	*str;
	int		i;

	str = readline("minishell> ");
	i = 0;
	if (str == NULL)
	{
		term->termios.c_lflag = term->num;
		tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
		printf("minishell> exit\n");
		*loop_stop_num = 1;
		return (NULL);
	}
	while (str[i] != '\0')
	{
		if (ft_strchr(WHITESPACES_WITHOUT_SPACE_RL, str[i]))
			i++;
		else
			break ;
	}
	if (str[i] != '\0')
		add_history(str);
	return (str);
}
