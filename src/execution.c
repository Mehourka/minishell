/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:08:22 by kmehour           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/18 18:23:55 by kmehour          ###   ########.fr       */
=======
/*   Updated: 2023/10/15 15:59:40 by kmehour          ###   ########.fr       */
>>>>>>> 52380f134b5b2d153a04be4a4b03360cd744ea78
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
	int pid;

	pid = fork();

	if (pid == 0) 
	{
		ft_exec_struct(cmd, envp);	
	}
<<<<<<< HEAD
	wait(&pid);
=======
	
>>>>>>> 52380f134b5b2d153a04be4a4b03360cd744ea78
}