/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_to_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:48:35 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/12 19:19:01 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

void ft_fork_for_heredoc(t_token_list *heredoc_list, t_environment_list *envp_list, int **fd_arr_heredoc);

int	ft_input_to_heredoc(t_token_list *heredoc_list,
		t_environment_list *envp_list, int **fd_arr_heredoc)
{
	pid_t	heredoc_fork;
	int		status_heredoc;

	status_heredoc = 0;
	heredoc_fork = fork();
	if (heredoc_fork == 0)
		ft_fork_for_heredoc(heredoc_list, envp_list, fd_arr_heredoc);
	waitpid(heredoc_fork, &status_heredoc, 0);
	WIFEXITED(status_heredoc);
	if (WEXITSTATUS(status_heredoc) == EXIT_HEREDOC_SIGINT)
	{
		g_exit_status_msh = EXIT_HEREDOC_SIGINT;
		return (EXIT_HEREDOC_SIGINT);
	}
	return (0);
}

void ft_fork_for_heredoc(t_token_list *heredoc_list, t_environment_list *envp_list, int **fd_arr_heredoc)
{
	int		i;
	
	signal(SIGINT, ft_sigint_heredoc); //// exit(EXIT_HEREDOC_SIGINT);
	i = 0;
	heredoc_list = heredoc_list->next;
	while (heredoc_list != NULL)
	{
		ft_readline_for_heredoc(heredoc_list->type, heredoc_list->value,
		fd_arr_heredoc[i][1], envp_list);
		i++;
		heredoc_list = heredoc_list->next;
	}
	exit(EXIT_SUCCESS);
}

void	ft_readline_for_heredoc(int type, char *string, int fd_num,
			t_environment_list *envp_list)
{
	char	*heredoc_line;

	heredoc_line = NULL;
	heredoc_line = readline("heredoc_minishell>");
	while (heredoc_line != NULL && (ft_strncmp(heredoc_line, string,
				ft_strlen(string))
			|| ft_strncmp(heredoc_line,
				string, ft_strlen(heredoc_line))))
	{
		if (type == HEREDOC_W)
			ft_change_string_for_heredoc(&heredoc_line, envp_list);
		write(fd_num, heredoc_line, ft_strlen(heredoc_line));
		write(fd_num, "\n", 1);
		free(heredoc_line);
		heredoc_line = readline("heredoc_minishell>");
	}
	free(heredoc_line);
	heredoc_line = NULL;
	return ;
}

// void  ft_readline_for_heredoc(int type, char *string, int fd_num, t_environment_list *envp_list)
// {
//   char *heredoc_line;

//   heredoc_line = NULL;
//   heredoc_line = readline("heredoc_minishell>");
//   if (g_exit_status_msh == 300) //signal heredoc stop ////
// 	{
//     printf("EXIT:300\n");
//     free(heredoc_line);
//     heredoc_line = NULL;
//     system("leaks minishell");
//     exit(1);
// 	}
//   while (heredoc_line != NULL && (ft_strncmp(heredoc_line, string, ft_strlen(string))
//           || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line))))
//           {
//             // printf("(%s)\n", heredoc_line);////
//             if (type == HEREDOC_W)
//                 ft_change_string_for_heredoc(&heredoc_line, envp_list);
//             write(fd_num, heredoc_line, ft_strlen(heredoc_line));
//             write(fd_num, "\n", 1);
//             free(heredoc_line);
//             heredoc_line = readline("heredoc_minishell>");
//             if (g_exit_status_msh == 300) //signal heredoc stop ////
//             {
//               printf("EXIT:300\n");
//               free(heredoc_line);
//               heredoc_line = NULL;
//               system("leaks minishell");
//               exit(1);
//             }
//           }
//           free(heredoc_line);
//           heredoc_line = NULL;
//     return ;
// }



//Create a heredoc using files
// #include "lib_for_minishell.h"

// void ft_readline_for_heredoc(char *string, int fd_heredoc);

// void ft_creat_heredoc(t_token_list *token_list)
// {
//   char *num_str;
//   char *filename;
//   int  fd_heredoc;
//   int  i;

//   i = 0;
//   while (token_list != NULL)
//   {
//     if (token_list->type == HEREDOC)
//     {
//       num_str = ft_itoa(i);
//       filename = ft_strjoin(".heredoc_minishell_", num_str);
//       fd_heredoc = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
//       ft_readline_for_heredoc(token_list->value, fd_heredoc);
//       free(token_list->value);
//       token_list->value = NULL;
//       token_list->value = ft_strdup(filename);
//       free(num_str);
//       free(filename);
//       close(fd_heredoc);
//       i++;
//     }
//     token_list = token_list->next;
//   }
//   return ;
// }



// void ft_readline_for_heredoc(char *string, int fd_heredoc)
// {
//   char *heredoc_line;

//   heredoc_line = readline("heredoc_minishell>");
//   while (ft_strncmp(heredoc_line, string, ft_strlen(string))
//           || ft_strncmp(heredoc_line, string, ft_strlen(heredoc_line)))
//           {
//             write(fd_heredoc, heredoc_line, ft_strlen(heredoc_line));
//             write(fd_heredoc, "\n", 1);
//             free(heredoc_line);
//             heredoc_line = readline("heredoc_minishell>");
//           }
//           free(heredoc_line);
//           heredoc_line = NULL;
//           return ;
// }

// fd_redir[3] = open(redir_list->value, O_RDONLY, 0644);
//close(fd_redir[3]);
//unlink(redir_list->value);


// void ft_dup2_stdin_heredoc(t_token_list *redir_list, int *fd_redir)
// {
//     char *error_str;
    
//     error_str = NULL;
//     if (redir_list->type == HEREDOC)
//     {
//       fd_redir[3] = open(redir_list->value, O_RDONLY, 0644);
//       dup2(fd_redir[3], STDIN_FILENO);
//       close(fd_redir[3]);
//       unlink(redir_list->value);
//     }
// return ;
// }