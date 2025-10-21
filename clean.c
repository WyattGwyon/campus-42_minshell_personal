/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:09:30 by clouden           #+#    #+#             */
/*   Updated: 2025/10/21 17:47:05 by clouden          ###   ########.fr       */
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

void	clean_all(t_data *data)
{
	if (data->line)
		free(data->line);
	free_tklst(&data->token_head);
	free_envlst(&data->env_head);
	free(data);
}
