/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:03:07 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 16:57:11 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	arr_len(char **arr)
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

void *safe_calloc(t_data *data, size_t size, size_t sizeoftp)
{
	void *ptr;
	
	ptr = ft_calloc(size, sizeoftp);
	if (!ptr)
	{
		clean_all(data);
		exit(1);
	}
	return (ptr);
}

void *safe_realloc(t_data *data, void *arr, size_t size)
{
	void *ptr;

	ptr = realloc(arr, size);
	if (!ptr)
	{
		clean_all(data);
		exit(1);
	}
	return (ptr);
}

void	handle_arg(t_data *data, t_cmd_node *cmd)
{
	int		len;
	char	**temp;

	if (!cmd->argv)
	{
		cmd->argv = safe_calloc(data,1 + 1, sizeof(char *));
		cmd->argv[0] = ft_strdup(data->token_head->value);
	}	
	else
	{
		len = arr_len(cmd->argv);
		cmd->argv = safe_realloc(data, cmd->argv, (len + 1 + 1) * sizeof(char *));
		cmd->argv[len] = ft_strdup(data->token_head->value);
		cmd->argv[len + 1] = NULL;
	}
	cmd->prev_token = WORD_TK;
}

void	handle_infile(t_data *data, t_cmd_node *cmd, int hd)
{
	int		len;
	char 	**temp_arr; // char *infile[];
	if (!cmd->infile)
	{
		cmd->infile = safe_calloc(data,1 + 1, sizeof(char *));
		cmd->heredoc = safe_calloc(data,1 + 1,sizeof(int));
		cmd->infile[0] = ft_strdup(data->token_head->value);
		cmd->heredoc[0] = hd;
	}
	else
	{
		len = arr_len(cmd->infile);
		cmd->infile = safe_realloc(data,cmd->infile, (len + 1 + 1) * sizeof(char *));
		cmd->heredoc = safe_realloc(data, cmd->heredoc, (len + 1 + 1) * sizeof(char *));
		cmd->infile[len] = ft_strdup(data->token_head->value);
		cmd->infile[len + 1] = NULL;
		cmd->heredoc[len] = hd;
		cmd->heredoc[len + 1] = -1;

	}
}

	
void	handle_outfile(t_data *data, t_cmd_node *cmd, int wm)
{
	int		len;
	char 	**temp_arr; // char *infile[];
	if (!cmd->outfile)
	{
		cmd->outfile = safe_calloc(data,1 + 1, sizeof(char *));
		cmd->write_modes = safe_calloc(data,1 + 1,sizeof(int));
		cmd->outfile[0] = ft_strdup(data->token_head->value);
		cmd->write_modes[0] = wm;
	}
	else
	{
		len = arr_len(cmd->outfile);
		cmd->outfile = safe_realloc(data,cmd->outfile, (len + 1 + 1) * sizeof(char *));
		cmd->write_modes = safe_realloc(data, cmd->write_modes, (len + 1 + 1) * sizeof(char *));
		cmd->outfile[len] = ft_strdup(data->token_head->value);
		cmd->outfile[len + 1] = NULL;
		cmd->write_modes[len] = wm;
		cmd->write_modes[len + 1] = -1;

	}
}

void	handle_file(t_data *data, t_cmd_node *cmd)
{
	if (cmd->prev_token == IN_REDIR_TK || cmd->prev_token == HERE_DOC_TK)
	{
		if (cmd->prev_token == IN_REDIR_TK)
			handle_infile(data, cmd, 0);
		else 
			handle_infile(data, cmd, 1);
	}
	else
	{
		if (cmd->prev_token == OUT_REDIR_TR_TK)
			handle_outfile(data, cmd, O_TRUNC | O_CREAT | O_WRONLY);
		else
			handle_outfile(data,cmd, O_APPEND | O_CREAT | O_WRONLY);
	}
	cmd->prev_token = WORD_TK;
}

void	handle_redir(t_data *data, t_cmd_node *cmd)
{
	cmd->prev_token = data->token_head->type;
}


void	handle_error(t_data *data, t_cmd_node *cmd)
{
	ft_putendl_fd("syntax error\n", 2);
}

void handle_exit(t_data *data, t_cmd_node *cmd)
{
	(void)cmd;
	shift_token(&data->token_head);
}

void load_state_function(void (*state_function[])(t_data *, t_cmd_node *))
{
	state_function[START] = NULL;
	state_function[WORD] = handle_arg;
	state_function[FILENM] = handle_file;
	state_function[REDIR] = handle_redir;
	state_function[ERROR] = handle_error;
	state_function[EXIT] = handle_exit;
}

void	get_next_state(int *current_state, int token)
{
	const int state[6][6] = {
		{1, 3, 3, 3, 3, 4}, //START
		{1, 3, 3, 3, 3, 5}, //WORD
		{1, 3, 3, 3, 3, 5},
		{2, 4, 4, 4, 4, 4},
		{4, 4, 4, 4, 4, 4},
		{5, 5, 5, 5, 5, 5},
	};
	*current_state = state[*current_state][token];	
}

t_builtin_type get_builtin(char **cmd)
{
	if (!cmd || !*cmd[0])
		return (NULL_CMD);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		return (PWD);
	else if (!ft_strncmp(cmd[0], "echo", 4))
		return (ECHO);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		return (CD);
	else if (!ft_strncmp(cmd[0], "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(cmd[0], "exit", 4))
		return (EXIT_BUILTIN);
	else if (!ft_strncmp(cmd[0], "env", 3))
		return (ENV);
	else
		return (NO_BUILTIN);
}

void	automata(t_data *data)
{
	void (*state_function[6])(t_data *, t_cmd_node *);
	int current_state;
	load_state_function(state_function);
	while (data->token_head)
	{
		data->new_cmd = safe_calloc(data, 1, sizeof(t_cmd_node));
		current_state = START;
		while (data->token_head && current_state < ERROR)
		{
			get_next_state(&current_state, data->token_head->type);
			state_function[current_state](data, data->new_cmd);
			if (current_state == EXIT)
				break;
			if (current_state == ERROR)
			{
				free_tklst(&data->token_head);
				free_single_cmd(&data->new_cmd);
				free_cmdlst(&data->cmd_head);
				break;
			}
			shift_token(&data->token_head);
		}
		if (current_state == ERROR)
			break ;
		data->new_cmd->builtin_type = get_builtin(data->new_cmd->argv);
		append_cmd(data);
		data->new_cmd = NULL;
	}
}

