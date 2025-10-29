/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 13:41:48 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 13:48:41 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void ft_tokenize_words(char **str, t_token_node **token_head)
{
	char buffer[1024] = {0};
	t_token_states state; 
	state = NORMAL;
	int i = 0;

	while (**str)
	{
		if (ft_isshelloperator(**str))
			break;
		if (isspace(**str) && state == NORMAL)
			break;
		handle_quote_state(**str, &state);
		buffer[i++] = **str;
		
		(*str)++;
	}
	if (buffer[0] && state != NORMAL)
	{
		printf("syntax error\n");
	}
	else if (state == NORMAL)
	{	
		append_token(token_head, buffer, WORD_TK);
	}
}

void ft_tokenizer(char *str, t_token_node **token_head)
{
	while (*str)
	{
		while (isspace(*str))
			str++;
		if (ft_isshelloperator(*str))
		{
			if (*str != '|')
				handle_redir_token(&str, token_head);
			else
			{
				append_token(token_head, "|", PIPE_TK);
				str++;
			}
		}
		else
		{
			ft_tokenize_words(&str, token_head); 
		}
	}
}

