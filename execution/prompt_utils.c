#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, int flag, int size)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + size);
	if (!join)
		return (NULL);
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	if (flag == 1)
	{
		join[i] = '\0';
		return(join);
	}
    join[i] = '$';
    join[i + 1] = '>';
	join[i + 2] = ' ';
	join[i + 3] = '\0';
	return (join);
}

char *print_prompt(t_env *envp)
{
    char *home;
    char path[PATH_MAX];
    char *prompt;
	int i;

    getcwd(path, PATH_MAX);
	home = ft_getenv(envp, "HOME");
	if (ft_strcmp(path, home) == 0)
		prompt = ft_strjoin("minishell :", "~", 0, 4);
	else
	{
		i = 0;
		while(home && home[i] && path[i] && home[i] == path[i])
			i++;
		if (home && home[i] == '\0')
			prompt = ft_strjoin("minishell :~", &path[i], 0, 4);
		else if (path != NULL)
    		prompt = ft_strjoin("minishell :", path, 0, 4);
	}
    return(prompt);
}
