#include "../minishell.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    if (s1 == NULL || s2 == NULL)
        return (1);
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return(s1[i] - s2[i]);
}

void exec_simple_commande(t_data *commande, t_env **envp)
{
    if (ft_strcmp(commande->argumment[0], "echo") == 0)
        exec_echo(commande->argumment);
    else if (ft_strcmp(commande->argumment[0], "pwd") == 0)
        exec_pwd(commande->argumment);
    else if (ft_strcmp(commande->argumment[0], "cd") == 0)
        exec_cd(commande->argumment, *envp);
    else if (ft_strcmp(commande->argumment[0], "export") == 0)
        exec_export(commande->argumment, envp);
    else if (ft_strcmp(commande->argumment[0], "env") == 0)
        exec_env(commande->argumment, *envp);
    else if (ft_strcmp(commande->argumment[0], "unset") == 0)
        exec_unset(commande->argumment, envp);
}

void exec_commandes(t_data *commandes, t_env **envp)
{
    if (commandes->next == NULL && commandes != NULL)
        exec_simple_commande(commandes, envp);
}