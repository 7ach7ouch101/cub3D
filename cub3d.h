#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

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

}   s_mlx_info;

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
} t_ray;

typedef struct s_tazi_data 
{
    t_image render;
    char    **map;
    char    **param;
    int last;
    int x_player;
    int y_player;
    t_ray ray[1024];
    s_mlx_info mlx;
    t_player p;
    
} t_tazi_data;


char	*get_next_line(int fd);
int	    ft_strlen(char *str);
int	    ft_strncmp(char *s1,char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

//remove later
void draw_rectangle(void *mlx_ptr, void *win_ptr, int x, int y, int width, int height, int color, t_image *img);
void draw_map(char **game_map, int map_width, int map_height, void *mlx_ptr, void *win_ptr, t_image *img);


#endif