/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:30 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:32 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	create_commands_part_2(t_token *copy, t_token *head, int i)
{
	copy->next = NULL;
	copy->type = head->type;
	copy->value = head->value;
	add_next((void **)&g_memory.commands[i].tokens, copy);
	g_memory.commands[i].io[STDIN_FILENO] = STDIN_FILENO;
	g_memory.commands[i].io[STDOUT_FILENO] = STDOUT_FILENO;
	g_memory.commands[i].runnable = true;
	g_memory.commands[i].pid = -5;
}

void	third_while(t_command *cmds, int nc)
{
	int	i;

	i = -1;
	while (++i < nc)
	{
		if (cmds + i && cmds[i].av && cmds[i].av[0])
		{
			if (nc == 1 && !__strcmp(cmds[i].av[0], "exit") \
			&& (!(cmds[i].ac > 2) || g_memory.status == 2))
				quit(g_memory.allocated, g_memory.status, true);
		}
	}
}

void	second_while(t_command *cmds, int nc)
{
	int	i;

	i = -1;
	while (++i < nc)
	{
		if (waitpid(cmds[i].pid, &g_memory.status, 0) != -1)
		{
			if (WIFEXITED(g_memory.status))
				g_memory.status = WEXITSTATUS(g_memory.status);
			else if (WIFSIGNALED(g_memory.status))
				g_memory.status = WTERMSIG(g_memory.status) + 128;
		}
		if (g_memory.status == 139)
			__putstr_fd("Segmentation fault\n", STDERR_FILENO);
		if (g_memory.status == 131)
			__putstr_fd("^\\Quit (core dumped)\n", STDERR_FILENO);
		if (cmds[i].io[STDIN_FILENO] > 2)
			close(cmds[i].io[STDIN_FILENO]);
		if (cmds[i].io[STDOUT_FILENO] > 2)
			close(cmds[i].io[STDOUT_FILENO]);
	}
}

void	cmp_dot(t_command *cmd)
{
	__putstr_fd("minishell: ", STDERR_FILENO);
	__putstr_fd(cmd->av[0], STDERR_FILENO);
	__putstr_fd(": command not found\n", STDERR_FILENO);
}

int	check_first(t_command *cmd, int nc)
{
	g_memory.status = 0;
	if (!__strcmp(cmd->av[0], "export") && cmd->ac != 1)
	{
		exec_export(cmd->ac, cmd->av);
		return (1);
	}
	else if (!__strcmp(cmd->av[0], "unset"))
	{
		exec_unset(cmd);
		return (1);
	}
	else if (!__strcmp(cmd->av[0], "cd"))
	{
		builtin_cd(cmd->ac, cmd->av, nc);
		return (1);
	}
	else if (!__strcmp(cmd->av[0], ".") || !__strcmp(cmd->av[0], ".."))
	{
		cmp_dot(cmd);
		return (1);
	}
	return (0);
}
