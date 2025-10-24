/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:54:43 by clouden           #+#    #+#             */
/*   Updated: 2025/10/24 21:18:04 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>	
#include <stdio.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef enum e_token_type
{
	WORD_TK,
	IN_REDIR_TK,
	HERE_DOC_TK,
	OUT_REDIR_TR_TK,
	OUT_REDIR_AP_TK,
	PIPE_TK,
} t_token_type;

typedef enum e_auto_state
{
	START,
	WORD,
	FILENM,
	REDIR,
	ERROR,
	EXIT,
} t_auto_state;

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

typedef struct s_cmd_node
{
	char	**argv;
	int		*heredoc;
	char 	**infile;
	char 	**outfile;
	int		*write_modes;
	char	*cmd_path;
	int		prev_token;
	struct s_cmd_node	*next;	
} t_cmd_node;

typedef	struct s_data
{
	char 			*line;
	char 			*prompt;
	t_token_node	*token_head;
	t_env_node		*env_head;
	t_cmd_node		*cmd_head;
	t_cmd_node		*new_cmd; 
} t_data;

typedef enum e_token_states
{
	NORMAL,
	IN_DQTS,
	IN_SQTS
} t_token_states;

void 	init_data(t_data *data, char **envp);
void	copy_envp(t_env_node **env_node, char **envp);
void	append_env(t_env_node **env_head, char *name, char *value);
void	free_tklst(t_token_node **token_head);
void	free_envlst(t_env_node **env_head);
void	clean_all(t_data *data);
t_env_node *get_env_node(t_env_node *env_head, char *name);
void	free_single_cmd(t_cmd_node **cmd);
void free_cmdlst(t_cmd_node **cmd_head);
void shift_token(t_token_node **token_head);
void append_cmd(t_data *data);
void	automata(t_data *data);
