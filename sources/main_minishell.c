
#include "lib_for_minishell.h"

// ete syntax error ka, inchua bashy skzbic pahanjum heredocneri mutqy heto cuyc talis syntax errory ev durs galis
// start_of_list->name_and_value[1] = ft_strdup(ft_strchr(envp[0], '=') + 1); khndiry nranum er, vor compilyatory i skzbane chgiti ardyunqy NULL e linelu, te urish ban
// octal 00, hexadecimal 0
// printf("(%p)\n", NULL) return 0x0; printf("(%p)\n", (void *)00000000 return 0x0; printf("(%p)\n", (void *)0) return 0x0;
// printf("(%p)\n", (void *)1) return 0x1;  printf("(%p)\n", (void *)42) return 0x2a; printf("(%p)\n", (void *)"a") return 0x109ceec20;
// printf("(%p)\n(%p)\n(%p)\n", (void *)55, (void *)'7', (void *)"7") return 0x37 0x37 0x104d36c20;
// argumentneri qanaki error !!!
// tab seghmelux petka amboghj kamandayi anuny cuyc ta ???
// configur exit_status_msh
// in unset->wrong_name change for working export and unset functions names
// ctrl + C must change exit_status_msh to 1
// skzbic mana galis heredocery, ete ka bacuma, ete tesnuma syntax error gruma dra masin ev stopa talis, aysinqn heredocery chi bacum
// heredoc documentation [COMMAND] <<[-] 'DELIMITER' (der petq chi anel, verjum kereva)
// maximum quant of heredoc is 16
// ete syntax error ka, petq e chsharunakel
// "bash: syntax error near unexpected token `&'" echo $? 258
// ete voreve forki mej chi gtnum inputi hamar faily uremn exita linum miayn ayd forky
// kami( || ) jamanak, ete arajiny skhala(orinak` "Command not found" kam "No such file or directory"), cuyca talis u sharunakuma
// andi ( && ) jamanak, ete arajiny skhala, el chi sharunakum
// "bash: sss: No such file or directory" echo $? 1
// "bash: wcl: command not found" echo $? 127
// ete grvuma "bash: (komandy, vory chka kam fayly, vory chka): u heto inchvor ban" , apa ayd jamanak cragiry ashkhatuma, hajord qaylina ancnum"
// ete grvuma "bash: miangamic patchary u symboly", apa petq e chsharunakel
// petqe hashvi arnel envp-i NULL linely (unsetov karelia amboghjy jnjel), thready error e cuyc talis

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    t_token_list *heredoc_list;

// (void)envp;
// char *e[2];
// e[0] = "abc";
// e[1] = NULL;
// envp_list = ft_list_creat_environment(e);
// envp_list = NULL;

    (void)argc;
    (void)argv;
// ft_printf_double_arr(envp);
    envp_list = ft_list_creat_environment(envp);
// ft_list_iter_printf_environment(envp_list, printf);
    token_list = ft_list_creat_token();
    heredoc_list = ft_list_creat_token();
    exit_status_msh = 0;
    ft_loop(token_list, heredoc_list, envp_list);
    exit(EXIT_SUCCESS);
}


// int main (void)
// {
//     // //char str[2];
//     // char *tmp;
//     // // tmp = NULL;
//     int num = 100;
//     // //tmp = getcwd(NULL, 0);
//     // tmp = getcwd(NULL, 0);
//     // perror("+++++++++");
//     // printf("(%s)\n", tmp);
//     // system("leaks minishell");
//     printf("%d", -100 == -num);
//     // opendir("/bin");
//     // perror("opendir:");
//     return (0);
// }
