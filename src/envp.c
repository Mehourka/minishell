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
#include <linux/limits.h>


//cd
//	change oldpwd and pwd

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

void populate_new_env(char**src_env, char**dest_env)
{
	int i;

	i = 0;
	while(src_env[i])
	{
		if(src_env[i])
			dest_env[i] = src_env[i];
		i++;
	}
}

char**remove_var(char**env, int var_index)
{
	char **new_env;
	
	new_env = get_new_env(get_env_size(env) - 1);
	if(!new_env)
		return NULL;

	free(env[var_index]);
	env[var_index] = NULL;

	populate_new_env(env,new_env);

	free(env); //free pointers array
	return new_env;

}

// add

// start with export and unset

int modify_var(char**env, int index, char*value)//deal with = and index on export 
{
	free(env[index]);
	env[index] = ft_strdup(value);
	if(!env[index])
		return -1;   //delete this function

}

//----------builtins-------


int ft_unset(char*var)
{
	
}


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



