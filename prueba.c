# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include "Libft/libft.h"

int main(int ac, char **av, char **env)
{
    if (ac == 1)
    {
        char *hola = ft_strdup("./../so_long_mlx/./so_long ../so_long_mlx/maps/map6.ber");
        execve("./../so_long_mlx/./so_long", ft_split(hola, ' '), env);
    }
    if (av)
        ft_printf("a");
}
