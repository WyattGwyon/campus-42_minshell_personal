/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 19:22:19 by clouden           #+#    #+#             */
/*   Updated: 2025/11/03 19:40:40 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void expand_dollar(t_token_node *token_node, char **expander, char *buffer, \
			int *i, t_data *data)
{
	t_env_node *env; 
	char *number;

	(*expander)++;
	if (**expander == '?')
	{
		number = ft_itoa(data->last_exit_code);
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
