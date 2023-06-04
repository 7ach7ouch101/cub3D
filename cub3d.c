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
char    **get_map(char *file)
{
    char *str;
    int fd;
    int ;
    char **map;

    fd = open(file, O_RDONLY);
    str = get_next_line(fd);
    while(str)
    {
        if(str[0] == '1' || str[0] == '0')
        {
            
        }
        str = get_next_line(fd);
    }

}

void    parse_map(char *file)
{
    char **map;

    map = get_map(file);
    
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