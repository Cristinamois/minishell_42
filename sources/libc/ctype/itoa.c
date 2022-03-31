/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:39 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:40 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	ft_isoperator(int c)
{
	return (c == '+' || c == '-');
}

int	__atoi(char *str)
{
	unsigned long long	sum;
	int					sign;
	int					digits;

	while (*str && __isspace(*str))
		++str;
	sign = 1;
	if (ft_isoperator(*str) && *str++ == '-')
		sign = -1;
	sum = 0;
	digits = 0;
	while (*str && __isdigit(*str))
	{
		sum = (sum * 10) + (*str++ - '0');
		++digits;
	}
	if (digits >= 18 || sum > 9223372036854775807)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return ((int)(sum * sign));
}

static void	ft_putnbr_stock(int n, char *str, int *i)
{
	if (n > 9)
	{
		ft_putnbr_stock(n / 10, str, i);
		ft_putnbr_stock(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

static size_t	ft_nbrlen(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*__itoa(int n)
{
	char	*str;
	int		i;
	int		nbr;

	nbr = n;
	str = allocate(sizeof(char) * (ft_nbrlen(nbr) + 1));
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	ft_putnbr_stock(nbr, str, &i);
	str[i] = '\0';
	return (str);
}
