
#include "lib_for_minishell.h"

int ft_atoi_for_long_long(char *str, long long *result);

void ft_exit(char **str, int fd_out, int exit_num) 
{
    long long exit_atoi;
    int atoi_res;
    int i;

    (void)exit_num;
    dup2(fd_out, STDOUT_FILENO);
    i = 1;
    if (str[i] == NULL)
    {
        printf(PRINT_EXIT);
        exit(exit_status_msh);
    }
    exit_atoi = 0;
    atoi_res = ft_atoi_for_long_long(str[i], &exit_atoi);
    if (atoi_res == 1 && str[i + 1] != NULL)
    {
        printf (PRINT_EXIT);
        printf(ERROR_MANY_ARG);
        exit_status_msh = EXIT_FAILURE;
        return ;
    }
    else if (atoi_res == 0)
    {
        printf (PRINT_EXIT);
        printf(ERROR_NUM_ARG_REQ, str[i]);
        exit_status_msh = 255;
        exit(exit_status_msh);
    }
    else
    {
        printf (PRINT_EXIT);
        if (exit_atoi >= 0)
            exit_status_msh = exit_atoi % 256;
        else
            exit_status_msh = 256 + exit_atoi % 256;
        exit(exit_status_msh);
    }
    return ;
}



int ft_atoi_for_long_long(char *str, long long *result)
{
    unsigned long long   num;
    unsigned long long   min;
	int         minus;

	num = 0;
    min = 9223372036854775808ULL;
	minus = 1;
	while (*str != '\0' && (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		minus *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
	{
		num = num * 10 + *str - 48;
        if ((minus == 1 && num > LLONG_MAX)
            || (minus == -1 && num > min))
            return (0);
		str++;
	}
    if (*str != '\0')
        return (0);
    *result = num * minus;
	return (1);
}
