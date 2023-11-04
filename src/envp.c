#include "minishell.h"
char* get_var_string(char *var, char *const envp[]);
int get_char_index(char*s, char c);




//builtins:
void env(char *const envp[])
{
    while(*envp)
    {
        printf("%s\n",*envp);
        envp++;
    }
}


//env utils

int get_var_index(char *var, char *const envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0 &&
			get_char_index(envp[i],'=') == (int)ft_strlen(var))
			return i;
		i++;
	}
	//look user variables
	return -1;
}



size_t get_env_size(char**env)
{
	size_t size;

	size = 0;
	while(env[size])
		size++;

	return size;
}

char** get_new_env(size_t size)
{
	char **new_env;

	new_env = (char**)malloc(sizeof(char*) * (size + 1));
	if(!new_env)
		return NULL;
	
	new_env[size] = NULL;

	return new_env;
}
/*
void populate_new_env(char**src_env, char**dest_env)
{
	int i;

	i = 0;
	while(src_env[i]) //review this function entirely
	{
		//if(src_env[i])
		dest_env[i] = src_env[i];
		i++;
	}
}*/

char** copy_system_env(char**env)
{
	char **new_env;
	int i;

	i = 0;
	new_env = get_new_env(get_env_size(env));
	if(!new_env)
		return NULL;

	while(new_env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if(new_env[i])
			return NULL;
		i++;
	}

	return new_env;
}

//--------builtints utils

char** remove_var(char*var_to_remove,char**env)
{
	char **new_env;
	int i;
	int j;

	i = 0;
	j = 0;
	new_env = get_new_env(get_env_size(env) - 1);
	if(!new_env)
		return NULL;

	while(new_env[i])
	{
		if(env[j] == var_to_remove)
			j++;	
		new_env[i] = env[j];
		i++;
		j++;
	}

	free(var_to_remove);

	free(env); //free pointers array
	return new_env;

}

char** add_var(char*var, char**env) //in export test if var qualifies or not
{
	char **new_env;
	int i;

	i = 0;
	new_env = get_new_env(get_env_size(env) + 1);
	if(!new_env)
		return NULL;
	
	
	while(env[i])
	{
		new_env[i] = env[i];
		i++;
	}

	new_env[i] = ft_strdup(var);
	if(!new_env)
		return NULL;
	
	free(env);
	return new_env;
}



int modify_var(char**env, int index, char*value)//deal with = and index on export 
{
	free(env[index]);
	env[index] = ft_strdup(value);
	if(!env[index])
		return -1;   //delete this function

}

//----------builtins-------

//cd
//	change oldpwd and pwd

typedef struct s_env{
	char**env;
}	t_env;





int ft_unset(t_env *s_env, char**cmd)
{	
	char*var_string;
	int i;

	var_string = NULL;
	i = 1; 
	while(cmd[i])
	{
		var_string = get_var_string(cmd[i],s_env->env);
		if(var_string)
			s_env->env = remove_var(var_string,s_env->env);
		i++;
	}
}	


#include <linux/limits.h>
int ft_pwd(void)
{
	char wd[PATH_MAX];

	if(getcwd(wd,PATH_MAX))
	{
		printf("%s\n",wd);
		return 0;
	}

	return 1; //error function here
}

//export
//	export no arg almost like env
//	if var exists, modify it
//	if not, check if valid
//	if valid, modify it

