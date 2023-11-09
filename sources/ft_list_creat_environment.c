
#include "lib_for_minishell.h"

int ft_count_envp_len(char *envp[]);
t_environment_list	*ft_list_new_for_environment(char *string_from_envp);

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
    //ft_change_shlvl_of_environment(&start_of_list);
    return   (start_of_list);
}



int ft_count_envp_len(char *envp[])
{
    int i;

    i = 0;
    while(envp[i] != NULL)
        i++;
    return (i);
}



t_environment_list	*ft_list_new_for_environment(char *string_from_envp)
{
	t_environment_list	*result;

	result = (t_environment_list *)malloc(sizeof(t_environment_list));
	if (!result)
		return (NULL);
	result->name_and_value = ft_split(string_from_envp, '='); // change to first symbol '='
	result->next = NULL;
	return (result);
}



// void ft_change_shlvl_of_environment(t_environment_list **start_of_list)
// {
//     t_environment_list *tmp_list;

//     tmp_list = *start_of_list;
//     while (tmp_list != NULL)
//     {
//         if (!ft_strncmp(tmp_list->name_and_value[0], "SHLVL", 6))
//         {
//             if (tmp_list->name_and_value[1])
//             {
                
//             }
//         }
//         tmp_list = tmp_list->next;
//     }
//     return;
// }