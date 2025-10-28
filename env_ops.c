/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:17 by clouden           #+#    #+#             */
/*   Updated: 2025/10/28 20:15:51 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


t_env_node *get_env_node(t_env_node *env_head, char *name)
{
	int i = 0;
	while (isalpha(name[i]) || name[i] == '_')
			i++;
	while (env_head)
	{
		if (ft_strncmp(env_head->name, name, i) == 0)	
		{
			return (env_head);
		}
		env_head = env_head->next;
	}
	return (NULL);
}

void *set_env_node(t_env_node **env_head, char *name , char *input_value)
{
	t_env_node 	*temp;
	
	temp = get_env_node(*env_head, name);
	if (temp == NULL)
	{
		append_env(env_head, name, input_value);
	}
	else
	{
		if (input_value != NULL)
		{
			free(temp->value);
			temp->value = ft_strdup(input_value);
		}
		
	}
}

void remove_env(t_data *data, t_env_node *curr, t_env_node *prev)
{
	if (prev)
		prev->next = curr->next;
	else
		data->env_head = curr->next;
	free_env_node(curr);
}
