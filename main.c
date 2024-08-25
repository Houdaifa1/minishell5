#include "minishell.h"

void print_use_list(t_data *head) // for testing
{
    t_data *temp = head;
    int i = 0;
    while (temp)
    {
        while (temp->argumment[i] != NULL)
        {
            printf("Arg %d:%s\n", i, temp->argumment[i]);
            i++;
        }
        i = 0;
        temp = temp->next;
        if (temp)
        {
            printf("---- Next Command ----\n");
        }
    }
}

int main(int arc, char **arv, char **envp)
{
    t_data *data;
    t_env   *env_var;
    char *input;
    char *temp;

    env_var = env_to_list(envp);
    data = NULL;
    while (1)
    {
        
        input = readline(temp = print_prompt(env_var));
        if (input[0] != '\0')
        {
            if (parse_line(&data, input) == 0)
            {
                add_history(input);
                exec_commandes(data, &env_var);  
            }
        }
        ft_free_list(data); 
        data = NULL;
        free(temp);
        free(input);
    }
    ft_free_list2(env_var);
}
