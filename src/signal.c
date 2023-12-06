/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:46 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:47 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <termios.h>

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT && get_ms()->heredeoc_mode == false)
	{
		write(1, "\n", 1);
		ft_putchar_fd('\0', STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * Setup terminal to prevent "^C" output on SIGINT
 **/
void	ft_setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

/**
 * Handel SIGINT and ignore SIGQUIT
*/
void	ft_set_signal_actions(int mode)
{
	if (mode == SIG_MAIN)
	{
		ft_setup_term();
		signal(SIGINT, ft_handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == SIG_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	sigint_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, ">\n", 2);
		if (get_ms()->hdline)
		{
			free(get_ms()->hdline);
			get_ms()->hdline = NULL;
		}
		close(get_ms()->hd_fd);
		ft_free_n_exit(222);
	}
}
