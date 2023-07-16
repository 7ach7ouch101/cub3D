/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 01:31:42 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 05:40:02 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_kolchi(t_tazi_data *data)
{
    if(data->param[0])
        free(data->param[0]);
    if(data->param[1])
        free(data->param[1]);
    if(data->param[2])
        free(data->param[2]);
    if(data->param[3])
        free(data->param[3]);
    if(data->param[4])
        free(data->param[4]);
    if(data->param[5])
        free(data->param[5]);
}

void	ft_error(char *str, t_tazi_data *data)
{
	printf ("%s\n", str);
	free_kolchi(data);
	exit(0);
}
