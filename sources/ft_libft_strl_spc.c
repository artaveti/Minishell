
#include "lib_for_minishell.h"

size_t	ft_strl_spc(const	char *s)
{
	size_t	i;

	i = 0;
	if (!s[0])
		return (0);
	while (s[i] != '\0' && s[i] != ' ')
		i++;
	return (i);
}
