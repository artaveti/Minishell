
#include "lib_for_minishell.h"

t_environment_list	*ft_list_new_for_environment(char *string_from_envp)
{
	t_environment_list	*result;

	result = (t_environment_list *)malloc(sizeof(t_environment_list));
	if (!result)
		return (NULL);
	result->name_and_value = ft_split(string_from_envp, '=');
	result->next = NULL;
	return (result);
}
