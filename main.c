/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:23:05 by clouden           #+#    #+#             */
/*   Updated: 2025/11/03 20:59:17 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void append_cmd(t_data *data)
{
	t_cmd_node *temp;
	
	if (!data->cmd_head)
	{
		data->cmd_head = data->new_cmd;
		return ;
	}
	temp = data->cmd_head;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = data->new_cmd;
}

void resolve_quotes(t_token_node *token_node)
{
	int i = 0;
	int b = 0;
	char buffer [1024] = {0};

	while (token_node->value[i])
	{
		if (token_node->value[i] == '\'' || token_node->value[i] == '"')
			i++;
		else	
		{
			buffer[b] = token_node->value[i];
			i++;
			b++;
		}
	}
	free(token_node->value);
	token_node->value = ft_strdup(buffer);
}

void	purge_quotes(t_token_node **token_head)
{
	t_token_node *tmp;
	int i = 0;

	tmp = *token_head;
	while (tmp)
	{
		if (tmp->type == WORD_TK
			&& (ft_strchr(tmp->value, '\'') || ft_strchr(tmp->value, '"')))
		{
			resolve_quotes(tmp);
		}
		tmp = tmp->next;
	}
}

void	sigint_handler(int sig)
{
	rl_replace_line("",0);
	rl_on_new_line();
	rl_done = 1;
	g_last_signal = SIGINT;
}

void sigquit_handler(int sig)
{
		g_last_signal = SIGQUIT;
}

volatile sig_atomic_t g_last_signal;

static int event(void)
{
		return (0);
}

int main(int argc, char *argv[], char **envp)
{
	char 			*line;
	t_token_node	*token_head = NULL;
	t_data 			*data = ft_calloc(1, sizeof(t_data));
	

	if (argc > 1 && argv[1])
		return (1);
	init_data(data, envp);
	rl_event_hook = event;
	while (1)
	{	
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
		data->line = readline(data->prompt);
		if (!data->line)
			break;	
		if (g_last_signal == SIGINT)
		{
			g_last_signal = 0;
			data->last_exit_code = 130;
		}
		else if (g_last_signal == SIGQUIT)
		{
			g_last_signal = 0;
			data->last_exit_code = 131;
		}
		ft_tokenizer(data->line, &data->token_head);
		expand_tokens(&data->token_head, data);
		purge_quotes(&data->token_head);
		automata(data);
		executor(data);
		clean_exec(&data->exec);
		free_tklst(&data->token_head);
		free_cmdlst(&data->cmd_head);
		free(data->line);
	}
	clean_all(data);
	return (0);
}
