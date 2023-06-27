#include "cub3d.h"

int	ft_strncmp(char *s1,char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i] && i < (n - 1)) && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*merge(char *s1, char *s2, char *p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		a;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	p = malloc((a + b) + 1);
	if (!p)
		return (NULL);
	p = merge(s1, s2, p);
	return (p);
}

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_rectangle(void *mlx_ptr, void *win_ptr, int x, int y, int width, int height, int color, t_image *img)
{
	int i, j;
	for (i = x; i < x + width - 1; i++)
	{
		for (j = y; j < y + height - 1; j++)
		{
			my_mlx_pixel_put(img, i, j, color);
		}
	}
}

void draw_map(char **game_map, int map_width, int map_height, void *mlx_ptr, void *win_ptr, t_image *img)
{
	int x, y;

	// mlx_clear_window(mlx_ptr, win_ptr);

	int display_width = map_width;
	int display_height = map_height;

	int start_x = 0;					  
	int start_y = 0;					  
	int end_x = start_x + display_width;  
	int end_y = start_y + display_height; 

	for (y = start_y; y < end_y && y < map_height; y++)
	{
		for (x = start_x; x < end_x && x < map_width; x++)
		{
			if (game_map[y][x] == '1')
			{
				int rect_x = x * 20;
				int rect_y = y * 20;

				draw_rectangle(mlx_ptr, win_ptr, rect_x, rect_y, 20, 20, 0xFFFFFF, img);
			}
		}
	}
}