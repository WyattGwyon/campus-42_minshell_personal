/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:18:37 by clouden           #+#    #+#             */
/*   Updated: 2025/10/27 13:57:37 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void shift_token(t_token_node **token_head)
{
	t_token_node *temp;
	t_token_node *temp2;
	
	if (!(*token_head)->next)
	{
		free_tklst(token_head);
		*token_head = NULL;
		return ;
	}
	temp = (*token_head)->next;
	temp2 = *token_head;
	*token_head = temp;
	if (temp2->value)
		free(temp2->value);
	free(temp2);
}

void	append_token(t_token_node **head, char *value, t_token_type type)
{
	t_token_node	*new_node;
	t_token_node	*temp;
	
	new_node = ft_calloc(1, sizeof(t_token_node));
	new_node->value = ft_strdup(value);
	new_node->type = type;
	if (!*head)
	{
		*head = new_node; 
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}


void	handle_redir_token(char **str, t_token_node **head)
{
	static	t_token_node tokens[] =
	{
		{">>", OUT_REDIR_AP_TK, NULL},
		{">", OUT_REDIR_AP_TK, NULL},
		{"<<", HERE_DOC_TK, NULL},
		{"<", IN_REDIR_TK, NULL},
	};
	int 	state = 0;
	
	if (**str == '>')
	{
		if (*((*str) + 1) == '>')
		{
			state = 0;
			(*str) += 2;
		}
		else 
		{
			state = 1;
			(*str)++;
		}
	}
	else if (**str == '<')
	{
		if (*((*str) + 1) == '<')
		{	
			state = 2;
			(*str) += 2;
		}
		else 
		{
			state = 3;	
			(*str)++;
		}
	}	
	append_token(head, tokens[state].value, tokens[state].type);
}


