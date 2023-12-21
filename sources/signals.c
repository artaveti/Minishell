
#include "lib_for_minishell.h"

void ft_sig_quit(int sig_num)
{
	g_exit_status_msh = 131;
	printf("Quit: %d\n", sig_num);
}



void ft_sig_int_new_line(int sig_num)
{
	struct termios term;

	tcgetattr(STDIN_FILENO, &term);
	printf("%lu\n", term.c_lflag);
	// if (sig_num == 2)
	// {
	// 	term.c_lflag &= ~ECHOCTL;
	// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// }
	printf("%lu\n", term.c_lflag);
	printf("(%d)\n", sig_num);
}



void ft_sig_int(int sig_num)
{
	(void)sig_num;
	g_exit_status_msh = 130;
	printf("\n");
}







// void	handleterm(int sig)
// {
// 	struct termios	term;

// 	tcgetattr(0, &term);
// 	if (sig == 0)
// 	{
// 		term.c_lflag &= ~ECHOCTL;
// 		tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	}
// }






// void	inthandle(int sig)
// {
// 	(void)sig;
// 	// write(1, "\n", 1);
// 	// rl_on_new_line();
// 	// rl_redisplay();
// 	printf("Hello!\n");
// }



// void	ft_signal(int handle)
// {
// 	handleterm(handle);
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, inthandle);
// }



// void	heredoc_sig(int sig)
// {
// 	(void)sig;
// 	g_exit_status_msh = 300;
// 	write(1, "\n", 1);
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// }



// void	heredoc_sig(int sig)////
// {
// //   const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
// //   write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 10);
// }
