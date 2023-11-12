
#include "lib_for_minishell.h"
// ete minus intic avela == 0
// ete minus inta == 0
// ete ka inchvor tar, kam erku hat plyus, kam erku hat minus == 1

int ft_count_envp_len(char *envp[]);
t_environment_list	*ft_list_new_for_environment(char *string_from_envp);
void ft_change_shlvl_of_environment(t_environment_list **start_of_list);
void ft_change_oldpwd_of_environment(t_environment_list **start_of_list);

t_environment_list   *ft_list_creat_environment(char *envp[])
{
    t_environment_list *start_of_list;
    t_environment_list *tmp;
    int envp_len;
    int i;

    if (!envp || !envp[0] || envp == NULL || envp[0] == NULL)
        return (NULL);
    start_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
    start_of_list->envp_flag = 1;
    start_of_list->name_and_value = (char **)malloc(sizeof(char *) * 3);
    start_of_list->name_and_value[0] = ft_creat_first_part_of_word(envp[0], "=");
    start_of_list->name_and_value[1] = ft_strdup(ft_strchr(envp[0], '=') + 1);
    start_of_list->name_and_value[2] = NULL;
    start_of_list->next = NULL;
    envp_len = ft_count_envp_len(envp);
    i = 1;
    while(i < envp_len)
    {
        tmp = ft_list_new_for_environment(envp[i]);
        ft_list_add_back_for_environment(&start_of_list, tmp);
        i++;
    }
    ft_change_shlvl_of_environment(&start_of_list);
    ft_change_oldpwd_of_environment(&start_of_list);
    return (start_of_list);
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
    result->envp_flag = 1;
    result->name_and_value = (char **)malloc(sizeof(char *) * 3);
    if(!ft_char_find('=', string_from_envp))
    {
	    result->name_and_value[0] = ft_strdup(string_from_envp);
        result->name_and_value[1] = NULL;
        result->name_and_value[2] = NULL;
    }
    else
    {
        result->name_and_value[0] = ft_creat_first_part_of_word(string_from_envp, "=");
        result->name_and_value[1] = ft_strdup(ft_strchr(string_from_envp, '=') + 1);
        result->name_and_value[2] = NULL;
    }
    result->next = NULL;
	return (result);
}



void ft_change_oldpwd_of_environment(t_environment_list **start_of_list)
{
    t_environment_list *tmp_list;
    t_environment_list *tmp_oldpwd;

    tmp_list = *start_of_list;
    while (tmp_list != NULL)
    {
        if (!ft_strncmp(tmp_list->name_and_value[0], "OLDPWD", 7))
        {
            tmp_list->envp_flag = 0;
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = NULL;
            return ;
        }
        tmp_list = tmp_list->next;
    }
    tmp_oldpwd = (t_environment_list *)malloc(sizeof(t_environment_list));
    tmp_oldpwd->name_and_value = (char **)malloc(sizeof(char *) * 3);
    tmp_oldpwd->envp_flag = 0;
    tmp_oldpwd->name_and_value[0] = ft_strdup("OLDPWD");
    tmp_oldpwd->name_and_value[1] = NULL;
    tmp_oldpwd->name_and_value[2] = NULL;
    tmp_oldpwd->next = NULL;
    ft_list_add_back_for_environment(start_of_list, tmp_oldpwd);
    return ;
}
