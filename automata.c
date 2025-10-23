/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:03:07 by clouden           #+#    #+#             */
/*   Updated: 2025/10/23 19:06:24 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arr_len(char *arr)
{
	int	i = 0;
	
	if (!arr)
		return (0);
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	word(t_data *data, t_cmd_node **cmd)
{
	int	len;
	char **temp;

	if (!(*cmd)->argv)
	{
		(*cmd)->argv = calloc(1 + 1, sizeof(char *));
		(*cmd)->argv[0] = strdup(data->token_head->value);
	}	
	else
	{
		len = arr_len((*cmd)->argv);
		temp = realloc((*cmd)->argv, len + 1 + 1);
		if (!temp)
		{
			clean_all(data);
			free_single_cmd((*cmd));
			exit(1);
		}
		else
		{
			(*cmd)->argv[len] = temp;
			(*cmd)->argv[len] = strdup(data->token_head->value);
		}
	}
	(*cmd)->prev_token = WORD;
}

void	handle_infile_redir(t_data *data, t_cmd_node **cmd)
{
	if (!cmd->infile)
	{
		set first infile
	}		
}

void	file(t_data *data, t_cmd_node **cmd)
{
	if ((*cmd)->prev_token == IN_REDIR_TK || (*cmd)->prev_token == HERE_DOC_TK)
	{
		handle_infile_redir(
	}
}

void	redir(t_data *data, t_cmd_node **cmd)
{
	(*cmd)->prev_token = data->token_head->type;
}


void	pipe(t_data *data, t_cmd_node *cmd)
{
	
}

void load_state_function(void (*state_function[])(t_data *, t_cmd_node *))
{
	state_function[START] = NULL;
	state_function[WORD] = word;
	state_function[FILENO] = file;
	state_function[REDIR] = redir;
	state_function[ERROR] = error;
	state_function[EXIT] = NULL;
}

int get_next_state(int current_state, int token)
{
	const int state[6][6] = {
		{1, 3, 3, 3, 3, 4},
		{1, 3, 3, 3, 3, 5},
		{1, 3, 3, 3, 3, 5},
		{2, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4},
		{5, 5, 5, 5, 5, 5},
	};
}



