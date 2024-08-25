#include "../minishell.h"

void ft_print_env(t_env *envp)
{
    while (envp)
    {
        printf("%s", envp->var);
        if (envp->val)
            printf("\"%s\"\n", envp->val);
        else
            printf("\n");
        envp = envp->next;
    }
}
int ft_isalpha(int c, int i)
{
    if (i == 2)
    {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            return (0);
    }
    else
    {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
            return (0);
    }
    return (1);
}
int ft_contain_equal(char *commande)
{
    int i;
    int check;

    i = 0;
    check = 1;
    while (commande[i])
    {
        if (commande[i] == '=')
            check = 0;
        i++;
    }
    return (check);
}
int check_argument(char *commande)
{
    int i;

    if (commande[0] == '-')
    {
        printf("export: %s: invalid option\n", commande);
        return (1);
    }
    if (ft_isalpha(commande[0], 1) == 1)
        return (1);
    i = 0;
    while (commande[i] != '=' && commande[i] != '\0')
    {
        if (commande[i + 1] == '=' && commande[i] == '+')
        {
            return (2);
        }
        else if (ft_isalpha(commande[i], 2) == 1)
            return (1);
        else
            i++;
    }
    if (commande[i] == '\0')
        return (3);
    return (0);
}
int ft_strcmp2(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1 || !s2)
        return (1);
    while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '+' && s1[i] == s2[i])
        i++;
    if ((s1[i] == '=' && s2[i] == '\0') || (s2[i] == '=' && s1[i] == '\0'))
        return (0);
    if (s2[i] == '+' && (s1[i] == '\0' || s1[i] == '='))
        return(0);
    return (s1[i] - s2[i]);
}
int ft_update_val(t_env **envp, char *var, char *val)
{
    t_env *temp;
    int check;

    check = 0;
    temp = *envp;

    while (temp != NULL)
    {
        if (ft_strcmp2(temp->var, var) == 0)
        {
            if (val != NULL)
            {
                if (temp->val != NULL)
                    free(temp->val);
                free(temp->var);
                temp->var = ft_strdup(var);
                temp->val = ft_strdup(val);
            }
            check = 1;
        }
        temp = temp->next;
    }
    return (check);
}
void create_env(t_env **temp, t_env **envp, t_env *check)
{
    if ((*temp) == NULL)
        (*envp) = check;
    else
    {
        while ((*temp)->next)
            (*temp) = (*temp)->next;
        (*temp)->next = check;
    }
}
void add_to_env(t_env **temp, t_env **envp, t_env *node)
{
    t_env *iterate;
    char *hold;

    iterate = *envp;
    while(iterate)
    {
        if (ft_strcmp2(iterate->var, node->var) == 0)
        {
            printf("dsqd\n");
            if (iterate->val == NULL)
            {
                iterate->var = ft_strjoin(hold = iterate->var, "=", 1, 1);
                iterate->val = ft_strdup(node->val);
            }
            else
                iterate->val = ft_strjoin((hold = iterate->val), node->val, 1, 1);
            free(hold);
            return;
        }
        iterate = iterate->next;
    }
    create_env(temp, envp, node);
}
void exec_export(char **commande, t_env **envp)
{
    t_env *temp;
    t_env *check;
    int j;
    int i;

    if (commande[1] == NULL)
        ft_print_env(*envp);
    else
    {
        j = 1;
        while (commande[j])
        {
            i = 0;
            temp = *envp;
            if (check_argument(commande[j]) == 0 || check_argument(commande[j]) == 3)
            {
                if (check_argument(commande[j]) == 3)
                    check = ft_one_node2(commande[j]);
                else
                    check = ft_one_node(commande[j]);
                if (ft_update_val(envp, check->var, check->val) == 0)
                    create_env(&temp, envp, check);
                else
                    free(check);
            }
            else if (check_argument(commande[j]) == 2)
                add_to_env(&temp, envp, ft_one_node(commande[j]));
            else
                printf("export: `%s': not a valid identifier\n", commande[j]);
            j++;
        }
    }
}
