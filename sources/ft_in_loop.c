/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:46:56 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/10 16:00:51 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void	ft_loop(t_token_list *token_list, t_token_list *heredoc_list,
			t_environment_list *envp_list)
{
	t_term_and_work_dir	term;
	int					loop_stop_num;
	char				*input_str;
	int					error_num;
	
	tcgetattr(STDIN_FILENO, &(term.termios));
	term.num = term.termios.c_lflag;
	term.pwd_str_in_term = getcwd(NULL, 0);
	loop_stop_num = 0;
	error_num = 0;
	while(loop_stop_num == 0)
    {
//printf("%s\n", term.pwd_str_in_term);
        term.termios.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &(term.termios));
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, ft_sigint_new_line);
//ft_list_iter_printf_environment(envp_list, printf);
        input_str = ft_readline(&term, &loop_stop_num);
//printf("input_str(%d)\n", input_str[0] == '\0');
        if (loop_stop_num == 0)
        {
            error_num = ft_syntax_error_quotes_quant(input_str);
            ft_lexer(input_str, token_list);
            ft_parser(&token_list, envp_list);
//ft_list_iter_printf_token(token_list, printf);
            ft_syntax_error(&token_list->next, &error_num);
            ft_heredoc_quant_error(&token_list->next, &error_num);
            ft_creat_token_for_heredoc(input_str, heredoc_list, envp_list);
            if (error_num != EXIT_ERROR_SYNTAX
                && token_list->next != NULL)
                ft_program(token_list, heredoc_list, &envp_list, &term);
            if (error_num == EXIT_ERROR_SYNTAX)
                g_exit_status_msh = EXIT_ERROR_SYNTAX;
            free(input_str);
            ft_list_free_for_token(&token_list->next);
            ft_list_free_for_token(&heredoc_list->next);
        }
    }
    free(term.pwd_str_in_term);
    return ;
}
