#include "lib_for_minishell.h"

void ft_creat_or_change_pwd_of_environment(t_environment_list **start_of_list);
void ft_list_creat_pwd_for_environment(t_environment_list **start_of_list, char *working_dir);

void ft_creat_or_change_pwd_of_environment(t_environment_list **start_of_list)
{
    //use getenv in this function
    t_environment_list *tmp_list;
    char *working_dir;

    working_dir = getcwd(NULL, 0);
    tmp_list = *start_of_list;
    while (tmp_list != NULL)
    {
        if (!ft_strncmp(tmp_list->name_and_value[0], "PWD", 4))
        {
            if (working_dir == NULL)
            {
                printf(ERROR_ENVP_GETCWD_CANT_ACCESS);
                return ;
            }
            else
            {
                tmp_list->envp_flag = 1;
                free(tmp_list->name_and_value[1]);
                tmp_list->name_and_value[1] = ft_strdup(working_dir);
                free(working_dir);
            }
            return ;
        }
        tmp_list = tmp_list->next;
    }
	ft_list_creat_pwd_for_environment(start_of_list, working_dir);
    free(working_dir);
    return ;
}


void ft_list_creat_pwd_for_environment(t_environment_list **start_of_list, char *working_dir)
{
    t_environment_list *tmp_pwd;
    if (working_dir == NULL)
    {
        printf(ERROR_ENVP_GETCWD_CANT_ACCESS);
        return ;
    }
    tmp_pwd = (t_environment_list *)malloc(sizeof(t_environment_list));
    tmp_pwd->name_and_value = (char **)malloc(sizeof(char *) * 3);
    tmp_pwd->envp_flag = 1;
    tmp_pwd->name_and_value[0] = ft_strdup("PWD");
    tmp_pwd->name_and_value[1] = ft_strdup(working_dir);
    tmp_pwd->name_and_value[2] = NULL;
    tmp_pwd->next = NULL;
    ft_list_add_back_for_environment(start_of_list, tmp_pwd);
	return ;















    t_environment_list *shlvl;
    
    shlvl = (t_environment_list *)malloc(sizeof(t_environment_list));
    shlvl->name_and_value = (char **)malloc(sizeof(char *) * 3);
    shlvl->envp_flag = 1;
	shlvl->name_and_value[0] = ft_strdup("SHLVL");
    shlvl->name_and_value[1] = ft_strdup("1");;
    shlvl->name_and_value[2] = NULL;
    shlvl->next = NULL;

    ft_list_add_back_for_environment(start_of_list, shlvl);
    return ;
}