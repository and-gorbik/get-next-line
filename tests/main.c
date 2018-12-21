#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line.h"

int main(int c, char **v)
{
    if (c != 2)
    {
        printf("Incorrect arguments\n");
        return (-1);
    }

    int     fd = open(v[1], O_RDONLY);
    int     counter = 0;
    int     ret = 0;
    char    *line = NULL;
    
    if (fd < 0)
    {
        printf("Incorrect file descriptor: %d\n", fd);
        return (-1);
    }
    while (1)
    {
        ret = get_next_line(fd, &line);
        if (ret == -1)
        {
            printf("Error with gnl\n");
            return (-1);
        }
        printf("LINE: %s\n", line);
        free(line);
        ++counter;
        if (!ret)
            break;
    }
    printf("COUNT: %d\n", counter);
    return (0);
}