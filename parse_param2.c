/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_param2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:20:47 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 09:00:31 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

char	*escape_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	return (ft_strdup(&str[i]));
}

void	check_rgb2(char *param, t_tazi_data *data, int i, int j)
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
		data->sc[data->j] = ft_atoi(str);
		data->j++;
		free(str);
	}
}
