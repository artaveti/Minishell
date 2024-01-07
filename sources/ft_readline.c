/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:30:27 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/07 15:34:01 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

char	*ft_readline(t_term_and_work_dir *term, int *loop_stop_num)
{
	char	*str;
	int		i;

	str = readline("minishell> ");
	i = 0;
	if (str == NULL) //// this "if" for "ctrl + D"(null)
	{
		term->termios.c_lflag = term->num;
		tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
		printf("minishell> exit\n");
		*loop_stop_num = 1;
		return (NULL);
//system("leaks minishell");
//exit(g_exit_status_msh);
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
