 #include "lib_for_minishell.h"

#include <limits.h>

long int atoi_limit(const char *str, int *limit) ;
int get_exit_status(long res);
int ft_is_digit(int c);
int parse_error(char *str, int *exit_status) ;

void exit_builtin(t_environment_list **env_list, int exit_status) ;
long int atoi_limit(const char *str, int *limit) ;


//ete commanda exel minchev ed u exit aranc argumentia, naxord cmd error berel dursa galis naxord commandi error codeov


void ft_exit(char **str, t_environment_list **envp, int exit_num) 
{
    int exit_status = 0;
    int i = 0; 
    int limit = 0;
    printf("Hi from exit\n");

    i = 1;
    if (!str[i])   //if no args
    {
        printf("exit\n");
        exit(exit_status_msh); //naxord statusov
    }
    while (str[i])
    {
        exit_status = atoi_limit(str[i], &limit);
        if (limit || parse_error(str[i], &exit_status))
        {
            printf("minishell: exit: %s: numeric argument required\n", str[i]);
            exit_status = 255;
            exit_status_msh = exit_status;
            if (exit_num == BUILTIN_EXIT)
                exit(exit_status_msh);
            // break;
        }
        i++;
    }
    if (i > 2)
    {
        printf("minishell: exit: too many arguments\n");
        exit_status = 1;
    }
    //exit_builtin(envp, atoi(str[i]));  //replace
    exit_builtin(envp, exit_status);
      if (exit_num == BUILTIN_EXIT) 
        exit(EXIT_SUCCESS);
    exit_status_msh = 0;
    return ;
   // printf("End of exit\n");
}

int get_exit_status(long res)
{
    long double num;
    long int_part;

    if (res >= 0 && res <= 255)
        return (res);
    num = (long double)res / 256;
    int_part = (long)num;
    num = (num - int_part) * 256;
    if (num >= ((long)num + 0.5))
        res = (long)num + 1;
    else
        res = (long)num;
    if (res < 0)
        return (256 + res);
    else
        return (res);
}



int ft_is_digit(int c)
 {
    return (c >= '0' && c <= '9');
}


int parse_error(char *str, int *exit_status) 
{
    int i = 0;
    while (str[i]) 
    {
        if (!(ft_is_digit(str[i]) || str[i] == '-'))  // kam limit long long intic meca.. hashvel leny ?
        {
            printf("exit\n");
            printf("minishell: exit: %s: numeric argument required\n", str);
            *exit_status = 255;
            return 1;
        }
        i++;
    }
    return 0;
}




void exit_builtin(t_environment_list **env_list, int exit_status) 
{
    while (*env_list != NULL) 
    {
        free((*env_list)->name_and_value);  
        t_environment_list *temp = *env_list;
        *env_list = (*env_list)->next;
        free(temp);
    }
    exit_status = get_exit_status(exit_status);
   
    exit(exit_status);
}


long int atoi_limit(const char *str, int *limit) 
{
    int i = 0;
    int sign = 1;
    long result = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
        i++;
    if (str[i] == '-') 
    {
        sign = -1;
        i++;
    } 
    else if (str[i] == '+') 
        i++;
    while (str[i] >= '0' && str[i] <= '9')
     {
        if (result > (LONG_MAX - (str[i] - '0')) / 10)
         {
            *limit = (sign == 1 && result > (LONG_MAX / 10)) ||
                     (sign == -1 && result < (LONG_MIN / 10));
            return sign * LONG_MAX;  
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return sign * result;
}