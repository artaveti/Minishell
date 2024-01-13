/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_builtin_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artaveti <artaveti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:53:14 by artaveti          #+#    #+#             */
/*   Updated: 2024/01/13 17:28:48 by artaveti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_for_minishell.h"

int		ft_check_if_cd_export_unset_exit(t_environment_list **envp_list,
			t_for_prog *prog, t_token_list *tmp_redir_list, int fd_out);
int		ft_check_if_echo_pwd_env(t_environment_list **envp_list,
			t_for_prog *prog, t_token_list *tmp_redir_list, int fd_out);
void	ft_free_and_str_to_lowercase_for_echo_pwd_env(t_for_prog *prog,
			char **tmp_str);
void	ft_running_for_only_one_builtin(t_environment_list **envp_list,
			t_for_prog *prog, t_token_list *tmp_redir_list);

void	ft_check_if_builtin_run(t_environment_list **envp_list,
			t_for_prog *prog, t_token_list *tmp_redir_list, int fd_out)
{
	int	result_num;

	result_num = 0;
	result_num = ft_check_if_cd_export_unset_exit(envp_list, prog,
			tmp_redir_list, fd_out);
	if (result_num == 0)
		return ;
	result_num = ft_check_if_echo_pwd_env(envp_list, prog,
			tmp_redir_list, fd_out);
	return ;
}

int	ft_check_if_cd_export_unset_exit(t_environment_list **envp_list,
		t_for_prog *prog, t_token_list *tmp_redir_list, int fd_out)
{
	if (!ft_strncmp(prog->argv_for_execve[prog->index][0], "cd", 3)
			|| !ft_strncmp(prog->argv_for_execve[prog->index][0], "export", 7)
			|| !ft_strncmp(prog->argv_for_execve[prog->index][0], "unset", 6)
			|| !ft_strncmp(prog->argv_for_execve[prog->index][0], "exit", 5))
	{
		if (prog->fd_quant_pipe == 0)
		{
			prog->check_builtin = BUILTIN_RETURN;
			ft_running_for_only_one_builtin(envp_list, prog, tmp_redir_list);
			return (0);
		}
		else
		{
			ft_running_builtin(envp_list, prog,
				prog->argv_for_execve[prog->index], fd_out);
			return (0);
		}
	}
	return (1);
}

int	ft_check_if_echo_pwd_env(t_environment_list **envp_list, t_for_prog *prog,
		t_token_list *tmp_redir_list, int fd_out)
{
	char	*tmp_str;

	tmp_str = ft_strdup(prog->argv_for_execve[prog->index][0]);
	ft_str_to_lowercase(tmp_str);
	if (!ft_strncmp(tmp_str, "echo", 5) || !ft_strncmp(tmp_str, "pwd", 4)
		|| !ft_strncmp(tmp_str, "env", 4))
	{
		if (prog->fd_quant_pipe == 0)
		{
			prog->check_builtin = BUILTIN_RETURN;
			ft_free_and_str_to_lowercase_for_echo_pwd_env(prog, &tmp_str);
			ft_running_for_only_one_builtin(envp_list, prog, tmp_redir_list);
			return (0);
		}
		else
		{
			ft_free_and_str_to_lowercase_for_echo_pwd_env(prog, &tmp_str);
			ft_running_builtin(envp_list, prog,
				prog->argv_for_execve[prog->index], fd_out);
			return (0);
		}
	}
	free(tmp_str);
	return (1);
}

void	ft_free_and_str_to_lowercase_for_echo_pwd_env(t_for_prog *prog,
			char **tmp_str)
{
	free(*tmp_str);
	ft_str_to_lowercase(prog->argv_for_execve[prog->index][0]);
	return ;
}



  // if (!ft_strncmp(prog->argv_for_execve[prog->index][0], "cd", 3)
  //     || !ft_strncmp(prog->argv_for_execve[prog->index][0], "export", 7)
  //     || !ft_strncmp(prog->argv_for_execve[prog->index][0], "unset", 6)
  //     || !ft_strncmp(prog->argv_for_execve[prog->index][0], "exit", 5))
  // {
  //   if(prog->fd_quant_pipe == 0)
  //   {
  //     prog->check_builtin = BUILTIN_RETURN;
  //     ft_running_for_only_one_builtin(envp_list, prog, tmp_redir_list);
  //     return ;
  //   }
  //   else
  //   {
  //     ft_running_builtin(envp_list, prog, prog->argv_for_execve[prog->index], fd_out);
  //     return ;
  //   }
  // }

  // char *tmp_str;
  // tmp_str = ft_strdup(prog->argv_for_execve[prog->index][0]);
  // ft_str_to_lowercase(tmp_str);
  // if (!ft_strncmp(tmp_str, "echo", 5)
  //     || !ft_strncmp(tmp_str, "pwd", 4)
  //     || !ft_strncmp(tmp_str, "env", 4))
  // {
  //   if(prog->fd_quant_pipe == 0)
  //   {
  //     prog->check_builtin = BUILTIN_RETURN;
  //     free(tmp_str);
  //     ft_str_to_lowercase(prog->argv_for_execve[prog->index][0]);
  //     ft_running_for_only_one_builtin(envp_list, prog, tmp_redir_list);
  //     return ;
  //   }
  //   else 
  //   {
  //     free(tmp_str);
  //     ft_str_to_lowercase(prog->argv_for_execve[prog->index][0]);
  //     ft_running_builtin(envp_list, prog, prog->argv_for_execve[prog->index], fd_out);
  //     return ;
  //   }
  // }
  // free(tmp_str);
  // return ;



// void ft_if_only_one_builtin(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog)
// {
//   char *tmp_str;
//   if (!ft_strncmp(prog->argv_for_execve[0][0], "cd", 3)
//       || !ft_strncmp(prog->argv_for_execve[0][0], "export", 7)
//       || !ft_strncmp(prog->argv_for_execve[0][0], "unset", 6)
//       || !ft_strncmp(prog->argv_for_execve[0][0], "exit", 5))
//   {
//     ft_running_for_only_one_builtin(tmp_redir_list, envp_list, prog);
//     return ;
//   }
//   tmp_str = ft_strdup(prog->argv_for_execve[0][0]);
//   ft_str_to_lowercase(tmp_str);
//   if (!ft_strncmp(tmp_str, "echo", 5)
//       || !ft_strncmp(tmp_str, "pwd", 4)
//       || !ft_strncmp(tmp_str, "env", 4))
//   {
//     ft_str_to_lowercase(prog->argv_for_execve[0][0]);
//     ft_running_for_only_one_builtin(tmp_redir_list, envp_list, prog);
//     free(tmp_str);
//     return ;
//   }
//   free(tmp_str);
//   return ;
// }



// void ft_if_not_only_one_builtin(t_environment_list **envp_list, t_for_prog *prog, int fd_out, int exit_num)
// {
//   char *tmp_str;
//   if (!ft_strncmp(prog->argv_for_execve[prog->index][0], "cd", 3)
//       || !ft_strncmp(prog->argv_for_execve[prog->index][0], "export", 7)
//       || !ft_strncmp(prog->argv_for_execve[prog->index][0], "unset", 6)
//       || !ft_strncmp(prog->argv_for_execve[prog->index][0], "exit", 5))
//   {
//     ft_running_builtin(prog->argv_for_execve[prog->index], envp_list, fd_out, exit_num);
//     return ;
//   }
//   tmp_str = ft_strdup(prog->argv_for_execve[prog->index][0]);
//   ft_str_to_lowercase(tmp_str);
//   if (!ft_strncmp(tmp_str, "echo", 5)
//       || !ft_strncmp(tmp_str, "pwd", 4)
//       || !ft_strncmp(tmp_str, "env", 4))
//   {
//     free(tmp_str);
//     ft_str_to_lowercase(prog->argv_for_execve[prog->index][0]);
//     ft_running_builtin(prog->argv_for_execve[prog->index], envp_list, fd_out, exit_num);
//     return ;
//   }
//   free(tmp_str);
//   return ;
// }



// void ft_if_not_only_one_builtin(char **array_of_strings, t_environment_list **envp_list, int fd_out, int exit_num)
// {
//   char *tmp_str;
//   if (!ft_strncmp(array_of_strings[0], "cd", 3)
//       || !ft_strncmp(array_of_strings[0], "export", 7)
//       || !ft_strncmp(array_of_strings[0], "unset", 6)
//       || !ft_strncmp(array_of_strings[0], "exit", 5))
//   {
//     ft_running_builtin(array_of_strings, envp_list, fd_out, exit_num);
//     return ;
//   }
//   tmp_str = ft_strdup(array_of_strings[0]);
//   ft_str_to_lowercase(tmp_str);
//   if (!ft_strncmp(tmp_str, "echo", 5)
//       || !ft_strncmp(tmp_str, "pwd", 4)
//       || !ft_strncmp(tmp_str, "env", 4))
//   {
//     free(tmp_str);
//     ft_str_to_lowercase(array_of_strings[0]);
//     ft_running_builtin(array_of_strings, envp_list, fd_out, exit_num);
//     return ;
//   }
//   free(tmp_str);
//   return ;
// }
