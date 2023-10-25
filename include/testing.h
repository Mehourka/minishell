
#ifndef TESTING_H
# define TESTING_H

# include "minishell.h"
# include "libft.h"
# include <stdio.h>
# include <unistd.h>


// void	ft_test_parsing(char *line);
void	ft_print_tab(char **list);
// int		ft_exec_strcmd(char *cmd, char *const envp[]);
void	ft_print_exec_struct(t_exec *cmd);

#endif