
# include "execution.h"
# include "parsing.h"
# include "testing.h"

/*
	@brief Concatenate strings, joined with '/'

	@param parent left part of the joined path
	@param child right part of the joined path
	@return Full path string, Null if memory allocation crashed
*/
char	*ft_strjoin_path(const char *parent, const char *child)
{
	size_t	len_str1;
	size_t	len_str2;
	size_t	len_sep;
	char	*separator;
	char	*new_string;

	separator = "/";
	len_str1 = ft_strlen(parent);
	len_str2 = ft_strlen(child);
	len_sep  = ft_strlen(separator);
	new_string = malloc(len_str1 + len_sep + len_str2 + 1);
	if (!new_string)
		return (NULL);
	new_string[len_str1 + len_sep + len_str2] = '\0';
	ft_memcpy(new_string, (void *)parent, len_str1);
	ft_memcpy((new_string + len_str1), separator, 1);
	ft_memcpy((new_string + len_str1 + 1), (void *)child, len_str2);
	return (new_string);
}

/*
	@brief Search and check access to a command in PATH

	@param cmd Command name
	@param envp Enviroment variable
	@return return the command path if accessible, NULL otherwise
 */
char	*ft_get_cmd_path(char *cmd, char *const envp[])
{
	char	**path_tab;
	char	*tmp;
	int		res;
	int		i;

	i = 0;
	path_tab = ft_get_envpaths(envp);
	res = -1;
	while (path_tab[i])
	{
		tmp = ft_strjoin_path(path_tab[i], cmd);
		res = access(tmp, R_OK);
		if (res == 0)
			break ;
		free(tmp);
		i++;
	}
	ft_free_tab(path_tab);
	if (res == 0)
		return (tmp);
	return (NULL);
}

/*
	@brief extracts the PATH variable from the env in a table

	@param envp Environment variable
	@return A char table[][] containing PATH folders
*/
char	**ft_get_envpaths(char *const envp[])
{
	char	*env_paths;
	char	**tab;

	env_paths = "";
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			env_paths = ft_strdup(*envp + 5);
		}
		envp++;
	}
	tab = ft_split(env_paths, ':');
	free(env_paths);
	return (tab);
}

/*
	@brief Create a pipe and set in/out for each command
 */
void ft_set_pipes(t_exec **exec_tab, int cmd_count)
{
	int i;

	i = 0;
	while (cmd_count > 1 && i < cmd_count - 1)
	{
		// TODO
		if (pipe(exec_tab[i]->pfd) == -1)
		{
			ft_raise_err("Pipe error", 4);
		}
		exec_tab[i]->output = exec_tab[i]->pfd[1];
		exec_tab[i + 1]->input = exec_tab[i]->pfd[0];
		i++;
	}
}