
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include "execution.h"
# include "parsing.h"
# include "libft.h"
# include "readline/readline.h"
# include "readline/history.h"

# include "testing.h"

# define SPLIT_SEP 29

enum sig_mode{
	SIG_MAIN,
	SIG_CHILD
};


// =============== Signals ===============
void	ft_set_signal_actions(int mode);
void	ft_change_wspace(char *str);


// =============== Parsing ===============
char	**ft_parse_cmd(char *cmd_str);


// =============== Errors ===============
void	ft_raise_err(char *err_str, int err_nb);

#endif