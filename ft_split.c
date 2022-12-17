/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:31:31 by aechaoub          #+#    #+#             */
/*   Updated: 2022/12/17 14:55:35 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./getsky/get_next_line.h"


void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (0);
	p = malloc(count * size);
	if (!p)
		return (0);
	ft_bzero(p, count * size);
	return ((void *)p);
}


int	htimes(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (!c)
		return (1);
	while (s[i] == c)
		i++;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != 0)
				nb++;
		}
		else
			i++;
	}
	return (nb + 1);
}

int	untilc(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**ammr(char const *s, char c, int size, char **p)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (i < size)
	{
		while (s[j] && s[j] == c)
			j++;
		p[i] = ft_calloc((untilc(s + j, c) + 1), sizeof(char));
		x = 0;
		while (s[j] && s[j] != c)
		{
			p[i][x] = s[j];
			j++;
			x++;
		}
		p[i][x] = 0;
		i++;
	}
	p[i] = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**p;

	if (!s)
		return (NULL);
	size = htimes(s, c);
	p = ft_calloc((size + 1), sizeof(char const *));
	if (!p)
		return (0);
	if (!*s)
		return (p);
	p = ammr(s, c, size, p);
	// printf("%s    suuu\n",p[1]);

	return (p);
}
