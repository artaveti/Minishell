
#include "lib_for_minishell.h"

t_environment_list *ft_list_creat_start_of_environment(char *envp[]);
int ft_count_envp_len(char *envp[]);
void ft_additional_for_ft_list_new_for_environment(t_environment_list	*result, char *string_from_envp);

t_environment_list   *ft_list_creat_environment(char *envp[])
{
    t_environment_list *tmp;
    t_environment_list *start_of_list;
    int envp_len;
    int i;

    if (!envp || envp == NULL || !envp[0] || envp[0] == NULL)
        return (NULL);
    start_of_list = ft_list_creat_start_of_environment(envp);
    envp_len = ft_count_envp_len(envp);
    i = 1;
    while(i < envp_len)
    {
        tmp = ft_list_new_for_environment(envp[i]);
        ft_list_add_back_for_environment(&start_of_list, tmp);
        i++;
    }
    ft_creat_or_change_shlvl_of_environment(&start_of_list);
    ft_creat_or_change_pwd_of_environment(&start_of_list);
    ft_creat_or_change_oldpwd_of_environment(&start_of_list);
    return (start_of_list);
}

t_environment_list *ft_list_creat_start_of_environment(char *envp[])
{
    t_environment_list *start_of_list;

    start_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
    start_of_list->name_and_value = (char **)malloc(sizeof(char *) * 3);
    if (!ft_char_find('=', envp[0]))
    {
        start_of_list->envp_flag = 0;
        start_of_list->name_and_value[0] = ft_strdup(envp[0]);
        start_of_list->name_and_value[1] = NULL;
    }
    else
    {
        start_of_list->envp_flag = 1;
        start_of_list->name_and_value[0] = ft_creat_first_part_of_word(envp[0], "=");
        start_of_list->name_and_value[1] = ft_strdup(ft_strchr(envp[0], '=') + 1);
    }
    start_of_list->name_and_value[2] = NULL;
    start_of_list->next = NULL;
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
    result->name_and_value = (char **)malloc(sizeof(char *) * 3);
    if(!ft_char_find('=', string_from_envp))
    {
        result->envp_flag = 0;
	    result->name_and_value[0] = ft_strdup(string_from_envp);
        result->name_and_value[1] = NULL;
    }
    else
        ft_additional_for_ft_list_new_for_environment(result, string_from_envp);
    result->name_and_value[2] = NULL;
    result->next = NULL;
	return (result);
}

void ft_additional_for_ft_list_new_for_environment(t_environment_list	*result, char *string_from_envp)
{
    result->envp_flag = 1;
    if (*(ft_strchr(string_from_envp, '=') - 1) == '+')
        result->name_and_value[0] = ft_creat_first_part_of_word(string_from_envp, "+");
    else
        result->name_and_value[0] = ft_creat_first_part_of_word(string_from_envp, "=");
    result->name_and_value[1] = ft_strdup(ft_strchr(string_from_envp, '=') + 1);
}
