
#include "lib_for_minishell.h"

int	ft_isalpha(int sign)
{
	if ((sign >= 'a' && sign <= 'z') || (sign >= 'A' && sign <= 'Z') )
		return (1);
	return (0);
}



int	ft_isnum(int sign)
{
	if (sign >= '0' && sign <= '9')
		return (1);
	return (0);
}



int	ft_isalnum(int sign)
{
	if (ft_isalpha(sign) || ft_isnum(sign))
		return (1);
	return (0);
}
