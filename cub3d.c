#include "cub3d.h"

void    ft_error(char *str)
{
    printf("%s\n", str);
    exit(0);
}

int check_file(char *file)
{
    int i;
    i = 0;

    if(open(file, O_RDONLY) == -1)
    {
        printf("FILE NOT FOUND!!\n");
        return (0);
    }
    while(file[i] != '.')
    {
        if(file[i + 1] == '.')
        {
            if(file[i + 2] == 'c' && file[i + 3] == 'u' && file[i + 4] == 'b' && file[i + 5] == '\0')
                return (1);
            else
            {
                printf("EXTENSION ERROR \n");
                return (0);
            }
        }
        i++;
    }
    return (1);
}

char **parse_param(char *file)
{
    char **param;
    int fd;
    char *str;

    param = malloc(7 * sizeof(char*));
    fd = open(file, O_RDONLY);
    str = get_next_line(fd);
    while(str)
    {
        if(ft_strncmp(&str[0], "NO", 2) == 0)
            param[0] = &str[3];
        else if(ft_strncmp(&str[0], "SO", 2) == 0 && (ft_strncmp(&str[2], " ", 1) == 0))
            param[1] = &str[3];
        else if(ft_strncmp(&str[0], "WE", 2) == 0 && (ft_strncmp(&str[2], " ", 1) == 0))
            param[2] = &str[3];
        else if(ft_strncmp(&str[0], "EA", 2) == 0 && (ft_strncmp(&str[2], " ", 1) == 0))
            param[3] = &str[3];
        else if((ft_strncmp(&str[0], "F", 1) == 0) && (ft_strncmp(&str[1], " ", 1) == 0))
            param[4] = &str[2];
        else if((ft_strncmp(&str[0], "C", 1) == 0) && (ft_strncmp(&str[1], " ", 1) == 0))
            param[5] = &str[2];
        str = get_next_line(fd);
    }
    return (param);
}

int check_line(char *str)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while(str[i])
    {
        if((str[0] == '\n') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            j++;
        if((str[0] == ' ' && str[ft_strlen(str) - 2] == ' '))
        {
            while(str[i])
            {
                if((str[i] == '1' && str[i + 1] == '1') || (str[i] == '0' && str[i + 1] == '0')
                    || (str[i] == 'N' || str[i + 1] == '0' || str[i + 1] == '1'))
                    return (0);
                i++;
            }
            j++;
        }
        i++;
    }
    if(j > 0)
        return (1);
    return (0);
}

char    *get_map(int fd)
{
    char *str;
    char *str1;
    char *map;

    str = get_next_line(fd);
    while(check_line(str) == 1)
        str = get_next_line(fd);
    str1 = get_next_line(fd);
    str1 = ft_strjoin(str, str1);
    free(str);
    map = malloc(1);
    while(str1)
    {
        map = ft_strjoin(map, str1);
        free(str1);
        str1 = get_next_line(fd);
    }
    return (map);
}

