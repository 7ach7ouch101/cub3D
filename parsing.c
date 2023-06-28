/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hadd <hel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 22:26:02 by mmeziani          #+#    #+#             */
/*   Updated: 2023/06/28 01:35:30 by hel-hadd         ###   ########.fr       */
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
    map = calloc(1, 1);
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
                {
                    // pause(); //something not right here;
                    ft_error("Error");
                }
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
    data->map_len_max = find_max_line(map);
    data->map_wei_max = ft_count(map);
    map = fill_map(map);
    data->map = map;
}