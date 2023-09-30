
#include "lib_for_minishell.h"

void	ft_lstiter_printf(t_token_list	*token_list,
							int (f)(const char *, ...))
{
	t_token_list	*tmp;

	if (!token_list || !f)
		return ;
	tmp = token_list;
	while (tmp != NULL)
	{
		f("TMP_TYPE:::%d\n", tmp->type);
		tmp = tmp->next;
	}
	return ;
}
