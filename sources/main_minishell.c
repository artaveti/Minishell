
#include "lib_for_minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    t_environment_list *envp_list;
    t_token_list *token_list;
    char *input_str;
    int parser_num;
    //int status;

    (void)argc;
    (void)argv;
    // i = 0;
    // while(envp[i] != NULL)
    // {
    //     printf("%s\n", envp[i]);
    //     i++;
    // }
    envp_list = ft_list_creat_environment(envp);
    //ft_list_iter_printf_for_environment(envp_list, printf);
    token_list = ft_list_creat_start_of_token();
    //path_arr = ft_make_path_arr(envp);
    exit_status = 0;
    while(1)
    {
        input_str = ft_readline(); //if input_str == NULL, must go to while
        ft_lexer(input_str, token_list);
        //ft_list_iter_printf_for_token(token_list, printf);
        parser_num = ft_parser(&token_list, envp_list);
        //printf("\n\n\n");
        //ft_list_iter_printf_for_token(token_list, printf);
        if(input_str[0] != '\0' && parser_num != EXIT_ERROR_SYNTAX) // 258
            ft_program(token_list, envp_list);
        // while (wait(&status) != -1)
        // {
            //printf("pid_arr[I][%d](%d)\n", i, pid_arr[i]);
            //waitpid(pid_arr[i], &status, 0);
            //printf("I am here\n");
            // WIFEXITED(status);
            // exit_status = WEXITSTATUS(status);
            //i++;
        // }
		// ;
        free(input_str);
        ft_list_free_for_token(&token_list->next);
        //system("leaks minishell");
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



// int main(void)
// {
//     int i;

//     i = 1;

//     printf("%d\n", i / 2);
//     return (0);
// }