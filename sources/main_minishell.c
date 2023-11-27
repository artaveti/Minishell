
#include "lib_for_minishell.h"

// argumentneri qanaki error !!!
// chakertneri qanaki error !!!
// tab seghmelux petka amboghj kamandayi anuny cuyc ta ???
// configur exit_status_msh
// in unset->wrong_name change for working export and unset functions names
// ctrl + C must change exit_status_msh to 1
// skzbic mana galis heredocery, ete ka bacuma, ete tesnum syntax error gruma dra masin ev stopa talis, aysinqn heredocery chi bacum
// maximum quant of heredoc is 16
// ete syntax error ka, petq e chsharunakel
// "bash: syntax error near unexpected token `&'" echo $? 258
// ete voreve forki mej chi gtnum inputi hamar faily uremn exita linum miayn ayd forky
// kami( || ) jamanak, ete arajiny skhala(orinak` "Command not found" kam "No such file or directory"), cuyca talis u sharunakuma
// andi ( && ) jamanak, ete arajiny skhala, el chi sharunakum
// "bash: sss: No such file or directory" echo $? 1
// "bash: wcl: command not found" echo $? 127
// ete grvuma "bash: (komandy, vory chka kam fayly, vory chka): u heto inchvor ban" , apa ayd jamanak cragiry ashkhatuma, hajord qaylina ancnum"
// isk ete grvuma "bash: miangamic patchary u symboly", apa petq e chsharunakel
// petqe hashvi arnel envp-i NULL linely (unsetov karelia amboghjy jnjel), thready error e cuyc talis

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    char *input_str;
    int error_num;

// char *e[1];
// e[0] = NULL;
// (void)envp;

    (void)argc;
    (void)argv;
    ft_printf_double_arr(envp); ///////////
    envp_list = ft_list_creat_environment(envp);
    //ft_list_iter_printf_environment(envp_list, printf);
    // envp_list = NULL;
    token_list = ft_list_creat_token();
    exit_status_msh = 0;
    while(1)
    {
        //ft_list_iter_printf_environment(envp_list, printf);
        input_str = ft_readline();
        ft_lexer(input_str, token_list);
        ft_parser(&token_list, envp_list);
        ft_syntax_error(&token_list->next, &error_num);
        ft_heredoc_quant_error(&token_list->next);
        if (error_num != EXIT_ERROR_SYNTAX && token_list->next != NULL)
            ft_program(token_list, &envp_list);
        if (error_num == EXIT_ERROR_SYNTAX)
            exit_status_msh = EXIT_ERROR_SYNTAX;
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        // system("leaks minishell");
    }
    exit(EXIT_SUCCESS);
}
