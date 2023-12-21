#include "lib_for_minishell.h"

//echo -n not redirect to file ???

int     n_set(char *str, int *suppress_nl);
void    ft_print_for_echo(char **array_of_strings, int *flag_word, int *i);
void    ft_exit_for_echo(int *suppress_nl, int exit_num);

void ft_echo(char **array_of_strings, int exit_num)
{
    int i;
    int suppress_nl = 0;
    int flag_word = 0;
    int flag_set = 0;

    i = 1;
    while(array_of_strings[i] != NULL)
    {
        if (ft_strlen(array_of_strings[i]) >= 2 && n_set(array_of_strings[i], &suppress_nl) && !flag_word)
        {
            flag_set = suppress_nl;
            i++;
        }
        else
        {  
            if (!flag_set)
                suppress_nl = 0;
            ft_print_for_echo(array_of_strings, &flag_word, &i);
            i++;
        }
    }
    ft_exit_for_echo(&suppress_nl, exit_num);
    g_exit_status_msh = 0;
    return ;
}



int n_set(char *str, int *suppress_nl)
{
    int i = 0;

    if (!str || !*str)
        return (0);
    if (str[i] == '-')
    {
        i++;
        while (str[i] == 'n') 
            i++;
        if (str[i] == '\0')
        {
            *suppress_nl = 1;
            return 1; 
        }
        else 
            return 0;
    } 
    return 0;
}



void    ft_print_for_echo(char **array_of_strings, int *flag_word, int *i)
{
    *flag_word = 1;
    write(STDOUT_FILENO, array_of_strings[*i], ft_strlen(array_of_strings[*i]));
    // printf("%s", array_of_strings[*i]);
    if (array_of_strings[*i + 1])
    {
        write(STDOUT_FILENO, " ", 1);
        // printf(" ");
    }
    return ;
}



void    ft_exit_for_echo(int *suppress_nl, int exit_num)
{
    if (!*suppress_nl)
    {
        write(STDOUT_FILENO, "\n", 1);
        // printf("\n");
    }
    // fflush(STDIN_FILENO);
    if (exit_num == BUILTIN_EXIT) 
        exit(EXIT_SUCCESS);
    return ;
}
