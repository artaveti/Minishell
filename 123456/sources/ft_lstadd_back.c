
#include "lib_for_minishell.h"

void	ft_lstadd_back(t_token_list	**lst, t_token_list	*new)
{
	t_token_list	*tmp;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = ft_lstlast(*lst);
	tmp->next = new;
	return ;
}
