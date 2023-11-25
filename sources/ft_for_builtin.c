
#include "lib_for_minishell.h"

void ft_running_for_only_one_builtin(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int *check);

void ft_if_only_one_builtin(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int *check)
{
  char *tmp_str;
  
  if (!ft_strncmp(prog->argv_for_execve[0][0], "cd", 3)
      || !ft_strncmp(prog->argv_for_execve[0][0], "export", 7)
      || !ft_strncmp(prog->argv_for_execve[0][0], "unset", 6)
      || !ft_strncmp(prog->argv_for_execve[0][0], "exit", 5))
  {
    ft_running_for_only_one_builtin(tmp_redir_list, envp_list, prog, check);
    return ;
  }
  tmp_str = ft_strdup(prog->argv_for_execve[0][0]);
  ft_str_to_lowercase(tmp_str);
  if (!ft_strncmp(tmp_str, "echo", 5)
      || !ft_strncmp(tmp_str, "pwd", 4)
      || !ft_strncmp(tmp_str, "env", 4))
  {
    ft_str_to_lowercase(prog->argv_for_execve[0][0]);
    ft_running_for_only_one_builtin(tmp_redir_list, envp_list, prog, check);
    free(tmp_str);
    return ;
  }
  free(tmp_str);
  return ;
}



void ft_running_for_only_one_builtin(t_token_list *tmp_redir_list, t_environment_list **envp_list, t_for_prog *prog, int *check)
{
  int fd_redir[3];
  
  *check = BUILTIN_RETURN;
  ft_change_stdin_stdout_fd_redir(tmp_redir_list, fd_redir,
    prog->fd_arr_heredoc);
  ft_close_pipe_fd(prog->fd_arr_heredoc, prog->fd_quant_heredoc);
  ft_running_builtin(prog->argv_for_execve[0], envp_list,
      STDOUT_FILENO, BUILTIN_RETURN);
  return ;
}



void ft_running_builtin(char **array_of_strings, t_environment_list **envp_list, int fd_out, int exit_num)
{
//   else if (!ft_strncmp(array_of_strings[0], "echo", 5));
//     ft_echo();
//   else if (!ft_strncmp(array_of_strings[0], "cd", 3))
//     ft_cd();
//   else if (!ft_strncmp(array_of_strings[0], "pwd", 4))
//     ft_pwd();
  if (!ft_strncmp(array_of_strings[0], "export", 7))
    ft_export(array_of_strings, envp_list, exit_num);
  else if (!ft_strncmp(array_of_strings[0], "unset", 6))
    ft_unset(array_of_strings, envp_list, exit_num);
  else if (!ft_strncmp(array_of_strings[0], "env", 4))
    ft_env(array_of_strings, *envp_list, fd_out, exit_num);
//   else if (!ft_strncmp(array_of_strings[0], "exit", 5))
//     ft_exit();
  return ;
}
