/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:26:02 by mmeziani          #+#    #+#             */
/*   Updated: 2023/07/15 08:14:52 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        ft_error("FILE er FOUND!!\n");
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

char *escape_spaces(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] == ' ')
        i++;
    return (ft_strdup(&str[i]));
}

void    search(char *str, char **param)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(ft_strncmp(&str[i], "NO", 2) == 0 && (!param[0]))
            param[0] = escape_spaces(&str[i + 2]);
        else if(ft_strncmp(&str[i], "SO", 2) == 0 && (!param[1]))
            param[1] = escape_spaces(&str[i + 2]);
        else if(ft_strncmp(&str[i], "WE", 2) == 0 && (!param[2]))
            param[2] = escape_spaces(&str[i + 2]);
        else if(ft_strncmp(&str[i], "EA", 2) == 0 && (!param[3]))
            param[3] = escape_spaces(&str[i + 2]);
        else if((ft_strncmp(&str[i], "F", 1) == 0) && (!param[4]))
            param[4] = escape_spaces(&str[i + 1]);
        else if((ft_strncmp(&str[i], "C", 1) == 0) && (!param[5]))
            param[5] = escape_spaces(&str[i + 1]);
        i++;
    }
}

void    init_param(char **param)
{
    param[0] = NULL;
    param[1] = NULL;
    param[2] = NULL;
    param[3] = NULL;
    param[4] = NULL;
    param[5] = NULL;
    param[6] = NULL;
}

void    check_rgb(char *param, t_tazi_data *data, char type)
{
    char *str;
    int i;
    int j;
    int a;

    a = 0;
    i = 0;
    while(param[i])
    {
        j = 0;
        while(param[i] >= '0' && param[i] <= '9')
        {
            i++;
            j++;
        }
        if(j > 0)
        {
            str = malloc(j + 1);
            str[j] = '\0';
            ft_memcpy(str, &param[i - j], j);
            if (!(ft_atoi(str) >= 0 && ft_atoi(str) <= 255))
                ft_error("Error");
            if(type == 'f')
                data->sF[a] = ft_atoi(str);
            else if(type == 'c')
                data->sC[a] = ft_atoi(str);
            a++;
            free(str);
        }
        i++;
    }
}

void    check_threeC(char *param)
{
    int num;
    int i;
    int count;

    count = 0;
    i = 0;
    num = 0;
    while(param[i])
    {
        while(param[i] >= '0' && param[i] <= '9')
        {
            num++;
            i++;
        }
        if(num != 0)
            count++;
        num = 0;
        i++;
    }
    if(count != 3)
        ft_error("Error");
}

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void    check_files(char **param)
{
    if(open(param[0], O_RDONLY) == -1)
        ft_error("Error");
    if(open(param[1], O_RDONLY) == -1)
        ft_error("Error");
    if(open(param[2], O_RDONLY) == -1)
        ft_error("Error");
    if(open(param[3], O_RDONLY) == -1)
        ft_error("Error");
}

void    parse_rgb(char **param)
{
    int j;

    j = 0;
    while(param[4][j])
    {
        if(param[4][j] == ' ' || (param[4][j] >= '0' && param[4][j] <= '9') || param[4][j] == ',')
            j++;
        else
            ft_error("RGB syntax error");
    }
    j = 0;
    while(param[5][j])
    {
        if(param[5][j] == ' ' || (param[5][j] >= '0' && param[5][j] <= '9') ||  param[5][j] == ',')
            j++;
        else
            ft_error("RGB syntax error");
    }
}

char **parse_param(char *file, t_tazi_data *data)
{
    char **param;
    int fd;
    int fd2;
    char *str;

    param = malloc(7 * sizeof(char*));
    init_param(param);
    fd = open(file, O_RDONLY);
    str = get_next_line(fd);
    while(str)
    {
        search(str, param);
        free(str);
        str = get_next_line(fd);
    }
    //check_exe(param);//xpm
    check_files(param);
    parse_rgb(param);
    check_threeC(param[5]);//C
    check_threeC(param[4]);//F
    check_rgb(param[4], data, 'f');//F
    check_rgb(param[5], data, 'c');//C
    data->C = create_trgb(data->sC[0], data->sC[1], data->sC[2]);
    data->F = create_trgb(data->sF[0], data->sF[1], data->sF[2]);
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
        if((str[0] == '\n') || (str[i] >= 'A' && str[i] <= 'Z' && !(str[i + 1] == '1') 
            && !(str[i + 1] == '0') && !(str[i] == 'N') && !(str[i] == 'E') && !(str[i] == 'W') && !(str[i] == 'S')) 
            || (str[i] >= 'a' && str[i] <= 'z' && !(str[i + 1] == '1') && !(str[i + 1] == '0')))
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

int    check_line1(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        while(str[i] == ' ' || str[i] == '\n')
            i++;
        if (!str[i])
            return (0);
        if (!((ft_strncmp(&str[i], "WE", 2) == 0) || (ft_strncmp(&str[i], "EA", 2) == 0) || (ft_strncmp(&str[i], "SO", 2) == 0) || (ft_strncmp(&str[i], "NO", 2) == 0)
            || (str[i] == 'F') || (str[i] == 'C')))
            ft_error("Bad conf file");
        else
            return (0);
        i++;
    }
    return (1);
}

char    *get_map(int fd)
{
    char *str;
    char *str1;
    char *map;

    str = get_next_line(fd);
    map = NULL;
    while(str && (check_line(str) == 1))
    {
        if (check_line1(str))
            ft_error("config lilo ghalat");
        free(str);
        str = get_next_line(fd);
    }
    str1 = get_next_line(fd);
    str = ft_strjoin(str, str1);
    free(str1);
    str1 = str;
    map = ft_calloc(1, 1);//ahya
    while(str1)
    {
        map = ft_strjoin(map, str1);
        free(str1);
        str1 = get_next_line(fd);
    }
    free(str1);
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
    if (player == 0)
        ft_error("No lilo player");
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

int ft_count(char **map)
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

int find_max_line(char **map)
{
    int i;
    int j;
    int max;

    i = 0;
    max = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
            j++;
        if(max < j)
            max = j;
        i++;
    }
    return (max);
}

char    **fill_map(char **map)
{
    int i;
    int j;

    i = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == ' ')
                map[i][j] = '1';
            j++;
        }
        while(ft_strlen(&map[i][0]) != find_max_line(map))
        {
            map[i] = ft_strjoin(map[i], "1");
        }
        i++;
    }
    return (map);
}

void    check_map(char *tmp)
{
    int i;
    int count;

    count = 0;
    i = 0;
    if(!tmp[0])
        ft_error("Map not found");
    while(tmp[i])
    {
        if(tmp[i - 1] == '\n')
        {
            while(tmp[i] == ' ')
            {
                if(tmp[i + 1] == '\n')
                    ft_error("Map is separated");
                i++;
            }
        }
        // if (tmp[i - 1] == '\n' && tmp[i] == '\n' && tmp[i+1] != '\0' && tmp[i+1] != '\n')//error map
        //     ft_error("Map is separated");
        i++;
    }
}

void    check_firstandlast_line(char **map)
{
    int i;

    i = 0;
    while(map[0][i])
    {
        if(map[0][i] == 'N' || map[0][i] == 'E' || map[0][i] == 'W' || map[0][i] == 'S')
            ft_error("MAP NOT SURROUNDED BY WALLS");
        i++;
    }
    i = 0;
    while(map[ft_count(map) - 1][i])
    {
        if(map[ft_count(map) - 1][i] == 'N' || map[ft_count(map) - 1][i] == 'E' || map[ft_count(map) - 1][i] == 'W' 
            || map[ft_count(map) - 1][i] == 'S')
            ft_error("MAP NOT SURROUNDED BY WALLS");
        i++;
    }
}

void    parse_map(char *file, t_tazi_data *data)
{
    char *tmp;
    char **map;
    int i = 0;

    tmp = get_map(open(file, O_RDONLY));
    check_map(tmp);
    map = ft_split(tmp, '\n');
    free(tmp);
    check_firstandlast_line(map);
    check_component(map);
    search_for_player(map);
    check_surroundedby_walls(map);
    data->map_len_max = find_max_line(map);
    data->map_wei_max = ft_count(map);
    map = fill_map(map);
    data->map = map;
}