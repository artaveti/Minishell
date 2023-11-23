
#include "lib_for_minishell.h"

void	*ft_memmove(void	*dst, const void	*src, size_t	len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	if (dst > src)
	{
		i = len;
		while (i--)
		{
			((unsigned char *)(dst))[i] = ((unsigned char *)(src))[i];
		}
		return (dst);
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((unsigned char *)(dst))[i] = ((unsigned char *)(src))[i];
			i++;
		}
		return (dst);
	}
}