void    check_component(char **map)
{
    int player;
    int i;
    int j;

    i = 0;
    player = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(!(map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' ' 
                || map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E'))
                ft_error("Error");
            if(map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S' || map[i][j] == 'E')
                player++;
            if(player > 1)
                ft_error("To many players");
            j++;
        }
        i++;
    }
}

void search_for_player(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S'|| map[i][j] == 'E' || map[i][j] == 'W')
            {
                if (!(((map[i][j + 1]) && ((map[i][j + 1] == '0') || (map[i][j + 1] == '1'))) &&
                    ((map[i][j - 1]) && ((map[i][j - 1] == '0') || (map[i][j - 1] == '1'))) &&
                    ((map[i - 1][j]) && ((map[i - 1][j] == '0') || map[i - 1][j] == '1')) &&
                    ((map[i + 1][j]) && ((map[i + 1][j] == '0') || map[i + 1][j] == '1'))))
                    ft_error("MAP NOT SURROUNDED BY WALLS");
            }
            j++;
        }
        i++;
    }
}
int ft_count(char **map)//y
{
    int i;

    i = 0;
    while(map[i])
        i++;
    return (i);
}
void    check_surroundedby_walls(char **map)
{
    int i;
    int j;
    int last; 

    i = 0;
    last = ft_count(map);
    while(map[i])
    {
        j = 0;
        if((i + 1) == last)
        {
            while(map[i][j])
            {
                if(map[i][j] == '0')
                    ft_error("MAP NOT SURROUNDED BY WALLS");
                j++;
            }
        }
        if(i == 0)
        {
            while(map[i][j])
            {
                if(map[i][j] == '0')
                    ft_error("MAP NOT SURROUNDED BY WALLS");
                j++;
            }
            i++;
        }
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == '0')
            {
                if (!(((map[i][j + 1]) && ((map[i][j + 1] == '0') || (map[i][j + 1] == '1') || (map[i][j + 1] == 'N') || (map[i][j + 1] == 'S') || (map[i][j + 1] == 'E') || (map[i][j + 1] == 'W'))) &&
                    ((map[i][j - 1]) && ((map[i][j - 1] == '0') || (map[i][j - 1] == '1') || (map[i][j - 1] == 'N') || (map[i][j - 1] == 'S') || (map[i][j - 1] == 'E') || (map[i][j - 1] == 'W'))) &&
                    ((map[i - 1][j]) && ((map[i - 1][j] == '0') || (map[i - 1][j] == '1') || (map[i - 1][j] == 'N') || (map[i - 1][j] == 'S') || (map[i - 1][j] == 'E') || (map[i - 1][j] == 'W'))) &&
                    ((map[i + 1][j]) && ((map[i + 1][j] == '0') || map[i + 1][j] == '1' || map[i + 1][j] == 'N' || map[i + 1][j] == 'S'|| map[i + 1][j] == 'E' || map[i + 1][j] == 'W'))))
                    ft_error("MAP NOT SURROUNDED BY WALLS");
            }
            j++;
        }
        i++;
    }
}

void    parse_map(char *file, t_tazi_data *data)
{
    char *tmp;
    char **map;
    int i = 0;

    tmp = get_map(open(file, O_RDONLY));
    map = ft_split(tmp, '\n');
    check_component(map);
    search_for_player(map);
    check_surroundedby_walls(map);
    data->map = map;
}

int press(int keycode, t_tazi_data *data)
{
    if(keycode == 123)
        data->p.rot = -1;
    if(keycode == 124)
        data->p.rot = 1;
    if(keycode == 13 || keycode == 126) //w
        data->p.dir = 1;
    if(keycode == 1 || keycode == 125)//s
        data->p.dir = -1;
    // if(keycode == 0) //a
    // {
    // }
    // if(keycode == 2)//d
    // {
    // }
    return 0;
}
int release(int keycode, t_tazi_data *data)
{
    if(keycode == 123)
        data->p.rot = 0;
    if(keycode == 124)
        data->p.rot = 0;
    if(keycode == 13 || keycode == 126) //w
        data->p.dir = 0;
    if(keycode == 1 || keycode == 125)//s
        data->p.dir = 0;
    // if(keycode == 0) //a
    // {
    // }
    // if(keycode == 2)//d
    // {
    // }
    return 0;
}
void move(t_tazi_data *data)
{
    double del_x;
    double del_y;

    del_x = cos(data->p.a) * 3 * data->p.dir;
    del_y = sin(data->p.a) * 3 * data->p.dir;
    if(data->map[(int)(data->p.y + del_y) / 20][(int)(data->p.x + del_x) / 20] != '1')
    {
        data->p.x += del_x;
        data->p.y += del_y;
    }
}
void rotate(t_tazi_data *data)
{
    data->p.a += (0.1 * data->p.rot);
}

int    print_map(char **arr)
{
    int i = -1;

    while(arr[++i]);
    return i;
}

void    draw_player(t_tazi_data *data)
{
    int i = 0;
    int j;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            if(data->map[i][j] == 'N')
            {//ila kant N player ghaywkon kishof lfoq, lakant S ghaykon kishof lta7t etc...
                data->p.a = 270 * (M_PI / 180);
                data->p.x = j * 20 + 10;
                data->p.y = i * 20 + 10;
                return;
            }
            j++;
        }
        i++;
    }
}

