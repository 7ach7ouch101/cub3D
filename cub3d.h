#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

char	*get_next_line(int fd);
int	    ft_strlen(char *str);
int	    ft_strncmp(char *s1,char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s, char c);

#endif