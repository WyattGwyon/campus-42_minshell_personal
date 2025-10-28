/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:51:41 by clouden           #+#    #+#             */
/*   Updated: 2025/10/28 18:54:33 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int env_length(t_env_node *env_head)
{
	int i = 0;
	while (env_head)
	{
		env_head = env_head->next;
		i++;
	}
	return (i);
}