t_ray horizontal_ray(t_tazi_data *data, t_ray *ray_h, double angl)
{
    double x_s;
    double y_s;
    double dist;

    if(data->p.a > 0 && angl < M_PI)
    {
        y_s = 20;
        ray_h->y = floor(data->p.y /20) * (20) + 20;
    }
    else
    {
        y_s = -20;
        ray_h->y = floor(data->p.y /(-20)) * (-20) - 0.0001 ;
    }

    ray_h->x = data->p.x + (ray_h->y - data->p.y) / tan(angl);
    x_s = y_s / tan(angl);

        //
    while(ray_h->x >= 0 && ray_h->x/20 <= ft_strlen(data->map) && ray_h->y >= 0 && ray_h->y/20 <= ft_count(data->map))
    {
        if( !(floor(ray_h->x / 20) < 0 )&& !(floor(ray_h->x / 20) > ft_strlen(data->map) - 1) && !(floor(ray_h->y / 20) < 0) && !(floor(ray_h->y / 20) > ft_count(data->map) - 1))
        {
            if (data->map[floor(ray_h->y / 20][floor(ray_h->x / 20)] == '1') //////////// 
            {
                ray_h->x = x_intercept;
                ray_h->y = y_intercept;
                return (*dist = distance(args->p.x, args->p.y, x_intercept, y_intercept), pos);
            }
        }
        else if(has_wall_at(x_intercept, y_intercept, args) == -1)
            return (pos.x = INFINITY, pos.y = INFINITY, *dist = INFINITY, pos);
        else
        {
            x_intercept += x_step;
            y_intercept += y_step;
        }
    }
    return (pos.x = INFINITY, pos.y = INFINITY, *dist = INFINITY, pos);
        //

}
/////////////////////////////////

t_ray ray_info(t_tazi_data *data, int i)
{
    double angl;
    t_ray ray_h;
    t_ray ray_v;

    angl = data->p.a - (90 / 2) + (90 * i / 1024);
    angl = remainder(angl, 2 * M_PI);
    if(angl < 0)
        angl = (2 * M_PI) + angl;
    horizontal_ray(data, &ray_h, angl)
}

//////////////////////////////////
void cast_ray(t_tazi_data *data)
{
    int i;

    i = 0;
    while (i < 1024)
    {
        data->ray[i] = ray_info(data, i);
    }
    
}

int rendering(t_tazi_data *data)
{
    //if image exists destroy it
    mlx_destroy_image(data->mlx.mlx_p, data->render.img);
    data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);
    move(data);
    rotate(data);
    // draw_map(data->map, ft_strlen(data->map[0]), print_map(data->map), data->mlx.mlx_p, data->mlx.mlx_w, &data->render);
    // draw_rectangle(data->mlx.mlx_p, data->mlx.mlx_w, data->p.x, data->p.y, 10, 10, 0xFF0000, &data->render);

    cast_ray(data);
    mlx_put_image_to_window(data->mlx.mlx_p, data->mlx.mlx_w, data->render.img,0,0);
    return 0;
}


void    mlx_func(t_tazi_data *data)
{
    draw_player(data);
    data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);
	// mlx_hook(args->win, 17, 0, , NULL); // exit; // later;
    mlx_hook(data->mlx.mlx_w, 2, 0, press, data); // press;
	mlx_hook(data->mlx.mlx_w, 3, 0, release, data); // release;
	mlx_loop_hook(data->mlx.mlx_p, rendering, data);
}

int main(int ac, char **av)
{
    t_tazi_data data;
    char **param;

    if(ac == 2)
    {
        if(check_file(av[1]) == 0)
            return (0);
        param = parse_param(av[1]);
        parse_map(av[1], &data);
        data.p.dir = 0;
        data.p.rot = 0;
        data.mlx.mlx_p = mlx_init();
	    data.mlx.mlx_w = mlx_new_window(data.mlx.mlx_p, 1024, 720, "cub3d");
        mlx_func(&data);
        mlx_loop(data.mlx.mlx_p);
    }
    else
        printf("NOT ENOUGH ARGUMENTS !!\n");
    return (0);
}