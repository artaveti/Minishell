
#include "lib_for_minishell.h"

char	*ft_strjoin_space(char const	*s1, char const	*s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strl_spc(s2) + 1));
	if (!res)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
