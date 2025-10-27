/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:42:59 by clouden           #+#    #+#             */
/*   Updated: 2025/10/27 20:32:52 by clouden          ###   ########.fr       */
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


int echo(t_data *data, char *str)
{
	return (0);	
} 



