/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 10:50:39 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/14 12:04:16 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>

# define SPLIT_SEP 29

typedef struct s_parse {
	char *cmd_1;
	char *cmd_2;
	char *outfile;
	char *infile;
} t_parse;

// =============== Signals ===============
void	set_signal_actions(void);
void	change_wspace(char *str);


// =============== Parsing ===============
char **parse_cmd(char *cmd_str);


#endif