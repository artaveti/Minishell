#include "lib_for_minishell.h"

int ft_for_cd_home_set(t_environment_list **envp, t_for_prog *prog, char **path, int fd_out);
int ft_for_cd_check_is_path_wrong(t_for_prog *prog, char **path);
void ft_for_cd_change_pwd_and_oldpwd_in_envp(t_environment_list **envp, t_for_prog *prog);

void ft_cd(t_environment_list **envp, t_for_prog *prog, char **array_of_strings, int fd_out)
{
    char *path;
    path = NULL;
    if (array_of_strings[1] == NULL)
    {
        if (ft_for_cd_home_set(envp, prog, &path, fd_out) == 1)
            return ;
    }
    else
        path = ft_strdup(array_of_strings[1]);
    if (ft_for_cd_check_is_path_wrong(prog, &path) == 1)
        return ;
    if (prog->pwd_str[0] == NULL)
        printf(ERROR_CD_GETCWD_CANT_ACCESS);
    free(prog->pwd_str[0]);
    prog->pwd_str[0] = getcwd(NULL, 0);
    if (prog->pwd_str[0] == NULL)
        prog->pwd_str[0] = ft_strdup(".");
    ft_for_cd_change_pwd_and_oldpwd_in_envp(envp, prog);
    free(path);
    if (prog->check_builtin == BUILTIN_EXIT)
        exit(EXIT_SUCCESS);
    g_exit_status_msh = EXIT_SUCCESS;
    return ;
}

void ft_for_cd_change_pwd_and_oldpwd_in_envp(t_environment_list **envp, t_for_prog *prog)
{
        t_environment_list *pwd_of_list;
        t_environment_list *tmp_node;

        tmp_node = find_node_by_name(*envp, "PWD");
        if (tmp_node == NULL || tmp_node->name_and_value[1] == NULL)
            change_node_by_name(envp,  "OLDPWD", "");
        else
            change_node_by_name(envp,  "OLDPWD", tmp_node->name_and_value[1]);
        if (tmp_node == NULL)
        {
            pwd_of_list = (t_environment_list *)malloc(sizeof(t_environment_list));
            pwd_of_list->name_and_value = (char **)malloc(sizeof(char *) * 3);
            pwd_of_list->envp_flag = 1;
            pwd_of_list->name_and_value[0] = ft_strdup("PWD");
            pwd_of_list->name_and_value[1] = NULL;
            pwd_of_list->name_and_value[2] = NULL;
            pwd_of_list->next = NULL;
            ft_list_add_back_for_environment(envp, pwd_of_list);
        }
        change_node_by_name(envp,  "PWD", prog->pwd_str[0]);
        return ;
}

int ft_for_cd_home_set(t_environment_list **envp, t_for_prog *prog, char **path, int fd_out)
{
            t_environment_list *tmp_node_home;

            tmp_node_home = find_node_by_name(*envp, "HOME");
            if (tmp_node_home == NULL || tmp_node_home->name_and_value[1] == NULL)
            {
                dup2(fd_out, STDOUT_FILENO);
                printf(ERROR_CD_HOME_DIR);
                if (prog->check_builtin == BUILTIN_EXIT) 
                    exit(EXIT_FAILURE);
                g_exit_status_msh = EXIT_FAILURE;
                return (1);
            }
            else if (tmp_node_home->name_and_value[1][0] == '\0')
            {
                if (prog->pwd_str[0] == NULL)
                    printf(ERROR_CD_GETCWD_CANT_ACCESS);
                if (prog->check_builtin == BUILTIN_EXIT)
                    exit(EXIT_SUCCESS);
                g_exit_status_msh = EXIT_SUCCESS;
                return (1);
            }
            else
                *path = ft_strdup(tmp_node_home->name_and_value[1]);
            return (0);
}

int ft_for_cd_check_is_path_wrong(t_for_prog *prog, char **path)
{
    if (((prog->pwd_str[0] == NULL || !ft_strncmp(prog->pwd_str[0], ".", 2)) && !ft_strncmp(*path, "..", 3)) || chdir(*path) != 0)
    {
        if (prog->pwd_str[0] == NULL)
            printf(ERROR_CD_GETCWD_CANT_ACCESS);
        printf(ERROR_CD_NO_FILE_OR_DIR, *path);
        free(*path);
        if (prog->check_builtin == BUILTIN_EXIT)
            exit(EXIT_FAILURE);
        g_exit_status_msh = EXIT_FAILURE;
        return (1);
    }
    return (0);
}
