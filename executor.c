/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:21:29 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 16:18:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void load_builtin_function(int (*builtin_function[])(t_data *, char **))
{
	builtin_function[PWD] = print_working_dir;
	builtin_function[ECHO] = print_echo;
	builtin_function[CD] = cd_builtin;
	builtin_function[EXPORT] = export_builtin;
	builtin_function[UNSET] = unset_builtin;
	builtin_function[EXIT_BUILTIN] = exit_builtin;
	builtin_function[ENV] = print_env;
	builtin_function[NULL_CMD] = NULL;
}

void execute_builtin(t_data *data)
{
	int (*builtin_function[8])(t_data *, char **);

	load_builtin_function(builtin_function);
	data->last_exit_code = builtin_function[data->cmd_head->builtin_type](data, data->cmd_head->argv);
}

void executor(t_data *data)
{
	if (data->cmd_head && !data->cmd_head->next && data->cmd_head->builtin_type < 7)
	{
		execute_builtin(data);
	}
}
