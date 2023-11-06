
#include "lib_for_minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    char *input_str;

    (void)argc;
    (void)argv;
    envp_list = ft_list_creat_environment(envp);
    //ft_list_iter_printf_environment(envp_list, printf);
    token_list = ft_list_creat_token();
    exit_status = 0;
    while(1)
    {
        input_str = ft_readline(); //if input_str == NULL, must go to while
        ft_lexer(input_str, token_list);
        ft_list_iter_printf_token(token_list, printf);
        ft_parser(&token_list, envp_list);
        exit_status = ft_syntax_error(&token_list->next);
        printf("\n\n\n");
        ft_list_iter_printf_token(token_list, printf);
        if (input_str[0] != '\0' && token_list->next != NULL && exit_status == 0)
            ft_program(token_list, envp_list);
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        //system("leaks minishell");
    }
    exit(EXIT_SUCCESS);
}



// int main(void)
// {
//     int i;

//     i = 1;
//     printf("%d\n", i / 2);
//     return (0);
// }