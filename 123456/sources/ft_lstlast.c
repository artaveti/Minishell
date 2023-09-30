
#include "lib_for_minishell.h"

t_token_list	*ft_lstlast(t_token_list	*lst)
{
	t_token_list	*res;
	if (!lst)
		return (0);
	res = lst;
	while (res->next != NULL)
		res = res->next;
	return (res);
}
