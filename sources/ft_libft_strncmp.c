
#include "lib_for_minishell.h"

size_t	ft_strncmp(const char	*s1, const char	*s2, size_t	n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (0);
	while (*s1 && *s2 && i < n - 1)
	{
		if ((unsigned char) *s1 == (unsigned char) *s2)
		{
			s1++;
			s2++;
			i++;
		}
		else
			return ((unsigned char) *s1 - (unsigned char) *s2);
	}
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
