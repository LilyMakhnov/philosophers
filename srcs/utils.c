/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:11:53 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 11:12:03 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nbr)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nbr))
	{
		if (res >= 922337203685477580 && sign == 1)
			return (-1);
		if (res >= 922337203685477580 && sign == -1)
			return (0);
		res = res * 10 + *nbr++ - '0';
	}
	return (sign * res);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	len_dest;

	len_dest = 0;
	while (dest[len_dest])
		len_dest++;
	i = 0;
	while (src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

void	ft_nbr_to_str(char *str, long long nb)
{
	char	a;

	if (nb > 9)
	{
		ft_nbr_to_str(str, nb / 10);
		nb = nb % 10;
	}
	a = nb + '0';
	ft_strcat(str, &a);
}
