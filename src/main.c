/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:43 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/18 18:38:40 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void test_parsing(char *line);

char **copy_envp(char *const envp[])
{
	char **envp_cp;
	int ptr_i;

	ptr_i = 0;
	while(envp[ptr_i])
		ptr_i++;
		
	envp_cp = (char**)malloc(sizeof(char*)*ptr_i+1);
	if(!envp_cp)
		return NULL;
		
	ptr_i = 0;
	while(envp[ptr_i])
	{
		envp_cp[ptr_i] = ft_strdup(envp[ptr_i]);
		//free if error		
		ptr_i++;	
	}
	envp_cp[ptr_i] = NULL;
	return envp_cp;
}

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	char	**envp_cp;
	(void)	argc;
	(void)	argv;
	t_exec	*command;

	ft_set_signal_actions(SIG_MAIN);
	while (1)
	{
		//	copy envp
		envp_cp = copy_envp(envp);

		//	Readline
		line = readline("minishell > ");

		//	Check exit conditions
		if (!line || ft_strcmp(line, "exit") == 0)
		{
			printf("exit\n");
			exit(0);
		}
		//	Append to history
		if (*line)
		{
			add_history(line);
			//	Parse Input
			command = ft_parse_input(line, envp_cp);
			
			//	Execute Command(s)
			ft_execute(command, envp_cp);
		}
		free(line);
	}
}
