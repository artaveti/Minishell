
#include "lib_for_minishell.h"

// argumentneri qanaki error !!!
// chakertneri qanaki error !!!
// tab seghmelux petka amboghj kamandayi anuny cuyc ta ???
// configur exit_status_msh
// in unset->wrong_name change for working export and unset functions names
// ctrl + C must change exit_status_msh to 1
// skzbic mana galis heredocery, ete ka bacuma, ete tesnuma syntax error gruma dra masin ev stopa talis, aysinqn heredocery chi bacum
// heredoc documentation [COMMAND] <<[-] 'DELIMITER'
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
    t_token_list *heredoc_list;

// char *e[1];
// e[0] = NULL;
// (void)envp;

    (void)argc;
    (void)argv;
    // ft_printf_double_arr(envp);
    envp_list = ft_list_creat_environment(envp);
    // ft_list_iter_printf_environment(envp_list, printf);
    // envp_list = NULL;
    token_list = ft_list_creat_token();
    heredoc_list = ft_list_creat_token();
    exit_status_msh = 0;
    ft_loop(token_list, heredoc_list, envp_list);
    exit(EXIT_SUCCESS);
}
