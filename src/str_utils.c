#include "minishell.h"

char	*ft_strjoin_sep(const char *s1, const char *s2, const char *separator)
{
	size_t	len_str1;
	size_t	len_str2;
	size_t	len_sep;
	// char	*separator;
	char	*new_string;

	if (separator == NULL)
		separator = "";
	len_str1 = ft_strlen(s1);
	len_str2 = ft_strlen(s2);
	len_sep  = ft_strlen(separator);
	new_string = gc_calloc((len_str1 + len_sep + len_str2 + 1), 1);
	if (!new_string)
		return (NULL);
	new_string[len_str1 + len_sep + len_str2] = '\0';
	ft_memcpy(new_string, (void *)s1, len_str1);
	ft_memcpy((new_string + len_str1), separator, 1);
	ft_memcpy((new_string + len_str1 + 1), (void *)s2, len_str2);
	return (new_string);
}

char	*ft_strjoin_char(const char *s1, const char *s2, char c)
{
	char sep[2];

	sep[0] = c;
	sep[1] = '\0';
	return ft_strjoin_sep(s1, s2, sep);
}

/*
	@brief Concatenate two strings, joined with a chosen separator

	@param parent left part of the joined path
	@param child right part of the joined path
	@return Full path string, Null if memory allocation crashed
*/
char *ft_strjoin_path(const char *parent, const char *child)
{
	return ft_strjoin_sep(parent, child, "/");
}

char	**ft_parse_cmd(char *cmd_str)
{
	char **new_tab;
	int i;

	new_tab= ft_split(cmd_str, SPLIT_SEP);
	i = 0;

	while (new_tab && new_tab[i])
	{
		if (new_tab[i][0] == '\e')
			new_tab[i][0] = '\0';
		i++;
	}
	return (new_tab);
}
