/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:01 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:03 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	export_error(char *error)
{
	__putstr_fd("minishell: export: `", STDERR_FILENO);
	__putstr_fd(error, STDERR_FILENO);
	__putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	exit_error(char *av1)
{
	__putstr_fd("minishell: exit: ", STDERR_FILENO);
	__putstr_fd(av1, STDERR_FILENO);
	__putstr_fd(": numeric argument required\n", STDERR_FILENO);
	quit(g_memory.allocated, 2, true);
}

void	exec_exit(t_command *cmd, int nc)
{
	char	*av1;
	int		i;

	if (nc != 1)
		return ;
	__putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->ac > 1)
	{
		av1 = cmd->av[1];
		i = -1;
		while (av1[++i])
			if (!__isdigit(av1[i]))
				exit_error(av1);
		if (cmd->ac > 2)
		{
			__putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			quit(g_memory.allocated, 1, true);
		}
		else
			quit(g_memory.allocated, __atoi(av1), true);
	}
	else
		quit(g_memory.allocated, 0, true);
}
