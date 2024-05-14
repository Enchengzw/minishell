# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "Libft/libft.h"
/*
int main(int ac, char **av, char **env)
{
    if (ac == 1)
    {
        char *hola = ft_strdup("./../so_long_mlx/./so_long ../so_long_mlx/maps/map6.ber");
        execve("./../so_long_mlx/./so_long", ft_split(hola, ' '), env);
    }
    if (av)
        ft_printf("a");
}*/
int main(int ac, char **av, char **env)
{
    if (ac == 2)
    {
        char *path[] = {av[1], NULL};
        char *hola = ft_strdup(av[1]);
        if (execve(hola, path, env) == -1)
            perror("Error executing script");
    }

    return 0;
}