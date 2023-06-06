#include "cub3d.h"

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
        if((str[0] == '\n' || (str[i] == ' ' && str[ft_strlen(str) - 2] == ' ')
            || str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
            return (1);
        i++;
    }
    return (0);
}

char    *get_map(int fd)
{
    char *str;
    char *str1;
    char *map;
    int count;

    str = get_next_line(fd);
    while(str && check_line(str) == 1)
        str = get_next_line(fd);
    map = ft_strjoin(get_next_line(fd), get_next_line(fd));
    while(map)
    {
        map = ft_strjoin(get_next_line(fd), get_next_line(fd));
        //printf("%s", map);
    }
    printf("%s", map);
    return (map);
}

void    parse_map(char *file)
{
    char *map;

    map = get_map(open(file, O_RDONLY));
    //int count = 0;
    /*while(map[count] != '\0')
    {
        printf("%c", map[count]);
        count++;
    }*/
}

int main(int ac, char **av)
{
    char **param;
    if(ac == 2)
    {
        if(check_file(av[1]) == 0)
            return (0);
        param = parse_param(av[1]);
        parse_map(av[1]);
    }
    else
        printf("NOT ENOUGH ARGUMENTS !!\n");
    return (0);
}