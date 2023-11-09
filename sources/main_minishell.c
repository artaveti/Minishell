
#include "lib_for_minishell.h"


//space add to history
//configur exit_status_msh
//ctrl + C must change exit_status_msh to 1
//skzbic mana galis heredocery, ete ka bacuma, ete tesnum syntax error gruma dra masin ev stopa talis, aysinqn hajord heredocery chi bacum
// arajiny steghcuma heredocnery heredoc-i jamanak stdouty talisa pipein u tpacy chi erevum, petqa arandzin sarqel jamanakavor pokhel
// heto syntax errornery bolor depqeri hamar, ete ayn ka uremn exit
// "bash: syntax error near unexpected token `&'" echo $? 258
// ete voreve forki mej chi gtnum inputi hamar faily uremn exita linum miayn ayd forky
// kami( || ) jamanak, ete arajiny skhala(orinak` "Command not found" kam "No such file or directory"), cuyca talis u sharunakuma
// andi ( && ) jamanak, ete arajiny skhala, el chi sharunakum
// "bash: sss: No such file or directory" echo $? 1
// "bash: wcl: command not found" echo $? 127
// ete grvuma "bash: (komandy, vory chka kam fayly, vory chka): u heto inchvor ban" , apa ayd jamanak cragiry ashkhatuma, hajord qaylina ancnum"
// isk ete grvuma "bash: miangamic patchary u symboly", apa cragiry vochmiban chi anum ev miangamic exita linum
// heredoc buffer

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    char *input_str;
    int error_num;

    (void)argc;
    (void)argv;
    envp_list = ft_list_creat_environment(envp);
    //ft_list_iter_printf_environment(envp_list, printf);
    token_list = ft_list_creat_token();
    exit_status_msh = 0;
    while(1)
    {
        //ft_list_iter_printf_environment(envp_list, printf);
        input_str = ft_readline(); //if input_str == NULL, must go to while
        ft_lexer(input_str, token_list);
        // ft_list_iter_printf_token(token_list, printf);
        ft_parser(&token_list, envp_list);
        ft_syntax_error(&token_list->next, &error_num);
        // printf("\n\n\n");
        // ft_list_iter_printf_token(token_list, printf);
        if (error_num != EXIT_ERROR_SYNTAX && token_list->next != NULL) //&& input_str[0])
            ft_program(token_list, envp_list);
        if (error_num == EXIT_ERROR_SYNTAX)
            exit_status_msh = EXIT_ERROR_SYNTAX;
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        // system("leaks minishell");
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


// int	main(void)
// {
// 	char str[] = "-92233720g36854775910";  // 9223372036854775807  -9223372036854775808

// 	printf("%d\n", atoi(str)); //4457664474921187555  -4099609794157644803
// 	printf("%lld\n", ft_longlong_atoi_for_pushswap(str));
// }
