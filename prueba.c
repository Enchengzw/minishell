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
        char *hola = ft_strdup("cat -e -n test.c");
        execve("/bin/cat", ft_split(hola, ' '), env);
    }
    if (av)
        ft_printf("a");
}