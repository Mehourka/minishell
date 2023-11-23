
#include "minishell.h"

/* 
	@brief Check if token is any redirection type
*/
int	ft_is_redirection(t_ms_token *tk_ptr)
{
	return (tk_ptr->tk_type == TK_IN_REDIR ||
			tk_ptr->tk_type == TK_OUT_REDIR ||
			tk_ptr->tk_type == TK_OUT_REDIR_AP);
}


void ft_handle_redirections(t_exec_node *node, t_ms_token *tk_ptr)
{
	int tk_type;

	tk_type = tk_ptr->tk_type;
	(void) node;
	(void) tk_ptr;

	char *path = tk_ptr->next->content;

	if (tk_type == TK_IN_REDIR)
	{
		// Check if file is readable ?
		printf("DEBUG - Checking infile %s\n", path);
		if (access(path, R_OK) == -1)
			ft_raise_err("infile redirection error", 1);
		else
		{
			int fd = open(path, O_RDONLY);
			printf("DEBUG - opened %s with fd %i\n", path, fd);
			printf("DEBUG - node path %s\n", node->path);
			node->input = fd;
		}
		// Set node->input
	}

	if (tk_type == TK_OUT_REDIR)
	{	
		// Create file with truncation
		//Set node->output
	}

	if (tk_type == TK_OUT_REDIR_AP)
	{
		// create or append to the file
	}


}


/*
	@breif Create a t_exec_node linked list from the t_ms_token list
	@param head Head of the token linked list
	@return t_exec_node linked list
 */
t_exec_node *ft_init_exec_list(t_ms_token *tk_head)
{
	t_exec_node	*head;
	t_ms_token	*tk_ptr;
	t_exec_node	*curr_node;
	char		*strcmd;

	tk_ptr = tk_head;
	curr_node = ft_creat_exec_node();
	head = curr_node;
	strcmd = NULL;

	while(tk_ptr)
	{
		if (tk_ptr->tk_type == TK_STR)
		{
			if (tk_ptr->content == NULL)
				tk_ptr->content = " "; // Handles cat ""
			strcmd = ft_strjoin_char(strcmd, tk_ptr->content, 29);
		}
		if (tk_ptr->tk_type == TK_PIPE)
		{
			ft_parse_input(strcmd, curr_node);
			strcmd = NULL;
			curr_node->next = ft_creat_exec_node();
			curr_node = curr_node->next;
		}
		// if redirct
			// update curr_node->in/out
		if(ft_is_redirection(tk_ptr))
		{
			printf("DEBUG - Handling redirections !!!\n");
			ft_handle_redirections(curr_node, tk_ptr);
			tk_ptr = tk_ptr->next;
		}
		// if Heredoc
		//	create heredoc file and getnextline until EOF
			tk_ptr = tk_ptr->next;
	}
	ft_parse_input(strcmd, curr_node);
	return head;
}

/* 
	@brief assigns the current node in/out according the the redirection
 */
void ft_handle_redirection()
{

}


/*
	@brief Raise error

	@param err_str Error message to be printed
	@param err_nb Exit status number
*/
void	ft_raise_err(char *err_str, int err_nb)
{
	char *mod_err_str;

	// TODO : add free gc function

	// Distinguish between our raised errors, to be removed !!
	mod_err_str = ft_strjoin("MINISHELL ERROR - ", err_str); // DEBUG line
	perror(mod_err_str);
	gc_free_all();
	exit(err_nb);
}

/*
	@brief Executes a single t_exec_node after setting in and outs
*/
void	ft_execute_node(t_exec_node *cmd)
{
	int res;
	res = -1;
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		// ft_set_signal_actions(SIG_CHILD);
		if (cmd->input != STDIN_FILENO)
		{
			dup2(cmd->input, STDIN_FILENO);
			close(cmd->input);
		}
		if (cmd->output != STDOUT_FILENO)
		{
			dup2(cmd->output, STDOUT_FILENO);
			close(cmd->output);
		}
		close(cmd->pfd[0]);
		close(cmd->pfd[1]);
		if (cmd->path)
			res = execve(cmd->path, cmd->tab, get_ms()->env);
		ft_raise_err("command not found", res);
		exit(555);
	}
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
}

/*
	@brief Execute t_exec_node list
*/
void ft_execute_list(t_exec_node *head)
{
	t_exec_node	*ptr;

	ptr = head;
	while (ptr)
	{
		ft_set_node_pipes(ptr);
		ft_execute_node(ptr);
		ptr = ptr->next;
	}

	ptr = head;
	while (ptr)
	{
		waitpid(ptr->pid, NULL, 0);
		close(ptr->pfd[0]);
		close(ptr->pfd[1]);
		ptr = ptr->next;
	}
}
