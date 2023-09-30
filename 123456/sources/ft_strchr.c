
#include "lib_for_minishell.h"

char	*ft_strchr(const char	*s, int c)
{
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
