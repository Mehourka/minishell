# include "minishell.h"



# define SPLIT_SEP 22

int is_whitespace(char c){
	return ((c >= 9 && c <= 13) || c == 32);
}

void change_wspace(char *str)
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

void print_list(char **list)
{
	int i = 0;

	while(list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
}