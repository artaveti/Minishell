
// #include <termios.h>
// #include <stdlib.h> //exit();

// void	inthandle(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
//     rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handleterm(int sig)
// {
// 	struct termios	term;

// 	tcgetattr(0, &term);
// 	if (sig == 0)
// 	{
// 		term.c_lflag &= ~ECHOCTL;
// 		tcsetattr(0, TCSANOW, &term);
// 	}
// }

// void	ft_signal(int handle)
// {
// 	handleterm(handle);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, inthandle);
// }


    //ft_signal(0);

    // if (!input_str[0])
    //     exit(0);