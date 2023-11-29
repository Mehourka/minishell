
#include "minishell.h"



void test_parsing(char *line){
	ft_change_wspace(line);
	char **list = ft_split(line, SPLIT_SEP);
	ft_print_tab(list);
}

void ft_print_tab(char **list)
{
	int i = 0;

	printf("\n\n\t========= TABLE =========\n");
	while(list[i])
	{
		printf("%s; ", list[i]);
		i++;
	}
	printf("\n\t=========================\n\n");
}


void ft_print_tokens(t_ms_token *head)
{
	int count;
	printf("============== Tokens ==============\n");

	count = 0;
	while(head)
	{
		printf(
			"\tToken #%i\n\tcontent : %s\n\ttoken type : %i\n\n"
			, count, head->content, head->tk_type
		);
		head = head->next;
		count++;
	}
}

void ft_print_exec_node(t_exec_node *head)
{
	printf("\
		============ Command ============\n\
		\tInput : %i\n\
		\tOutput : %i\n\
		\tpfd[0] : %i\n\
		\tpfd[1] : %i\n\
		\tPath : %s\n\
		=================================\n\
		", head->input, head->output, head->pfd[0], head->pfd[1], head->path);
}

void ft_print_exec_nodes(t_exec_node *head)
{
	int count;
	printf("============== Exec nodes ==============\n");

	count = 0;
	while(head)
	{
		ft_print_exec_node(head);
		// ft_print_tab(head->tab);
		printf("-------------------------\n\n");
		head = head->next;
		count++;
	}
}

void print_tokens(t_ms_token*token_list,char*line)
{
	int i;

	i = 1;
	if(token_list)
		printf("\n\033[0;31m%s\n",line);
	while(token_list)
	{
		printf("\033[0;33m\n====================\n\033[0;37m");
		printf("\033[0;32mToken\033[0;34m %i\n", i);
		printf("\033[0;32mcontent:\033[0;34m %s\n",token_list->content);
		printf("\033[0;32mToken type\033[0;34m %i\n", token_list->tk_type);
		printf("\033[0;33m====================\n\033[0;37m");
		i++;
		token_list = token_list->next;
	}
}




