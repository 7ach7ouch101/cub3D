#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define WIN_HEIGHT 720
#define WN_WIDTH 1024
#define BLOCK_SIZE 20
#define FOV 60.0 * (M_PI / 180.0)
#define l3iba  (double)((WN_WIDTH/2.0) / tan(FOV / 2.0))

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct t_mlx_info
{
    void    *mlx_p;
    void    *mlx_w;

}               s_mlx_info;

typedef struct s_player
{
    double a;
    double x;
    double y;
    int    dir;
    int    rot;
}               t_player;

typedef struct s_ray 
{
    double dist;
    double x;
    double y;
    double a;
}               t_ray;

typedef struct s_tazi_data 
{
    char    **map;
    char    **param;
    int     map_len_max; // x
    int     map_wei_max; // y
    t_image render;
    t_ray ray[WN_WIDTH];
    s_mlx_info mlx;
    t_player p;
}               t_tazi_data;


char	*get_next_line(int fd);
int	    ft_strlen(char *str);
int	    ft_strncmp(char *s1,char *s2, size_t n);
void    parse_map(char *file, t_tazi_data *data);
char    **parse_param(char *file);
int     check_file(char *file);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
int     release(int keycode, t_tazi_data *data);
int     press(int keycode, t_tazi_data *data);
void    mlx_func(t_tazi_data *data);
void    cast_ray(t_tazi_data *data);
void    move(t_tazi_data *data);
void    rotate(t_tazi_data *data);
t_ray   ray_info(t_tazi_data *data, int i);
void    horizontal_ray(t_tazi_data *data, t_ray *ray_h, double angl);
void    vertical_ray(t_tazi_data *data, t_ray *ray_h, double angl);
void    position_player(t_tazi_data *data);
void    draw_all(t_tazi_data *data);
char	*ft_strdup(char *s1);
void	*ft_memcpy(void	*dst, char *src, int n);


#endif