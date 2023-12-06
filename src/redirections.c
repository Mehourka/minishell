/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:40:47 by kmehour           #+#    #+#             */
/*   Updated: 2023/12/06 17:40:48 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_in_redir(char *path, t_exec_node *node, int tk_type)
{
	int	fd;

	fd = -1;
	(void) tk_type;
	if (access(path, R_OK) == -1)
	{
		node->error_flag = true;
		ft_raise_err(path, "No such file or directory", 1);
	}
	else
	{
		if (node->input > 2)
			close(node->input);
		fd = ft_open(path, O_RDONLY, 0777);
		node->input = fd;
	}
}

void	ft_handle_out_redir(char *path, t_exec_node *node, int tk_type)
{
	int	fd;

	fd = -1;
	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
	{
		node->error_flag = true;
		ft_putstr_fd(" \n", STDERR_FILENO);
		ft_raise_err(path, "Permission denied", 1);
	}
	else
	{
		if (node->output > 2)
			close(node->output);
		if (tk_type == TK_OUT_REDIR)
			fd = ft_open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			fd = ft_open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
		node->output = fd;
	}
}

void	ft_handle_redirections(t_exec_node *node, t_ms_token *tk_ptr)
{
	int		tk_type;
	char	*path;

	path = tk_ptr->next->content;
	tk_type = tk_ptr->tk_type;
	if (tk_type == TK_IN_REDIR)
		ft_handle_in_redir(path, node, tk_type);
	if (tk_type == TK_OUT_REDIR || tk_type == TK_OUT_REDIR_AP)
		ft_handle_out_redir(path, node, tk_type);
}
