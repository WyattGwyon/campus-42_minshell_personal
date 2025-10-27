/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ops.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 16:48:17 by clouden           #+#    #+#             */
/*   Updated: 2025/10/22 19:02:44 by clouden          ###   ########.fr       */
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
