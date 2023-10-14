/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:43 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/14 12:07:42 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "testing.h"
void test_parsing(char *line);

int	main(void)
{
	char	*line;

	set_signal_actions();
	while (1)
	{
		//init
		line = readline("minishell > ");
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}

		//parser
		char **cmd_tab = parse_cmd(line);
		print_tab(cmd_tab);
		
		//minishell loop
		if (*line)
			add_history(line);
			
		free(line);
	}
}
