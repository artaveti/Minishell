#include "lib_for_minishell.h"

int n_set(char *str, int *suppress_nl);
size_t streq(char *s1, char *s2);  //ete datarka kam export chi (IF NOT EXPORT DO NOTHING)

void ft_echo(t_environment_list **envp, char **array_of_strings, int fd_out, int exit_num)
{
    int i;
    int suppress_nl = 0;
    int flag_word = 0;
    int flag_set = 0;

    (void)envp;
    (void)fd_out;
    i = 1;
    while(array_of_strings[i] != NULL)
    {
        if (ft_strlen(array_of_strings[i]) >= 2 && n_set(array_of_strings[i], &suppress_nl) && !flag_word) // flag set and not after_word
        {
            flag_set = suppress_nl;
            i++;
        }
        else
        {  
            if (!flag_set) //no flag is set and -n is just an arg
                suppress_nl = 0;
            flag_word = 1;
            printf("%s", array_of_strings[i]);
            if (array_of_strings[i + 1])
                printf(" ");
            i++;
        }
    }
    if (!suppress_nl)
        printf("\n");
    if (exit_num == BUILTIN_EXIT) 
        exit(EXIT_SUCCESS);
    exit_status_msh = 0;
        return ;
}




int n_set(char *str, int *suppress_nl)
{
    int i = 0;
  
    if (!str || !*str)
        return 0;
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



size_t streq(char *s1, char *s2)  //ete datarka kam export chi (IF NOT EXPORT DO NOTHING)
{
    int i = 0;
    if ((!s1 || !(*s1) || !s2 || !(*s2)) || (ft_strlen(s1) != ft_strlen(s2)))
        return  0;
    while (s1[i])
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}
