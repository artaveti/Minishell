
#include "lib_for_minishell.h"

char *ft_readline(t_term *term)
{
    char *str;
    int i;

    str = readline("minishell> ");
    i = 0;
    if (str == NULL) //// this "if" for "ctrl + D"(null)
    {
        term->termios.c_lflag = term->num;
        tcsetattr(STDIN_FILENO, TCSANOW, &(term->termios));
        printf("minishell> exit\n");
        exit(EXIT_SUCCESS);
    }
    while(str[i] != '\0')
    {
        if(ft_strchr(WHITESPACES_RL, str[i]))
            i++;
        else
            break;
    }
    if (str[i] != '\0')
        add_history(str);
    return (str);
}
