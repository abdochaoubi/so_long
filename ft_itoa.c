/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:57:23 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/15 20:55:31 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include<stdlib.h>

int	nblen(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int	ft_pow(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		i *= 10;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	un;
	int				nlen;
	int				i;
	char			*p;

	nlen = nblen(n) + 1;
	p = malloc(nlen);
	if (!p)
		return (0);
	i = 0;
	un = n;
	if (n < 0)
	{
		p[i++] = '-';
		un = n * -1;
	}
	nlen = ft_pow(un);
	while (nlen)
	{
		p[i++] = un / (nlen) + '0';
		un = un - (un / (nlen)) * nlen;
		nlen /= 10;
	}
	p[i] = 0;
	return (p);
}
