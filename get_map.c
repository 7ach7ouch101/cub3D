/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:30:01 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 08:30:32 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_cond(char *str, int i)
{
	if ((str[0] == '\n') || (str[i] >= 'A'
			&& str[i] <= 'Z' && !(str[i + 1] == '1')
			&& !(str[i + 1] == '0') && !(str[i] == 'N')
			&& !(str[i] == 'E') && !(str[i] == 'W')
			&& !(str[i] == 'S'))
		|| (str[i] >= 'a' && str[i] <= 'z'
			&& !(str[i + 1] == '1') && !(str[i + 1] == '0')))
		return (1);
	else
		return (0);
}

int	check_line(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (str[++i])
	{
		if (check_cond(str, i) == 1)
			j++;
		if ((str[0] == ' ' && str[ft_strlen(str) - 2] == ' '))
		{
			while (str[i])
			{
				if ((str[i] == '1' && str[i + 1] == '1') || (str[i] == '0' && \
					str[i + 1] == '0') || (str[i] == 'N' || str[i + 1] == '0'\
					|| str[i + 1] == '1'))
					return (0);
				i++;
			}
			j++;
		}
	}
	if (j > 0)
		return (1);
	return (0);
}

void	check_conf(char *str, int i, t_tazi_data *data)
{
	if (ft_strncmp(&str[i], "WE", 2) == 0)
		data->wecount = data->wecount + 1;
	if (ft_strncmp(&str[i], "EA", 2) == 0)
		data->eacount = data->eacount + 1;
	if (ft_strncmp(&str[i], "SO", 2) == 0)
		data->socount = data->socount + 1;
	if (ft_strncmp(&str[i], "NO", 2) == 0)
		data->nocount = data->nocount + 1;
	if (str[i] == 'F')
		data->fcount = data->fcount + 1;
	if (str[i] == 'C')
		data->ccount = data->ccount + 1;
	if (!(data->ccount == 0 || data->ccount == 1))
		ft_error("Bad conf file", data);
	if (!(data->fcount == 0 || data->fcount == 1))
		ft_error("Bad conf file", data);
	if (!(data->wecount == 0 || data->wecount == 1))
		ft_error("Bad conf file", data);
	if (!(data->eacount == 0 || data->eacount == 1))
		ft_error("Bad conf file", data);
	if (!(data->socount == 0 || data->socount == 1))
		ft_error("Bad conf file", data);
	if (!(data->nocount == 0 || data->nocount == 1))
		ft_error("Bad conf file", data);
}

int	check_line1(char *str, t_tazi_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\n')
			i++;
		if (!str[i])
			return (0);
		if (!((ft_strncmp(&str[i], "WE", 2) == 0) || \
			(ft_strncmp(&str[i], "EA", 2) == 0)
				|| (ft_strncmp(&str[i], "SO", 2) == 0) || \
			(ft_strncmp(&str[i], "NO", 2) == 0)
				|| (str[i] == 'F') || (str[i] == 'C')))
			ft_error("Bad conf file", data);
		else
		{
			check_conf(str, i, data);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_map(int fd, t_tazi_data *data)
{
	char	*str;
	char	*str1;
	char	*map;

	str = get_next_line(fd);
	while (str && (check_line(str) == 1))
	{
		if (check_line1(str, data))
			ft_error("config lilo ghalat", data);
		free(str);
		str = get_next_line(fd);
	}
	str1 = get_next_line(fd);
	str = ft_strjoin(str, str1);
	free(str1);
	str1 = str;
	map = ft_calloc(1, 1);
	while (str1)
	{
		map = ft_strjoin(map, str1);
		free(str1);
		str1 = get_next_line(fd);
	}
	free(str1);
	return (map);
}
