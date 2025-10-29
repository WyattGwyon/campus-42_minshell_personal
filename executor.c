/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 19:21:29 by clouden           #+#    #+#             */
/*   Updated: 2025/10/29 20:56:50 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void load_builtin_function(int (*builtin_function[])(t_data *, char **))
{
	builtin_function[PWD] = print_working_dir;
	builtin_function[ECHO] = print_echo;
	builtin_function[CD] = cd_builtin;
	builtin_function[EXPORT] = export_builtin;
	builtin_function[UNSET] = unset_builtin;
	builtin_function[EXIT_BUILTIN] = exit_builtin;
	builtin_function[ENV] = print_env;
	builtin_function[NULL_CMD] = NULL;
}

void execute_builtin(t_data *data)
{
	int (*builtin_function[8])(t_data *, char **);

	load_builtin_function(builtin_function);
	data->last_exit_code = builtin_function[data->cmd_head->builtin_type](data, data->cmd_head->argv);
}

char *get_cmd_path(t_data *data, char *cmd_name)
{
	int i = 0;
	char *path;
	char *temp;

	if (cmd_name == NULL || *cmd_name == 0)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (cmd_name);
	while (data->exec.path_arr[i])
	{
		temp = ft_strjoin(data->exec.path_arr[i], "/");
		path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

extern char **environ;

void validate_and_execv(t_data *data, t_cmd_node *cmd)
{
	struct stat path_stat;

	if (stat(cmd->cmd_path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			dprintf(STDERR_FILENO, "%s: is a directory\n", cmd->argv[0]);
			clean_and_exit(data, 126);
		}
	}
	if (!execve(cmd->cmd_path, cmd->argv, environ))
	{
		dprintf(STDERR_FILENO, "%s: %s\n", cmd->argv[0], strerror(errno));
		clean_and_exit(data, errno == EACCES ? 126 : 127);
	}

}

void child_cmd_logic(t_data *data, t_cmd_node *cmd)
{	
	if (cmd->builtin_type <= NULL_CMD)
	{
		execute_builtin(data);
		clean_and_exit(data, data->last_exit_code);
	}
	cmd->cmd_path = get_cmd_path(data, cmd->argv[0]);
	if (!cmd->cmd_path)
	{
		dprintf(STDERR_FILENO, "%s: command not found\n", cmd->argv[0]);
		clean_and_exit(data, 127);
	}
	validate_and_execv(data, cmd);
}

pid_t last_cmd_logic(t_data *data, t_cmd_node *cmd, int input_fd)
{
	pid_t pid;
	pid = fork();

	if (pid == 0)
	{
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		child_cmd_logic(data, cmd);
	}
	if (input_fd != STDIN_FILENO)
		close(input_fd);

	return (pid);
}


pid_t pipeline(t_data *data, t_cmd_node *cmd, int input_fd)
{
	int pip[2];
	pid_t pid;
	pid_t last_pid;

	if (!cmd->next)
	{
		return (last_cmd_logic(data, cmd, input_fd));
	}
	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		close(pip[R]);
		if (input_fd != STDIN_FILENO)
		{
			dup2(input_fd, STDIN_FILENO);
			close(input_fd);
		}
		dup2(pip[W], STDOUT_FILENO);
		close(pip[W]);
		child_cmd_logic(data, cmd);
	}
	close(pip[W]);
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	last_pid = pipeline(data, cmd->next, pip[R]);
	waitpid(pid, NULL, 0);
	return (last_pid);
}

void restore_fds(t_exec_data exec)
{
	dup2(exec.orig_stdin, STDIN_FILENO);
	dup2(exec.orig_stdout, STDOUT_FILENO);
	close(exec.orig_stdin);
	close(exec.orig_stdout);
}

void executor(t_data *data)
{
	pid_t last_pid;
	int last_pid_status;

	init_exec(data, &data->exec);
	if (data->cmd_head)
	{
		if (!data->cmd_head->next && data->cmd_head->builtin_type < 7)
		{
			execute_builtin(data);
			return ;
		}
		last_pid = pipeline(data, data->cmd_head, STDIN_FILENO);
		waitpid(last_pid, &last_pid_status, 0);
		data->last_exit_code = WEXITSTATUS(last_pid_status);
		while (wait(NULL) > 0)
			;
	}
	restore_fds(data->exec);
	clean_exec(&data->exec);
}



