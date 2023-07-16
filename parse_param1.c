/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 02:29:22 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 08:58:41 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	search(char *str, char **param)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], "NO", 2) == 0 && (!param[0]))
			param[0] = escape_spaces(&str[i + 2]);
		else if (ft_strncmp(&str[i], "SO", 2) == 0 && (!param[1]))
			param[1] = escape_spaces(&str[i + 2]);
		else if (ft_strncmp(&str[i], "WE", 2) == 0 && (!param[2]))
			param[2] = escape_spaces(&str[i + 2]);
		else if (ft_strncmp(&str[i], "EA", 2) == 0 && (!param[3]))
			param[3] = escape_spaces(&str[i + 2]);
		else if ((ft_strncmp(&str[i], "F", 1) == 0) && (!param[4]))
			param[4] = escape_spaces(&str[i + 1]);
		else if ((ft_strncmp(&str[i], "C", 1) == 0) && (!param[5]))
			param[5] = escape_spaces(&str[i + 1]);
		i++;
	}
}

void	init_param(char **param)
{
	param[0] = NULL;
	param[1] = NULL;
	param[2] = NULL;
	param[3] = NULL;
	param[4] = NULL;
	param[5] = NULL;
}

void	check_rgb1(char *param, t_tazi_data *data, int i, int j)
{
	char	*str;

	if (j > 0)
	{
		str = malloc(j + 1);
		if (!(str))
			ft_error("malloc error", data);
		str[j] = '\0';
		ft_memcpy(str, &param[i - j], j);
		if (!(ft_atoi(str) >= 0 && ft_atoi(str) <= 255))
			ft_error("Error", data);
		data->sf[data->i] = ft_atoi(str);
		data->i++;
		free(str);
	}
}

void	check_rgb(char *param, t_tazi_data *data, char type)
{
	int	i;
	int	j;

	i = 0;
	while (param[i])
	{
		j = 0;
		while (param[i] >= '0' && param[i] <= '9')
		{
			i++;
			j++;
		}
		if (type == 'f')
			check_rgb1(param, data, i, j);
		if (type == 'c')
			check_rgb2(param, data, i, j);
		i++;
	}
}

void	check_threec(char *param, t_tazi_data *data)
{
	int	num;
	int	i;
	int	count;

	count = 0;
	i = 0;
	num = 0;
	while (param[i])
	{
		while (param[i] >= '0' && param[i] <= '9')
		{
			num++;
			i++;
		}
		if (num != 0)
			count++;
		num = 0;
		i++;
	}
	if (count != 3)
		ft_error("Error", data);
}
