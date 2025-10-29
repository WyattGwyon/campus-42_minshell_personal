/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:11:27 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 19:14:31 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	append_env(t_env_node **env_head, char *name, char *value)
{
	t_env_node *new_node;
	t_env_node *temp;

	new_node = ft_calloc(1, sizeof(t_env_node));
	new_node->name = ft_strdup(name);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	if (!*env_head)
	{
		*env_head = new_node;
	}			
	else
	{
	
		temp = *env_head;
		while(temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

void	copy_envp(t_env_node **env_node, char **envp)
{
	char *tmpname;
	char *tmpval;

	if (!envp)
		return ;
	while (*envp)
	{
		tmpname = strtok(*envp, "=");
		tmpval = strtok(NULL, " ");
		if (!tmpval)
			tmpval = "";
		append_env(env_node, tmpname, tmpval);
		envp++;		
	}
	return ;
}

void	init_data(t_data *data, char **envp)
{
	data->line = NULL;
	data->prompt = "minishell $";
	data->token_head = NULL;
	data->env_head = NULL;	
	copy_envp(&data->env_head, envp);
	data->cwd = getcwd(NULL, 0);	
	
}


void init_exec(t_data *data, t_exec_data *exec)
{
	t_env_node *temp;
	exec->orig_stdin = dup(STDIN_FILENO);
	exec->orig_stdout = dup(STDOUT_FILENO);
	temp = get_env_node(data->env_head, "PATH");
	if (!temp)
	{
		exec->path_arr = safe_calloc(data, 1, sizeof(char*));
		return ;
	}
	exec->path_arr = ft_split(temp->value, ':');
	if (!exec->path_arr)
	{
		clean_all(data);
		exit(-1);
	}
}
