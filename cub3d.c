/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:39:12 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 05:39:19 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_file(char *file, t_tazi_data *data)
{
	int	i;

	i = 0;
	if (open(file, O_RDONLY) == -1)
		ft_error("FILE er FOUND!!", data);
	while (file[i] != '.')
	{
		if (file[i + 1] == '.')
		{
			if (file[i + 2] == 'c' && file[i + 3] == 'u'
				&& file[i + 4] == 'b' && file[i + 5] == '\0')
				return (1);
			else
			{
				ft_error ("EXTENSION ERROR", data);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	init_data(t_tazi_data *data)
{
	data->ccount = 0;
	data->fcount = 0;
	data->wecount = 0;
	data->eacount = 0;
	data->socount = 0;
	data->nocount = 0;
	data->p.dir = 0;
	data->p.rot = 0;
	data->p.a = 0;
	data->p.x = 0;
	data->p.y = 0;
	data->map_len_max = 0;
	data->map_wei_max = 0;
	data->ray->dist = 0;
	data->ray->a = 0;
	data->ray->x = 0;
	data->ray->y = 0;
	data->render.bits_per_pixel = 0;
	data->render.line_length = 0;
	data->render.endian = 0;
}

int	main(int ac, char **av)
{
	t_tazi_data	data;

	init_data(&data);
	if (ac == 2)
	{
		if (check_file(av[1], &data) == 0)
			return (0);
		parse_param(av[1], &data);
		parse_map(av[1], &data);
		position_player(&data);
		data.mlx.mlx_p = mlx_init();
		data.mlx.mlx_w = mlx_new_window(data.mlx.mlx_p,
				WN_WIDTH, WIN_HEIGHT, "cub3d");
		mlx_func(&data);
		mlx_loop(data.mlx.mlx_p);
	}
	else
		printf("Error ARGS");
	return (0);
}
