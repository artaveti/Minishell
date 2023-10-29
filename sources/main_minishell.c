
#include "lib_for_minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    char *input_str;
    char **envp_for_execve;
    char **path_arr;
    //int fd_quant;
    //pid_t pid;

    (void)argc;
    (void)argv;
    // i = 0;
    // while(envp[i] != NULL)
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }
    exit_status = 0;
    envp_list = ft_list_creat_environment(envp);
    //ft_list_iter_printf_for_environment(envp_list, printf);
    token_list = ft_list_creat_start_of_token();
    //path_arr = ft_make_path_arr(envp);
    while(1)
    {
        input_str = ft_readline();
        ft_lexer(input_str, token_list);
        //ft_list_iter_printf_for_token(token_list, printf);
        ft_parser(&token_list, envp_list);
        //ft_list_iter_printf_for_token(token_list, printf);
        envp_for_execve = ft_creat_envp_for_execve(envp_list);
        //ft_printf_double_arr(envp_for_execve);
        path_arr = ft_make_path_arr_for_execve(envp_for_execve);
        //ft_printf_double_arr(path_arr);
        ft_execve(token_list, envp_list, envp_for_execve, path_arr);
        // pid = fork();
        // if (pid == 0)
        // {
        //     ft_execve_firstfork(path_arr, &token_list, envp);
        //     exit(EXIT_SUCCESS);
        // }
        // wait(NULL);
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        ft_free_double_pointer_array(&envp_for_execve);
        ft_free_double_pointer_array(&path_arr);
        system("leaks minishell");
    }
    exit(EXIT_SUCCESS);
}



// int main(void)
// {
//     char **str;

//     str = (char **)malloc(sizeof(char *) * 2);
//     str[0] = (char *)malloc(sizeof(char) * 3);
//     str[0][0] = 'A';
//     str[0][1] = 'B';
//     str[0][2] = '\0';
//     str[1] = NULL;
    
//     //str[0] = NULL;
//     free(str[0]);
//     free(str);
//     system("leaks minishell");
//     return (0);
// }
