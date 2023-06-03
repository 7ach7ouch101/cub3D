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

int parse(char *file)
{
    int fd;
    char *str;

    fd = open(file, O_RDONLY);
    str = get_next_line(fd);
    printf("%s\n", str);
    return (0);
}

int main(int ac, char **av)
{
    if(ac == 2)
    {
        if(check_file(av[1]) == 0)
            return (0);
        if(parse(av[1]) == 0)
            return (0);
    }
    else
        printf("NOT ENOUGH ARGUMENTS !!\n");
    return (0);
}