
#include "lib_for_minishell.h"

int ft_count_envp_len(char *envp[]);
t_environment_list	*ft_list_new_for_environment(char *string_from_envp);
void ft_change_oldpwd_of_environment(t_environment_list **start_of_list);
void ft_change_shlvl_of_environment(t_environment_list **start_of_list);
int ft_change_shlvl_to_zero(t_environment_list **list, long long long_long_num);
int ft_change_shlvl_to_num_or_null(t_environment_list **list, long long long_long_num);
int	ft_check_is_num_minus(const char *str);
long long	ft_longlong_atoi_for_minishell(const char *str);
void ft_list_creat_shlvl_for_environment(t_environment_list **list);

////////////////////////////////////////////////////////////////////////////////////////////////////

t_environment_list   *ft_list_creat_environment(char *envp[])
{
    t_environment_list *start_of_list;
    t_environment_list *tmp;
    int envp_len;
    int i;

    start_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
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
    // ft_change_shlvl_of_environment(&start_of_list);
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

    tmp_list = *start_of_list;
    while (tmp_list != NULL)
    {
        if (!ft_strncmp(tmp_list->name_and_value[0], "OLDPWD", 7))
        {
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = NULL;
            return ;
        }
        tmp_list = tmp_list->next;
    }
    return ;
}



void ft_change_shlvl_of_environment(t_environment_list **start_of_list)
{
    t_environment_list *tmp_list;
    long long long_long_num ;

    tmp_list = *start_of_list;
    while (tmp_list != NULL)
    {
        if (!ft_strncmp(tmp_list->name_and_value[0], "SHLVL", 6))
        {
            long_long_num = ft_longlong_atoi_for_minishell(tmp_list->name_and_value[1]);
            if (ft_change_shlvl_to_zero(&tmp_list, long_long_num))
                return ;
            else if (ft_change_shlvl_to_num_or_null(&tmp_list, long_long_num))
                return ;
        }
        tmp_list = tmp_list->next;
    }
    ft_list_creat_shlvl_for_environment(&tmp_list);
    return;
}



void ft_list_creat_shlvl_for_environment(t_environment_list **list)
{
    t_environment_list *shlvl;

    shlvl = (t_environment_list *)malloc(sizeof(t_environment_list));
    shlvl->name_and_value = (char **)malloc(sizeof(char *) * 3);
	shlvl->name_and_value[0] = ft_strdup("SHLVL");
    shlvl->name_and_value[1] = ft_strdup("1");;
    shlvl->name_and_value[2] = NULL;
    shlvl->next = NULL;

    list[0] = shlvl;
    return ;
}



int ft_change_shlvl_to_zero(t_environment_list **list, long long long_long_num)
{
    t_environment_list *tmp_list;

    tmp_list = *list;
    if (ft_check_is_num_minus(tmp_list->name_and_value[1])
        || (long_long_num >= 2147483647 || long_long_num <= -2147483648))
        {
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = ft_strdup("0");
            return (1);
        }
        return (0);
}



int ft_change_shlvl_to_num_or_null(t_environment_list **list, long long long_long_num)
{
    t_environment_list *tmp_list;
    char *alp_num;

    tmp_list = *list;
    if (long_long_num < 2147483647 && long_long_num > -2147483648)
    {
        if (long_long_num == 999)
        {
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = ft_strdup("");
            return (1);
        }
        else if (long_long_num <= 998 && long_long_num >= 0)
        {
            alp_num = ft_itoa((int)long_long_num);
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = ft_strdup(alp_num);
            return (1);
        }
        else
        {
            printf("bash: warning: shell level (%lld) too high, resetting to 1\n", long_long_num + 1);
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = ft_strdup("1");
        }
    }
    return (0);
}



int	ft_check_is_num_minus(const char *str)
{
	if (str == NULL)
		return (0);
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
		return (1);
	return (0);
}



long long	ft_longlong_atoi_for_minishell(const char *str)
{
	long long	num;
	long long	minus;

	if (str == NULL)
		return (0);
	num = 0;
	minus = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
		str++;
	}
	if (*str != '\0' && !ft_isdigit(*str))
		return (0);
	return (num * minus);
}
