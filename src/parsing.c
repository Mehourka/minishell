# include "minishell.h"


/* 
	@brief Check if a cher is a white space
 */
int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	ft_change_wspace(char *str)
{
	int i;
	char *next_quote;

	i = 0;
	while (str[i]){
		if (is_whitespace(str[i])){
			str[i] = SPLIT_SEP;
		}
		if( str[i] == '"' || str[i] == '\'')
		{
			next_quote = ft_strchr(&str[i + 1], str[i]);
			if (next_quote){
				// *next_quote = SPLIT_SEP;
				// str[i] = SPLIT_SEP;
				i += (next_quote - &str[i]);
			}
		}

		i++;
	}
}

char	**ft_parse_cmd(char *cmd_str)
{
	char **new_tab;

	ft_change_wspace(cmd_str);
	new_tab= ft_split(cmd_str, SPLIT_SEP);
	return (new_tab);
}

/*
Gets the first word of a string
*/
char	*ft_getfwd(char *str)
{
	int		i;
	char	*word;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != 29)
		i++;
	word = ft_substr(str, 0, i);
	return (word);
}

/* 
	@biref Parse the raw input of a command into a t_exec structure

	@param strcmd Command in string format
	@param envp Environment system variable
 */
t_exec	*ft_parse_input(char *strcmd, char *const envp[])
{
	t_exec	*cmd = NULL;

	cmd = malloc(sizeof(t_exec));

	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->tab = ft_parse_cmd(strcmd);
	cmd->path = ft_get_cmd_path(cmd->tab[0], envp);

	return cmd;
}