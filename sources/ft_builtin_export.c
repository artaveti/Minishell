
#include "lib_for_minishell.h"

//// '#' sign in export ???
//// '=' sign in export ???
//// '+=' sign in export ???
//// krknvogh anunner

void ft_print_for_export(t_environment_list *envp);
int ft_check_name_for_export(char *str);
void ft_check_and_add_to_environment(t_environment_list **envp, char *str);
char *ft_creat_last_part_of_word_for_export(char *string, char *symbols);

void ft_export(t_environment_list **envp, t_for_prog *prog, char **array_of_strings, int fd_out)
{
    int i;
    
    i = 1;
    if (array_of_strings[i] == NULL)
    {
        ft_print_for_export(*envp);
        if (prog->check_builtin == BUILTIN_EXIT)
            exit(EXIT_SUCCESS);
        g_exit_status_msh = EXIT_SUCCESS;
        return ;
    }
    while(array_of_strings[i] != NULL)
    {
        dup2(fd_out, STDOUT_FILENO);
        if (ft_check_name_for_export(array_of_strings[i]) == 1)
        {
            g_exit_status_msh = EXIT_FAILURE;
            i++;
        }
        else
        {
            ft_check_and_add_to_environment(envp, array_of_strings[i]);
            i++;
        }
    }
    if (prog->check_builtin == BUILTIN_EXIT)
        exit(g_exit_status_msh);
    return ;
}



void ft_print_for_export(t_environment_list *envp)
{
    t_environment_list *tmp;

    tmp = envp;
    while(tmp != NULL)
    {
        if (tmp->envp_flag == 0)
            printf("declare -x %s\n", tmp->name_and_value[0]);
        else if (tmp->envp_flag == 1)
            printf("declare -x %s=\"%s\"\n", tmp->name_and_value[0], tmp->name_and_value[1]);
        tmp = tmp->next;
    }
    return ;
}



int ft_check_name_for_export(char *str)
{
    int i;

    if (!str || str == NULL)
        return (1);
    if (ft_isnum(str[0]) || str[0] == '+' || str[0] == '=')
    {
        printf(ERROR_FOR_EXPORT, str);
        return (1);
    }
    i = 0;
    while(str[i] != '\0')
    {
        if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
            return (0);
        if ((ft_strchr(WRONG_SIGN_EXPORT, str[i])) && str[i] != '\0')
        {
            printf(ERROR_FOR_EXPORT, str);
            return (1);
        }
        i++;
    }
    return (0);
}



void ft_check_and_add_to_environment(t_environment_list **envp, char *str)
{
    t_environment_list *tmp;
    t_environment_list *tmp_new;
    char *before_equal;
    char *after_equal;
    char *tmp_str;
    int flag_for_equal;
    int flag_for_plus;

    tmp = *envp;
    before_equal = NULL;
    after_equal = NULL;
    flag_for_equal = ft_char_find('=', str);
    flag_for_plus = 0;
    if (flag_for_equal == 1)
    {
        if (*(ft_strchr(str, '=') - 1) == '+')
            flag_for_plus = 1;
        if (flag_for_plus == 1)
            before_equal = ft_creat_first_part_of_word(str, "+");
        else
            before_equal = ft_creat_first_part_of_word(str, "=");
        after_equal = ft_creat_last_part_of_word_for_export(str, "=");
    }
    else
        before_equal = ft_strdup(str);
    while (tmp != NULL)
    {
        if (!ft_strncmp(tmp->name_and_value[0], before_equal, ft_strlen(before_equal) + 1))
        {
            if (flag_for_equal == 1 && flag_for_plus == 1)
            {   
                tmp_str = tmp->name_and_value[1];
                tmp->name_and_value[1] = ft_strjoin(tmp->name_and_value[1], after_equal);
                tmp->envp_flag = 1;
                free(tmp_str);
                free(before_equal);
                free(after_equal);
                return ;
            }
            else if (flag_for_equal == 1 && flag_for_plus == 0)
            {
                free(tmp->name_and_value[1]);
                tmp->name_and_value[1] = ft_strdup(after_equal);
                tmp->envp_flag = 1;
                free(before_equal);
                free(after_equal);
                return ;
            }
            else
            {
                // if (tmp->name_and_value != NULL && (!ft_strncmp(tmp->name_and_value[0], "OLDPWD", 7)
                //     || !ft_strncmp(tmp->name_and_value[0], "PWD", 4)) && tmp->name_and_value[1] != NULL)
                //     tmp->envp_flag = 1;
                // free(before_equal);
                // return ;
                if (!ft_strncmp(tmp->name_and_value[0], "OLDPWD", 7) || !ft_strncmp(tmp->name_and_value[0], "PWD", 4))
                    {
                        tmp->envp_flag = 0;
                        if (tmp->name_and_value[1] != NULL)
                            tmp->envp_flag = 1;
                    }
                // if ((!ft_strncmp(tmp->name_and_value[0], "OLDPWD", 7)
                //     || !ft_strncmp(tmp->name_and_value[0], "PWD", 4))
                //     && tmp->envp_flag == 2)
                //     tmp->envp_flag = 0;
                // if ((!ft_strncmp(tmp->name_and_value[0], "OLDPWD", 7)
                //     || !ft_strncmp(tmp->name_and_value[0], "PWD", 4))
                //     && tmp->name_and_value[1] != NULL)
                //     tmp->envp_flag = 1;
                free(before_equal);
                return ;
            }
        }
        tmp = tmp->next;
    }
    free(before_equal);
    free(after_equal);
    tmp_new = ft_list_new_for_environment(str);
    ft_list_add_back_for_environment(envp, tmp_new);
    return ;
}



char *ft_creat_last_part_of_word_for_export(char *string, char *symbols)
{
    char *last_part;
    int i;

    i = 0;
    while (string[i] != '\0')
    {
        if (ft_strchr(symbols, string[i]))
        {
            last_part = ft_strdup(&string[i + 1]);
            return (last_part);
        }
        i++;
    }
    return (NULL);
}
