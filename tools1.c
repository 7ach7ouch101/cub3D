/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 04:33:39 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/15 08:02:22 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memcpy(char	*dst, char *src, int n)
{
	char	*s;
	char		*d;

	d = dst;
	s = src;
	if (!src && !dst)
		return (NULL);
	while (n--)
	{
		*d = *s;
		d++;
		s++;
	}

	return (dst);
}

int	words(char *str, char c)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c && str[i + 1] == c)
			|| (str[i + 1] == '\0' && str[i] != c))
			u++;
		i++;
	}
	return (u);
}

void	*freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

char	**fillarr(char **p, char *s, char c)
{
	int	j;
	int	e;

	e = 0;
	while (*s)
	{
		j = 0;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (j > 0)
		{
			p[e] = (char *)malloc((j + 1) * sizeof(char));
			if (!p)
				return (freee(p));
			ft_memcpy(p[e], s, j);
			p[e][j] = '\0';
			e++;
			s = s + j;
		}
		else
			s++;
	}
	p[e] = NULL;
	return (p);
}

char	**ft_split(char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)malloc(((words(s, c) + 1) * sizeof(char *)));
	if (!p)
		return (NULL);
	p = fillarr(p, s, c);
	return (p);
}

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