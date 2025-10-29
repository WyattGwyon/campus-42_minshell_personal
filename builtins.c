/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:42:59 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 17:56:40 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define EXIT_ERR_ARG_TP "minishell: exit: %s: numeric argument required\n"
#define EXIT_ERR_ARG_C "minishell: exit: too many arguments\n"

int	ft_isvalnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
			i++;
		if (isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
int print_working_dir(t_data *data, char **argv)
{
	(void)argv;
	dprintf(1, "%s\n", data->cwd);
	return (0);
}

int exit_builtin(t_data *data, char **argv)
{
	int exit_code;
	
	dprintf(STDOUT_FILENO, "exit\n");
	if (!argv[1])
		exit_code = 0;
	else if (!ft_isvalnum(argv[1]))
	{
		exit_code = 2;
		dprintf(STDERR_FILENO, EXIT_ERR_ARG_TP, argv[1]);
	}
	else 
	{
		exit_code = ft_atoi(data->cmd_head->argv[1]);
		if (data->cmd_head->argv[2])
			ft_putendl_fd(EXIT_ERR_ARG_C, 2);
	}
	clean_all(data);
	exit(exit_code);
}

int print_env(t_data *data, char **str)
{
	t_env_node *temp;
	(void) str;

	temp = data->env_head;
	while (temp)
	{
		if (temp->value != NULL)
			dprintf(STDOUT_FILENO, "%s=%s\n", temp->name, temp->value);
		temp = temp->next;
	}
	return (0);
}

int print_echo(t_data *data, char **argv)
{
	int i = 1;
	int new_line = 0;

	while (argv[i])
	{
		if (i == 1 && strcmp(argv[i],"-n") == 0)
			new_line = 1;
		dprintf(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1] != NULL)
			dprintf(STDOUT_FILENO, " ");
		i++;
	}
	if (new_line != 1)
		dprintf(STDOUT_FILENO, "\n");
	return (0);
} 

int unset_builtin(t_data *data, char **str)
{
	int i = 0;
	while (str[++i])
		unset_env_node(data, str[i]);
	
	return (0);
}

int unset_env_node(t_data *data, char *name)
{
	t_env_node *curr;
	t_env_node *prev;

	curr = data->env_head;
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->name, name) == 0)
		{
			remove_env(data, curr, prev);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

void bubble_sort(char **arr)
{
	char *temp;
	int issorted;
	int i = 0;
	
	issorted = 0;
	while (issorted == 0)
	{
		issorted = 1;
		i = 0;
		while (arr[i])
		{
			if (arr[i + 1] && strcmp(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				issorted = 0;
			}
			i++;
		}
	}
	
}

void	sort_n_print(t_data *data)
{
	int len;
	char **sorted;
	t_env_node *temp;

	len = env_length(data->env_head);
	sorted = safe_calloc(data, len + 1, sizeof(char *));
	temp = data->env_head;
	len = 0;
	while (temp)
	{
		sorted[len] = ft_strjoin(temp->name, temp->value);
		len++;
		temp = temp->next;
	}
	bubble_sort(sorted);
	len = 0;
	while (sorted[len])
	{
		printf("declare -x %s\n", sorted[len]);
		len++;
	}
	free_arr(&sorted);
}

int export_builtin(t_data *data, char **str)
{
	int i = 1;
	int j;
	char **split;

	if (str[1] == NULL)
		sort_n_print(data);
	else
	{
		while (str[i])
		{
			j = 0;
			if (!ft_isalnum(str[i][j]) && str[i][j] == '_')
			{
				printf("invalid idenitifier\n");
				i++;
				continue ;
			}
			while (ft_isalnum(str[i][j]) || str[i][j] == '_')
				j++;
			if (str[i][j] == 0)
			{
				set_env_node(&data->env_head, str[i], NULL);
			}
			else if (str[i][j] == '=')
			{
				split = ft_split(str[i], '=');
				if (split[1] == NULL)
					set_env_node(&data->env_head, split[0], "");
				else
					set_env_node(&data->env_head, split[0], split[1]);
				free_arr(&split);
			}
			i++;
		}
	}
	return (0);
}	

int cd_builtin(t_data *data, char **argv)
{
	t_env_node *temp;
	struct stat dir_stat;
		
	if (!argv[1])
	{
		temp = get_env_node(data->env_head, "HOME");
		if (!temp)
			dprintf(STDERR_FILENO, 	"minishell: cd: HOME not set\n");
		else
		{
			chdir(temp->value);
		}
	}
	else if (argv[1])
	{
		if (stat(argv[1], &dir_stat) == -1)
		{
			if (errno == ENOENT)
				dprintf(STDERR_FILENO, "stat: does not exist\n");
			else
				dprintf(STDERR_FILENO, "stat: stat failed\n");
			return (1);
		}
		if (!S_ISDIR(dir_stat.st_mode))
			dprintf(STDERR_FILENO, "stat: is not a directory\n");
		else if ((dir_stat.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR))
			dprintf(STDERR_FILENO, "stat: permission denied\n");
		else
			chdir(argv[1]);
	}
	else if (argv[2])
		dprintf(STDERR_FILENO, "minishell: cd: too many argumantes\n");
	
	free(data->cwd);
	data->cwd = getcwd(NULL, 0);
}    




