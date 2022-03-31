/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_toruk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:35 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:58 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	pid_zero_or_neg(t_command *cmd, int nc, int np)
{
	if (cmd->pid == -1)
		throw_("couldn't fork()", true, 0);
	if (cmd->pid == 0)
	{
		if (dup2(cmd->io[STDIN_FILENO], STDIN_FILENO) == -1)
			quit(g_memory.allocated, 1, true);
		if (dup2(cmd->io[STDOUT_FILENO], STDOUT_FILENO) == -1)
			quit(g_memory.allocated, 1, true);
		close_pipes(np);
		relocate(cmd, nc);
	}
}

void	alduin(int nc)
{
	int	i;

	i = -1;
	while (++i < nc)
	{
		if (!create_main_args(&g_memory.commands[i]))
			g_memory.commands[i].runnable = false;
	}
}
