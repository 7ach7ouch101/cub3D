/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:17:23 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 04:29:36 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_component(char **map, t_tazi_data *data)
{
	int	player;
	int	i;
	int	j;

	i = -1;
	player = 0;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!(map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' ' \
				|| map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' \
				|| map[i][j] == 'E'))
				ft_error("Error", data);
			if (map[i][j] == 'N' || map[i][j] == 'W' || \
				map[i][j] == 'S' || map[i][j] == 'E')
				player++;
			if (player > 1)
				ft_error("To many players", data);
			j++;
		}
	}
	if (player == 0)
		ft_error("No lilo player", data);
}

void	search_for_player(char **map, t_tazi_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || \
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!(((map[i][j + 1]) && ((map[i][j + 1] == '0') || \
					(map[i][j + 1] == '1'))) &&
					((map[i][j - 1]) && ((map[i][j - 1] == '0') || \
					(map[i][j - 1] == '1'))) &&
					((map[i - 1][j]) && ((map[i - 1][j] == '0') || \
					map[i - 1][j] == '1')) &&
					((map[i + 1][j]) && ((map[i + 1][j] == '0') || \
					map[i + 1][j] == '1'))))
					ft_error("MAP NOT SURROUNDED BY WALLS", data);
			}
			j++;
		}
	}
}

void	check(char **map, int i, int j, t_tazi_data *data)
{
	if (!(((map[i][j + 1]) && ((map[i][j + 1] == '0') || \
		(map[i][j + 1] == '1') || (map[i][j + 1] == 'N') || \
		(map[i][j + 1] == 'S') || (map[i][j + 1] == 'E') || \
		(map[i][j + 1] == 'W'))) &&
		((map[i][j - 1]) && ((map[i][j - 1] == '0') || \
		(map[i][j - 1] == '1') || (map[i][j - 1] == 'N') || \
		(map[i][j - 1] == 'S') || (map[i][j - 1] == 'E') || \
		(map[i][j - 1] == 'W'))) &&
		((map[i - 1][j]) && ((map[i - 1][j] == '0') || \
		(map[i - 1][j] == '1') || (map[i - 1][j] == 'N') || \
		(map[i - 1][j] == 'S') || (map[i - 1][j] == 'E') || \
		(map[i - 1][j] == 'W'))) &&
		((map[i + 1][j]) && ((map[i + 1][j] == '0') || \
		map[i + 1][j] == '1' || map[i + 1][j] == 'N' || \
		map[i + 1][j] == 'S' || map[i + 1][j] == 'E' || \
		map[i + 1][j] == 'W'))))
		ft_error("MAP NOT SURROUNDED BY WALLS", data);
}

int	check1(int i, int j, char **map, t_tazi_data *data)
{
	if ((i + 1) == ft_count(map))
	{
		while (map[i][j])
		{
			if (map[i][j] == '0')
				ft_error("MAP NOT SURROUNDED BY WALLS", data);
			j++;
		}
	}
	return (j);
}

void	check_surroundedby_walls(char **map, t_tazi_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		j = check1(i, j, map, data);
		if (i == 0)
		{
			while (map[i][j])
			{
				if (map[i][j] == '0')
					ft_error("MAP NOT SURROUNDED BY WALLS", data);
				j++;
			}
			i++;
		}
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
				check(map, i, j, data);
		}
	}
}
