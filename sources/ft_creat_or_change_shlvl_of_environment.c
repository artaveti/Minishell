#include "lib_for_minishell.h"

int ft_change_shlvl_to_zero(t_environment_list **list, long long long_long_num);
int ft_change_shlvl_to_num_or_null(t_environment_list **list, long long long_long_num);
int	ft_check_is_num_minus(const char *str);
void ft_additional_for_ft_change_shlvl_to_num_or_null( t_environment_list *tmp_list, long long long_long_num);

void ft_creat_or_change_shlvl_of_environment(t_environment_list **start_of_list)
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
    ft_list_creat_by_name_for_environment(start_of_list, 1, "SHLVL", "1");
    return;
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
        }
        else if (long_long_num <= 998 && long_long_num >= 0)
        {
            alp_num = ft_itoa((int)long_long_num + 1);
            free(tmp_list->name_and_value[1]);
            tmp_list->name_and_value[1] = ft_strdup(alp_num);
            free(alp_num);
        }
        else
            ft_additional_for_ft_change_shlvl_to_num_or_null(tmp_list, long_long_num);
        return (1);
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

void ft_additional_for_ft_change_shlvl_to_num_or_null( t_environment_list *tmp_list, long long long_long_num)
{
    printf(ERROR_SHLVL, long_long_num + 1);
    free(tmp_list->name_and_value[1]);
    tmp_list->name_and_value[1] = ft_strdup("1");
}