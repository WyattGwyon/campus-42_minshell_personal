/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:23:05 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 13:48:41 by clouden          ###   ########.fr       */
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




void expand_dollar(t_token_node *token_node, char **expander, char *buffer, \
			int *i, t_data *data)
{
	int	exit_code = 130;
	t_env_node *env; 
	char *number;

	(*expander)++;
	if (**expander == '?')
	{
		number = ft_itoa(exit_code);
		ft_strlcat(buffer, number, 1024);
		free(number);
		(*expander)++;
	}
	else if (isalpha(**expander) || **expander == '_' )
	{
		env = get_env_node(data->env_head, *expander);
		if (env)
			ft_strlcat(buffer, env->value, 1024);
		while (isalnum(**expander) || **expander == '_')
			(*expander)++;
	
	}
	else if (isdigit(**expander))
	{
		(*expander)++;
	}
	else 
	{
		buffer[*i] = '$';
		buffer[*i + 1] = **expander;
		(*expander)++;
	}
	*i = ft_strlen(buffer);

}

void expand_single_token(t_token_node *token_node, t_data *data)
{
	t_token_states state = NORMAL;
	char *expander = token_node->value;	
	char buffer[1024] = {0};
	int i = 0;
	
	while (*expander)
	{
		handle_quote_state(*expander, &state);
		if (*expander == '$' && state != IN_SQTS)
		{
			expand_dollar(token_node, &expander, &buffer[0], &i, data);
		}
		else
		{
			buffer[i] = *expander;
			i++;
			expander++;
		}
	}	
	free(token_node->value);
	token_node->value = ft_strdup(buffer);
	return ;

}

void	expand_tokens(t_token_node **token_head, t_data *data)
{	
	t_token_node *tmp;
	int i = 0;
	
	tmp = *token_head;
	while (tmp)
	{
		if (tmp->type != WORD_TK)
			tmp = tmp->next;
		if (ft_strchr(tmp->value, '$'))
		{
			expand_single_token(tmp, data);
		}
		tmp = tmp->next;
	}
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



int main(int argc, char *argv[], char **envp)
{
	char *prompt = "minishell$ ";
	char 			*line;
	t_token_node	*token_head = NULL;
	t_data 			*data = ft_calloc(1, sizeof(t_data));
	

	if (argc > 1 && argv[1])
		return (1);
	init_data(data, envp);
	while (1)
	{	
		data->line = readline(data->prompt);
		if (!data->line)
			break;
	
		ft_tokenizer(data->line, &data->token_head);
		expand_tokens(&data->token_head, data);
		purge_quotes(&data->token_head);
		t_token_node *tmp = data->token_head;
		automata(data);
		executor(data);
		free_tklst(&data->token_head);
		free_cmdlst(&data->cmd_head);
		// for (t_token_node *tmp = data->token_head; tmp;)
		// {
		// 	free(tmp->value);
		// 	t_token_node *tmp2 = tmp;
		// 	tmp = tmp->next;
		// 	free(tmp2);
		// }
		free(data->line);
	}
	clean_all(data);
	return (0);
}
