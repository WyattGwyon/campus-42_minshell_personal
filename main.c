/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:23:05 by clouden           #+#    #+#             */
/*   Updated: 2025/10/22 18:18:46 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;

	i = 0;
	d_len = ft_strlen(dst);
	if (size == 0 || (size == 1 && dst[0] == '\0'))
	{
		return (ft_strlen((char *)src));
	}
	else if ((size == 1 && dst[0] != '\0') || \
			(size > 1 && d_len > size - 1))
	{
		return (size + ft_strlen((char *)src));
	}
	else if (size > 1 && d_len == size - 1)
		return (d_len + ft_strlen((char *)src));
	while (src[i] && d_len + i < size - 1)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + ft_strlen((char *)src));
}


static int	ft_getsize(long n, int neg)
{
	int	size;

	size = 2;
	if (neg == 1)
		size++;
	while (n >= 10)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

static char	*ft_ifzero(char *str)
{
	int	size;

	size = 2;
	str = calloc(1, size);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static char	*ft_buildstr(long n, char *str, int size)
{
	str = calloc(1, size);
	if (!str)
		return (NULL);
	size--;
	str[size] = '\0';
	while (n >= 0)
	{
		if (n == 0 && size == 0)
			return (str);
		else if (n == 0 && size == 1)
		{
			size--;
			str[size] = '-';
			return (str);
		}
		else
		{
			size--;
			str[size] = (n % 10) + '0';
			n /= 10;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	long	num;

	str = NULL;
	num = n;
	if (num == 0)
	{
		str = ft_ifzero(str);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (num < 0)
	{
		num = num * -1;
		size = ft_getsize(num, 1);
	}
	else
		size = ft_getsize(num, 0);
	str = ft_buildstr(num, str, size);
	if (str == NULL)
		return (NULL);
	return (str);
}

	
int	ft_isshelloperator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	append_token(t_token_node **head, char *value, t_token_type type)
{
	t_token_node	*new_node;
	t_token_node	*temp;
	
	new_node = calloc(1, sizeof(t_token_node));
	new_node->value = strdup(value);
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
void	handle_quote_state(char c, t_token_states *state)
{
	if (c == '"' )
	{
		if (*state == NORMAL)
			*state = IN_DQTS;
		else if (*state == IN_DQTS)
			*state = NORMAL;
	}
	else if (c == '\'') 
	{
		if (*state == NORMAL)
			*state = IN_SQTS;
		else if (*state == IN_SQTS)
			*state = NORMAL;
	}
}


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
	else if (buffer[0] && state == NORMAL)
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
	token_node->value = strdup(buffer);
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
		if (strchr(tmp->value, '$'))
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
	char buffer [1024];

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
	token_node->value = strdup(buffer);
}

void	purge_quotes(t_token_node **token_head)
{
	t_token_node *tmp;
	int i = 0;

	tmp = *token_head;
	while (tmp)
	{
		if (tmp->type == WORD_TK
			&& (strchr(tmp->value, '\'') || strchr(tmp->value, '"')))
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
	t_data 			*data = calloc(1, sizeof(t_data));
	

	if (argc > 1 && argv[1])
		return (1);
	init_data(data, envp);
	while (1)
	{	
		data->line = readline(data->prompt);	
		if (!data->line || strcmp(data->line, "exit") == 0)
			break;
	
		ft_tokenizer(data->line, &data->token_head);
		expand_tokens(&data->token_head, data);
		purge_quotes(&data->token_head);
		t_token_node *tmp = data->token_head;
		while (tmp)
		{
			printf("%s\n", tmp->value);
			tmp = tmp->next;
		}
		free_tklst(&data->token_head);
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
