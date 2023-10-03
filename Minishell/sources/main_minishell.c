
#include "lib_for_minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *input_str;
    char **path_arr;
    pid_t pid;
    t_environment_list *envp_list;
    t_token_list *token_list;

    (void)argc;
    (void)argv;

    envp_list = ft_list_creat_environment(envp);
    ft_list_iter_printf_for_environment(envp_list, printf);
    token_list = ft_list_creat_start_token();
    path_arr = ft_make_path_arr(envp);
    while(1)
    {
        input_str = ft_readline();
        ft_lexer(input_str, token_list);
        ft_list_iter_printf_for_token(token_list, printf);
        free(input_str);
        pid = fork();
        if (pid == 0)
        {
            ft_execve_firstfork(path_arr, &token_list, envp);
            exit(EXIT_SUCCESS);
        }
        wait(NULL);
        ft_list_free_for_token(&token_list->next);
        //system("leaks minishell");
    }
    exit(EXIT_SUCCESS);
}
