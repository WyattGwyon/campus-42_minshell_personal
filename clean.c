/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:09:30 by clouden           #+#    #+#             */
/*   Updated: 2025/10/28 19:52:08 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	free_tklst(t_token_node **token_head)
{
	t_token_node *tmp;
	t_token_node *tmp2;

	tmp = *token_head;
	while (tmp)
	{
		if (tmp->value)
		{
			free(tmp->value);
		}
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		tmp2 = NULL;
	}
	*token_head = NULL;
}

void free_envlst(t_env_node **env_head)
{
	t_env_node *tmp;
	t_env_node *tmp2;

	tmp = *env_head;
	while (tmp)
	{
		if (tmp->name)
		{
			free(tmp->name);
		}
		if (tmp->value)
		{
			free(tmp->value);
		}
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		tmp2 = NULL;
	}
	*env_head = NULL;
}


void	free_arr(char ***arr)
{	
	int i = 0;

	if (*arr)
	{
		while ((*arr)[i])
		{
			if ((*arr)[i])
				free((*arr)[i]);
			i++;
		}
		free(*arr);
		*arr = NULL;	
	}
}


void	free_single_cmd(t_cmd_node **cmd)
{
	int i = 0;
	free_arr(&(*cmd)->argv);
	free_arr(&(*cmd)->infile);
	free_arr(&(*cmd)->outfile);
	if ((*cmd)->heredoc)
		free((*cmd)->heredoc);
	if ((*cmd)->write_modes)
		free((*cmd)->write_modes);
	if ((*cmd)->cmd_path)
		free((*cmd)->cmd_path);
	free(*cmd);
	*cmd = NULL;
}	

void free_cmdlst(t_cmd_node **cmd_head)
{
	t_cmd_node *tmp;
	
	while (*cmd_head)
	{
		tmp = (*cmd_head)->next;
		free_single_cmd(cmd_head);
		*cmd_head = tmp;
	}
	*cmd_head = NULL;
}

void free_env_node(t_env_node *env_node)
{
	if (env_node->name)
		free(env_node->name);
	if (env_node->value)
		free(env_node->value);
	free(env_node);
}

void	clean_all(t_data *data)
{
	if (data->line)
		free(data->line);
	if (data->cwd)
		free(data->cwd);
	free_tklst(&data->token_head);
	free_envlst(&data->env_head);
	free_cmdlst(&data->cmd_head);
	free(data);
}
