
#include "lib_for_minishell.h"

t_token_list *ft_list_creat_start_token(void)
{
    t_token_list *start;

    start = malloc(sizeof(t_token_list));
    start->type = START;
    start->value = NULL;
    start->next = NULL;
    return (start);
}

t_environment_list   *ft_list_creat_environment(char *envp[])
{
    t_environment_list *start_of_list;
    t_environment_list *tmp;
    int envp_len;
    int i;

    start_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
    start_of_list->name_and_value = ft_split(envp[0], '=');
    start_of_list->next = NULL;

    envp_len = ft_count_envp_len(envp);
    i = 1;
    while(i < envp_len)
    {
        tmp = ft_list_new_for_environment(envp[i]);
        ft_list_add_back_for_environment(&start_of_list, tmp);
        i++;
    }
    return   (start_of_list);
}
