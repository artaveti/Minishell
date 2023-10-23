
#include "lib_for_minishell.h"

char	*ft_strdup(const char	*s1)
{
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dup)
		return (0);
	ft_strlcpy(dup, s1, ft_strlen(s1) + 1);
	return (dup);
}
