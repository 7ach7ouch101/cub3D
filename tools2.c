/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:40:56 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 04:41:02 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(char *str)
{
	int	res;
	int	s;
	int	i;

	res = 0;
	s = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = s * -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + res * 10;
		i++;
	}
	return (res * s);
}

void	*ft_memset(void *s, int c, int n)
{
	unsigned char	*p;
	unsigned char	a;

	p = s;
	a = c;
	while (n--)
	{
		*p = a;
		p++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = s;
	ft_memset (p, 0, n);
}

void	*ft_calloc(int count, int size)
{
	void	*p;
	int		i;

	i = 0;
	p = malloc(size * count);
	if (!p)
		return (NULL);
	ft_bzero(p, (count * size));
	return (p);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
