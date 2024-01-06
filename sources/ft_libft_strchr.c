
#include "lib_for_minishell.h"

char	*ft_strchr(const char	*s, int c)
{
	if (!s || !*s)
		return (NULL);
	while (*s || *s == (char)c)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}



// char	*ft_strchr(const char	*s, int c)
// {
// 	int i;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] || s[i] == (char)c)
// 	{
// 		if (s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	return (NULL);
// }
