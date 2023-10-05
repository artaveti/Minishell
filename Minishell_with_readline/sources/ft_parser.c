
#include "lib_for_minishell.h"

// void ft_change_dollar_sign(char *string, t_environment_list *envp_list)
// {
    
//     return ;
// }

// void ft_is_dollar_sign(t_token_list *token_list, t_environment_list *envp_list)
// {
//     int i;
//     int j;
//     char **splitted_dollar_sign;

//     if (token_list->type == WORD)
//     {
//         i = 0;
//         while (token_list->value[i] != '\0')
//         {
//             if (token_list->value[i] == '$')
//             {
//                 splitted_dollar_sign = ft_split(&token_list->value[i], '$');
//                 printf("I:::%d\n", i);
//                 j = 0;
//                 while(splitted_dollar_sign[j] != NULL)
//                 {
//                     ft_change_dollar_sign(splitted_dollar_sign[j], envp_list);
//                     printf("%s\n", splitted_dollar_sign[j]);
//                     j++;
//                 }
//             }
//             i++;
//         }
//     }
//     return ;
// }

// void ft_parser(t_token_list **token_list, t_environment_list *envp_list)
// {
//     t_token_list *tmp;
//     tmp = *token_list;

//     while (tmp != NULL)
//     {
//         ft_is_dollar_sign(tmp, envp_list);
//         tmp = tmp->next;
//     }
//     return ;
// }
