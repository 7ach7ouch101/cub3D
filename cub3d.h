/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 04:42:46 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/16 08:59:52 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define WIN_HEIGHT 720
# define WN_WIDTH 1024
# define BLOCK_SIZE 64
# define FOV 1.0472

typedef struct s_image{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx_info
{
	void	*mlx_p;
	void	*mlx_w;

}	t_mlx_info;

typedef struct s_player
{
	double	a;
	double	x;
	double	y;
	int		dir;
	int		rot;
}	t_player;

typedef struct s_ray
{
	double	dist;
	double	x;
	double	y;
	double	a;
	int		bol;
}	t_ray;

typedef struct s_tazi_data
{
	t_image		textur11[4];
	t_image		render;
	t_ray		ray[WN_WIDTH];
	t_mlx_info	mlx;
	t_player	p;
	int			sc[3];
	int			sf[3];
	int			i;
	int			j;
	int			c;
	int			f;
	int			nocount;
	int			socount;
	int			wecount;
	int			eacount;
	int			fcount;
	int			ccount;
	char		**map;
	char		**param;
	int			map_len_max;
	int			map_wei_max;
}	t_tazi_data;

void			free_map(t_tazi_data *data);
void			free_kolchi(t_tazi_data *data);
unsigned int	get_color(t_tazi_data *data, int x, int y, int wall_h);
void			for_norm(double angl, t_tazi_data *data,
					double *x_s, t_ray *ray_h);
void			for_norm2(double angl, t_tazi_data *data,
					double *y_s, t_ray *ray_h);
void			norm_vr2(t_tazi_data *data, t_ray *ray_h,
					double x_s, double y_s);
char			*get_next_line(int fd);
void			*ft_calloc(int count, int size);
int				ft_strlen(char *str);
int				ft_strncmp(char *s1, char *s2, size_t n);
void			parse_map(char *file, t_tazi_data *data);
void			parse_param(char *file, t_tazi_data *data);
int				check_file(char *file, t_tazi_data *data);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char *s, char c);
void			my_mlx_pixel_put(t_image *data, int x, int y, int color);
int				release(int keycode, t_tazi_data *data);
int				press(int keycode, t_tazi_data *data);
void			mlx_func(t_tazi_data *data);
void			cast_ray(t_tazi_data *data);
void			move(t_tazi_data *data);
void			rotate(t_tazi_data *data);
t_ray			ray_info(t_tazi_data *data, int i);
void			horizontal_ray(t_tazi_data *data, t_ray *ray_h, double angl);
void			vertical_ray(t_tazi_data *data, t_ray *ray_h, double angl);
void			position_player(t_tazi_data *data);
void			draw_all(t_tazi_data *data);
char			*ft_strdup(char *s1);
void			*ft_memcpy(char	*dst, char *src, int n);
int				ft_atoi(char *str);
void			ft_error(char *str, t_tazi_data *data);
char			*get_map(int fd, t_tazi_data *data);
void			check_component(char **map, t_tazi_data *data);
int				ft_count(char **map);
void			search_for_player(char **map, t_tazi_data *data);
void			check_surroundedby_walls(char **map, t_tazi_data *data);
void			init_param(char **param);
void			search(char *str, char **param);
void			check_threec(char *param, t_tazi_data *data);
void			check_rgb(char *param, t_tazi_data *data, char type);
int				create_trgb(int r, int g, int b);
char			*escape_spaces(char *str);
char			*ft_strchr(char *s, int c);
void			check_rgb2(char *param, t_tazi_data *data, int i, int j);

#endif