
#include "lib_for_minishell.h"

static void	ft_reverse(char	*res)
{
	int		i;
	int		j;
	char	tab;

	i = 0;
	j = ft_strlen(res) - 1;
	if (res[0] == '-')
		i = 1;
	while (i < j)
	{
		tab = res[i];
		res[i] = res[j];
		res[j] = tab;
		i++;
		j--;
	}
	res[ft_strlen(res)] = '\0';
}

static char	*ft_min_num(char	*res)
{
	int	i;

	i = 0;
	while (i < 11)
	{
		res[i] = "-2147483648"[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static char	*ft_zero(char	*res)
{
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static int	ft_letter_count(int n)
{
	int	count;
	int	nbr;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	count = 0;
	nbr = n;
	if (n < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		count++;
	}
	if (n < 0)
		count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_letter_count(n) + 1));
	if (!res)
		return (0);
	if (n == -2147483648)
		return (ft_min_num(res));
	if (n == 0)
		return (ft_zero(res));
	i = 0;
	if (n < 0)
	{
		n *= -1;
		res[i++] = '-';
	}
	while (n > 0)
	{
		res[i++] = "0123456789"[n % 10];
		n /= 10;
	}
	res[i] = '\0';
	ft_reverse(res);
	return (res);
}
