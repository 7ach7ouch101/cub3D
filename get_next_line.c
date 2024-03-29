/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 04:33:51 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 03:43:45 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = (char *)malloc(sizeof(char) * i + 2);
	else
		line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		line[i] = str[i];
	if (str[i] != '\n')
		line[i] = '\0';
	else
	{
		line[i] = '\n';
		line[++i] = '\0';
	}
	return (line);
}

char	*get_rest(char *str)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	i++;
	while (str[i] != '\0')
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*ft_strjoin_l(char *str, char *buff)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!str)
	{
		str = (char *) malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	if (!str || !buff)
		return (NULL);
	dest = (char *)malloc((ft_strlen(str) + ft_strlen(buff) + 1));
	if (!dest)
		return (NULL);
	while (str[++i] != '\0')
		dest[i] = str[i];
	while (buff[++j] != '\0')
		dest[i + j] = buff[j];
	dest[i + j] = '\0';
	free(str);
	return (dest);
}

char	*get_all_line(int fd, char *str)
{
	int		byte;
	char	*buff;

	byte = 1;
	buff = malloc(sizeof(char) * (1));
	if (!buff)
		return (NULL);
	while (byte != 0)
	{
		byte = read(fd, buff, 1);
		if (byte == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[byte] = '\0';
		str = ft_strjoin_l(str, buff);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*dest;
	static char	*str;

	if (fd < 0)
		return (NULL);
	str = get_all_line(fd, str);
	if (!str)
		return (NULL);
	dest = get_line(str);
	str = get_rest(str);
	return (dest);
}
