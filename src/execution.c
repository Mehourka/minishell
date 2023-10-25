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
	char *mod_err_str;

	// DEBUG
	// Distinguish between our raised errors, to be removed !!
	mod_err_str = ft_strjoin("MINISHELL ERROR - ", err_str);
	perror(mod_err_str);
	free(mod_err_str);
	exit(err_nb);
}

/*
	@brief Execute Command given as a string
*/
int	ft_exec_struct(t_exec *cmd, char *const envp[])
{
	// ft_print_exec_struct(cmd);
	int res;

	res = -1;
	if (cmd->path)
		res = execve(cmd->path, cmd->tab, envp);
	// ft_free_tab(cmd->tab);
	ft_raise_err("command not found", res);
 	return (2);
}

void	ft_execute(t_exec *cmd, char *const envp[])
{
	// set input outpu gracer a dup2()
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// ft_set_signal_actions(SIG_CHILD);
		dup2(cmd->input, STDIN_FILENO);
		dup2(cmd->output, STDOUT_FILENO);

		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		if (cmd->input != STDIN_FILENO)
			close(cmd->input);
		if (cmd->output != STDOUT_FILENO)
			close(cmd->output);


		ft_exec_struct(cmd, envp);
		exit(555);
	}
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
}

void ft_execute_tab(t_exec **cmd_tab, char *const envp[])
{
	int i;
	// int pfd[2];

	i = 0;
	while (cmd_tab[i])
	{
		ft_execute(cmd_tab[i], envp);
		i++;
	}

	i = 0;
	while (cmd_tab[i])
	{
		wait(&cmd_tab[i]->pid);
		i++;
	}
}

