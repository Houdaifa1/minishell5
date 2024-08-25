#include "../minishell.h"

void exec_env(char **commande, t_env *envp)
{
    if (commande[1] == NULL)
    {
        ft_print_env(envp);
    }
    else
        printf("env: ‘%s’: No such file or directory\n", commande[1]);
}