
#include "lib_for_minishell.h"

int	ft_list_length_for_token(t_token_list *list)
{
	int		i;
	t_token_list	*tmp;

	if (!list || list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}

int	ft_list_length_for_environment(t_environment_list *list)
{
	int		i;
	t_environment_list	*tmp;

	if (!list || list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp -> next;
		i++;
	}
	return (i);
}
