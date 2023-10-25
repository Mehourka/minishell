#include "minishell.h"

char*replace_vars_by_value(char *line, char *const envp[]);

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
	t_exec	**exec_tab = NULL;

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
			// Add modified line to history
			add_history(line);

			// Parse dollard signe
			line = replace_vars_by_value(line,envp);

			//	Parse Modified input
			exec_tab = ft_parse_pipes(line, envp);

			//	Execute Command(s)
			ft_execute_tab(exec_tab, envp);
		}
		free(line);
	}
}
