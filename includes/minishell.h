/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:54:43 by clouden           #+#    #+#             */
/*   Updated: 2025/10/30 19:22:35 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <string.h>	
#include <stdio.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

# define R 0
# define W 1

extern volatile sig_atomic_t g_last_signal;

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

typedef enum e_builtin_type
{
	PWD,
	ECHO,
	CD,
	EXPORT,
	UNSET,
	EXIT_BUILTIN,
	ENV,
	NULL_CMD,
	NO_BUILTIN,
} t_builtin_type;

typedef struct s_cmd_node
{
	char				**argv;
	int					*heredoc;
	char 				**infile;
	char 				**outfile;
	int					*write_modes;
	char				*cmd_path;
	int					prev_token;
	t_builtin_type		builtin_type;
	struct s_cmd_node	*next;	
} t_cmd_node;

typedef struct s_exec_data
{
	int	orig_stdin;
	int	orig_stdout;
	char **envp;
	char **path_arr;
} t_exec_data;

typedef	struct s_data
{
	char 			*line;
	char 			*prompt;
	t_token_node	*token_head;
	t_env_node		*env_head;
	t_cmd_node		*cmd_head;
	t_cmd_node		*new_cmd;
	t_exec_data		exec;
	int 			last_exit_code;
	char			*cwd;
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
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_itoa(int n);
int	ft_isshelloperator(char c);
void	handle_redir_token(char **str, t_token_node **head);
void	append_token(t_token_node **head, char *value, t_token_type type);
int print_working_dir(t_data *data, char ** argv);
int exit_builtin(t_data *data, char **argv);
void executor(t_data *data);
int print_env(t_data *data, char **str);
int print_echo(t_data *data, char **argv);
void free_env_node(t_env_node *env_node);
void remove_env(t_data *data, t_env_node *curr, t_env_node *prev);
int unset_env_node(t_data *data, char *name);
int unset_builtin(t_data *data, char **str);
int env_length(t_env_node *env_head);
int export_builtin(t_data *data, char **str);
void *safe_calloc(t_data *data, size_t size, size_t sizeoftp);
void	free_arr(char ***arr);
void *set_env_node(t_env_node **env_head, char *name , char *input_value);
void	handle_quote_state(char c, t_token_states *state);
void ft_tokenizer(char *str, t_token_node **token_head);
int cd_builtin(t_data *data, char **argv);
void init_exec(t_data *data, t_exec_data *exec);
void 	clean_and_exit(t_data *data, int exit_code);
void clean_exec(t_exec_data *exec);
int handle_redirection(t_data *data, t_cmd_node *cmd);
void	sigint_handler(int sig);
#endif
