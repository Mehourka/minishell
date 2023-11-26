#include "minishell.h"


int verify_arg_input(char*var) 
{
	int i;

	i = 0;
	if(ft_isdigit(var[i]))
		return -1;
	while(var[i] && var[i] != '=')
	{
		if(!ft_isalnum(var[i]) && var[i] != '_')
			return -1;
		i++;
	}

	return 0;
}

void ascii_sort(char**env, size_t len)
{
	size_t i;
	size_t j;
	char *temp;

	i = 0;
    j = 0;
	temp = NULL;
	while(j < len - 1)
	{
		while(i < len - 1)
		{
			if(strcmp(env[i],env[i + 1]) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		i = 0;
		j++;
	}
}
void print_line(char*s)
{
	int i;

	i = 0;
	write(1,"=\"",2);

	while(s[i])
	{
		if(s[i] == '\"')
			write(1,"\\",1);
		write(1,&s[i],1);
		i++;
	}

	write(1,"\"\n",2);

}

void print_sorted_env(char**env)
{
	int i;
	int j;
	char **env_cp;

	i = 0;
    j = 0;
	
	env_cp = copy_env(env);
	if(!env_cp)
		return ;
	ascii_sort(env_cp,get_env_size(env_cp));	
	while(env_cp[i])
	{
		//what about the _= variable? include it or not?
		ft_putstr_fd("declare -x ",1);
        while(env_cp[i][j] != '=')
        {
            write(1,&env_cp[i][j],1);
            j++;
        }
        print_line(env_cp[i] + get_char_index(env_cp[i],'=') + 1);
        j = 0;
		i++;	
	}
}

int ft_export(t_ms*s_ms, char**cmd)
{
	int i;
	int index;
	char* var;

	var = NULL;
	i = 1;
	index = 0;

	if(!cmd[i])
		print_sorted_env(s_ms->env);
	while(cmd[i])
	{
		if(verify_arg_input(cmd[i]) != 0)
			printf("not valid identifier\n");
		else if(get_char_index(cmd[i],'=') != -1)
		{
			var = ft_substr(cmd[i],0,get_char_index(cmd[i],'='));
			if(!var)
				return -1; //replace with error function
			index = get_var_index(var,s_ms->env);
			if(index != -1)
				replace_var(s_ms->env,index,cmd[i]);
			else
				s_ms->env = add_var(cmd[i],s_ms->env);
			
		}
		i++;
	}
	return 0;
} 


//------------------------------------------------------

int ft_unset(t_ms *s_ms, char**cmd)
{	
	char*var_string;
	int i;

	var_string = NULL;
	i = 1; 
	while(cmd[i])
	{
		var_string = get_var_string(cmd[i],s_ms->env);
		if(var_string)
			s_ms->env = remove_var(var_string,s_ms->env);
		i++;
	}
	return 0;
}	


//------------------------------------------------------

int ft_pwd(t_ms *s_ms, char **cmd)
{
	char wd[PATH_MAX];

	(void) s_ms;
	(void) cmd;

	if(getcwd(wd,PATH_MAX))
	{
		printf("%s\n",wd);
		return 0;
	}

	return 1; //error function here
}

//------------------------------------------------------

int ft_env(t_ms*s_ms, char **cmd)
{
	int i;

	(void) cmd;
	i = 0;
    while(s_ms->env[i])
    {
        printf("%s\n",s_ms->env[i]);
        i++;
    }
	printf("--> env size: %d\n",i); //delete
	return 0;
}


//------------------------------------------------------

int n_flag_check(char *cmd)
{
	int i;

	i = 1;
	if(cmd[0] != '-' || cmd[1] != 'n')  
		return -1;
	
	while(cmd[i])
	{
		if(cmd[i] != 'n')
			return -1;
		i++;
	}
	
	return 1;
}

int ft_echo(t_ms *s_ms, char**cmd)
{
	int i;
	int n;

	(void) s_ms;

	i = 1;
	n = 0;

	
	while(cmd[i] && n_flag_check(cmd[i]) == 1)
	{
		n = 1;
		i++;
	}
	while(cmd[i])
	{
		printf("%s",cmd[i]); // TODO: Change with ft_putstr_fd
		if(cmd[i + 1])
			printf(" ");
		i++;
	}
	if(n == 0)
		printf("\n");
	return 0;

}

//------------------------------------------------------

void update_cwd(t_ms*s_ms,char*path,char*old_path)
{
	char *var;
	int index;

	
	var = ft_strjoin("PWD=",path); 
	index = get_var_index("PWD",s_ms->env);
	if(index != -1)
		replace_var(s_ms->env,index,var);

	var = ft_strjoin("OLDPWD=",old_path); 
	index = get_var_index("OLDPWD",s_ms->env);
	if(index != -1)
		replace_var(s_ms->env,index,var);

}

char* ft_getenv(char**env)
{
	char *path;

	path = get_var_string("HOME",env);
	if(path)
	{
		return (path + get_char_index(path,'=') + 1);
	}
	return NULL;
}

int ft_cd(t_ms *s_ms, char **cmd) //deal with cd - ?
{
	char *path;
	char pwd[PATH_MAX];
	char oldpwd[PATH_MAX];
	
	path = NULL;
	if(cmd[1] && cmd[2])
		ft_raise_err("too much args\n",-1);
	if(!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
	{
		path = ft_getenv(s_ms->env);
		if(!path)
		{
			printf("cd: HOME not set\n");
			return -1;
		}
	}
	else
		path = cmd[1];
	if(!getcwd(oldpwd,PATH_MAX))
		return -1;
	if(chdir(path) != 0)
	{
		printf("cd: no such file or directory: %s\n",path);
		return -1;
	}
	if(!getcwd(pwd,PATH_MAX))
		return -1;
	update_cwd(s_ms,pwd,oldpwd);
	return 0;
}