#include "minishell.h"

char*replace_vars_by_value(char *line, char *const envp[]);
char **copy_env(char *const envp[]);
char **env_add(char *const envp[],char*new_var);

void env(char *const envp[]);
int ft_pwd(void);

int	main(int argc, char **argv, char *const envp[])
{
	char	*line;
	char	**envp_cp = NULL;
	(void)	argc;
	(void)	argv;
	t_exec	**exec_tab = NULL;

	ft_set_signal_actions(SIG_MAIN);
	while (1)
	{
		//	copy envp
		envp_cp = copy_env(envp);
		//envp_cp = env_add(envp_cp,"test");
		//env(envp_cp);
		//	Readline
		line = readline("minishell > ");
		ft_pwd();

		
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
			line = replace_vars_by_value(line,envp_cp);

			//	Parse Modified input
			exec_tab = ft_parse_pipes(line, envp_cp);

			//	Execute Command(s)
			ft_execute_tab(exec_tab, envp_cp);
		}
		free(line);
	}
}
