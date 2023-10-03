
#include "lib_for_minishell.h"

void	ft_list_iter_printf_for_token(t_token_list	*list,	int (f)(const char *, ...))
{
	t_token_list	*tmp;
	int i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		f("INDEX[%d]\n", i);
		f("TMP_TYPE:::%d\n", tmp->type);
		f("TMP_VALUE:::%s\n", tmp->value);
		f("TMP_NEXT:::%d\n", tmp->next > 0);
		tmp = tmp->next;
		i++;
	}
	return ;
}

void	ft_list_iter_printf_for_environment(t_environment_list	*list, int (f)(const char *, ...))
{
	t_environment_list	*tmp;
	int i;

	if (!list || !f)
		return ;
	tmp = list;
	i = 0;
	while (tmp != NULL)
	{
		f("INDEX[%d]\n", i);
		f("TMP_NAME_AND_VALUE[0]:::%s\n", tmp->name_and_value[0]);
		f("TMP_NAME_AND_VALUE[1]:::%s\n", tmp->name_and_value[1]);
		tmp = tmp->next;
		i++;
	}
	return ;
}