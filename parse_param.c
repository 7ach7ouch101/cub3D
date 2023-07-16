/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:27:12 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 09:00:22 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_files(char **param, t_tazi_data *data)
{
	if (open(param[0], O_RDONLY) == -1)
		ft_error("Error", data);
	if (open(param[1], O_RDONLY) == -1)
		ft_error("Error", data);
	if (open(param[2], O_RDONLY) == -1)
		ft_error("Error", data);
	if (open(param[3], O_RDONLY) == -1)
		ft_error("Error", data);
}

void	parse_rgb(char **param, t_tazi_data *data)
{
	int	j;

	j = 0;
	while (param[4][j])
	{
		if (param[4][j] == ' ' || (param[4][j] >= '0' && \
			param[4][j] <= '9') || param[4][j] == ',')
			j++;
		else
			ft_error("RGB syntax error", data);
	}
	j = 0;
	while (param[5][j])
	{
		if (param[5][j] == ' ' || (param[5][j] >= '0' && \
			param[5][j] <= '9') || param[5][j] == ',')
			j++;
		else
			ft_error("RGB syntax error", data);
	}
}

void	check_xpm(char *param, t_tazi_data *data)
{
	int	i;

	i = 0;
	while (param && param[i] != '.')
	{
		if (param[i + 1] == '.')
		{
			if (param[i + 2] == 'x' && param[i + 3] == 'p' && \
				param[i + 4] == 'm' && param[i + 5] == '\0')
				return ;
			else
				ft_error("EXTENSION TEXTURE ERROR", data);
		}
		i++;
	}
}

void	check_exe(char **param, t_tazi_data *data)
{
	if (!data->param[0] || !data->param[1] || !data->param[2]
		|| !data->param[3] || !data->param[4] || !data->param[5])
		ft_error("Error param", data);
	if (!(param))
		ft_error("allocation error", data);
	check_xpm(param[0], data);
	check_xpm(param[1], data);
	check_xpm(param[2], data);
	check_xpm(param[3], data);
}

void	parse_param(char *file, t_tazi_data *data)
{
	int		fd;
	char	*str;

	data->param = malloc(6 * sizeof(char *));
	if (!data->param)
		ft_error("allocation error", data);
	init_param(data->param);
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		search(str, data->param);
		free(str);
		str = get_next_line(fd);
	}
	check_exe(data->param, data);
	check_files(data->param, data);
	parse_rgb(data->param, data);
	check_threec(data->param[5], data);
	check_threec(data->param[4], data);
	check_rgb(data->param[4], data, 'f');
	check_rgb(data->param[5], data, 'c');
	data->c = create_trgb(data->sc[0], data->sc[1], data->sc[2]);
	data->f = create_trgb(data->sf[0], data->sf[1], data->sf[2]);
}
