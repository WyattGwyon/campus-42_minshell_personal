/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:54:43 by clouden           #+#    #+#             */
/*   Updated: 2025/10/17 14:54:46 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_type
{
	WORD_TK,
	PIPE_TK,
	IN_REDIR_TK,
	HERE_DOC_TK,
	OUT_REDIR_TR_TK,
	OUT_REDIR_AP_TK,
} t_token_type;

typedef struct s_token_node
{
	char			*value;
	t_token_type	type;
	struct s_token_node	*next;
} t_token_node; 

typedef struct s_env_node
{
	char *name;
	char *value;
	struct s_env_node *next;
} t_env_node;

typedef	struct s_data
{
	char 			*line;
	char 			*prompt;
	t_token_node	*token_head;
	

} t_data;

typedef enum e_token_states
{
	NORMAL,
	IN_DQTS,
	IN_SQTS
} t_token_states;
