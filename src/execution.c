/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouellet <aouellet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:08:22 by kmehour           #+#    #+#             */
/*   Updated: 2023/10/18 18:59:28 by aouellet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/* 
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	(void) err_str;
	perror(NULL);
	
	exit(err_nb);
}

/* 
	@brief Execute Command given as a string
*/
int	ft_exec_struct(t_exec *cmd, char *const envp[])
{
	// ft_print_exec_struct(cmd);
	int res;
	
	if (cmd->path)
		res = execve(cmd->path, cmd->tab, envp);
	// ft_free_tab(cmd->tab);
	ft_raise_err("command not found", 1);
 	return (2);
}

void	ft_execute(t_exec *cmd, char *const envp[])
{
	// Cree list de pid
	int pid;


	// set input outpu gracer a dup2()
	
	pid = fork();
	
	if (pid == 0) 
	{
		ft_set_signal_actions(SIG_CHILD);
		ft_exec_struct(cmd, envp);
		exit(555);
	}
	wait(&pid);
}