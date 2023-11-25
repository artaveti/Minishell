
#include "lib_for_minishell.h"

void	ft_str_to_lowercase(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return ;
}
