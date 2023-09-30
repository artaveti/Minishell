
#include "lib_for_minishell.h"

int main(int argc, char *arg[], char *envp[])
{
    char *input_str;
    char **path_arr;
    char **argv;
    pid_t pid;
    t_token_list token_list;
    int i;

    //token_list = malloc(sizeof(token_list));
    token_list.type = 100;
    token_list.value = NULL;
    token_list.next = NULL;
    (void)arg;
    i = argc;
    path_arr = ft_make_path_arr(envp);
    // i = 0;
    // while(path_arr[i] != NULL)
    // {
    //     printf("%s\n", path_arr[i]);
    //     i++;
    // }
    while(1)
    {
        input_str = ft_readline();
        ft_lexer(input_str, &token_list);

        ft_lstiter_printf(&token_list, printf);

        argv = ft_split(input_str, ' ');
        printf("PRINTF(%s)\n", argv[0]);
        free(input_str);
        pid = fork();
        if (pid == 0)
        {
            ft_execve_firstfork(path_arr, argv, envp);
            exit(EXIT_SUCCESS);
        }
        i = 0;
        while(argv[i] != NULL)
        {
            free(argv[i]);
            i++;
        }
        free(argv);
        //system("leaks minishell");
        wait(NULL);
    }
    // perror("EXECVE ERROR:::");
    // system("leaks minishell");
    exit(EXIT_SUCCESS);
}
