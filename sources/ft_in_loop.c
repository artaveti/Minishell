
#include "lib_for_minishell.h"

void   ft_loop(t_token_list *token_list, t_token_list *heredoc_list, t_environment_list *envp_list)
{
    char *input_str;
    int error_num;

    error_num = 0;
    signal(SIGINT, inthandle);////
    signal(SIGQUIT, SIG_IGN);
    while(1)
    {
//ft_list_iter_printf_environment(envp_list, printf);
        input_str = ft_readline();
        error_num = ft_syntax_error_quotes_quant(input_str);
        ft_lexer(input_str, token_list);
        ft_parser(&token_list, envp_list);
        ft_syntax_error(&token_list->next, &error_num);
        ft_heredoc_quant_error(&token_list->next, &error_num);
        ft_creat_token_for_heredoc(input_str, heredoc_list, envp_list);
// ft_list_iter_printf_token(token_list, printf);
        if (error_num != EXIT_ERROR_SYNTAX
            && token_list->next != NULL)
            ft_program(token_list, heredoc_list, &envp_list);
        if (error_num == EXIT_ERROR_SYNTAX)
            exit_status_msh = EXIT_ERROR_SYNTAX;
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        ft_list_free_for_token(&heredoc_list->next);
// system("leaks minishell");
    }
    return ;
}
