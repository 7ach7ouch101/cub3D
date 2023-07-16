/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:26:02 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 05:38:52 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_max_line(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (max < j)
			max = j;
		i++;
	}
	return (max);
}

char	**fill_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		while (ft_strlen(&map[i][0]) != find_max_line(map))
		{
			map[i] = ft_strjoin(map[i], "1");
		}
		i++;
	}
	return (map);
}

void	check_map(char *tmp, t_tazi_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!tmp[0])
		ft_error("Map not found", data);
	while (tmp[i])
	{
		if (tmp[i - 1] == '\n')
		{
			while (tmp[i] == ' ')
			{
				if (tmp[i + 1] == '\n')
					ft_error("Map is separated", data);
				i++;
			}
		}
		if (tmp[i - 1] == '\n' && tmp[i] == '\n' && \
			tmp[i + 1] != '\0' && tmp[i + 1] != '\n')
			ft_error("Map is separated", data);
		i++;
	}
}

void	check_firstandlast_line(char **map, t_tazi_data *data)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == 'N' || map[0][i] == 'E' || \
			map[0][i] == 'W' || map[0][i] == 'S')
			ft_error("MAP NOT SURROUNDED BY WALLS", data);
		i++;
	}
	i = 0;
	while (map[ft_count(map) - 1][i])
	{
		if (map[ft_count(map) - 1][i] == 'N' || \
			map[ft_count(map) - 1][i] == 'E' || map[ft_count(map) - 1][i] == 'W'
			|| map[ft_count(map) - 1][i] == 'S')
			ft_error("MAP NOT SURROUNDED BY WALLS", data);
		i++;
	}
}

void	parse_map(char *file, t_tazi_data *data)
{
	char	*tmp;
	char	**map;

	tmp = get_map(open(file, O_RDONLY), data);
	check_map(tmp, data);
	map = ft_split(tmp, '\n');
	free(tmp);
	check_firstandlast_line(map, data);
	check_component(map, data);
	search_for_player(map, data);
	check_surroundedby_walls(map, data);
	data->map_len_max = find_max_line(map);
	data->map_wei_max = ft_count(map);
	data->map = fill_map(map);
}
