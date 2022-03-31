/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:40 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:42 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

bool	create_main_args(t_command *cmd)
{
	t_token	*head;
	int		i;

	head = cmd->tokens;
	if (head)
	{
		cmd->ac = (int)get_next_size((void *)head);
		cmd->av = (char **)allocate(sizeof(char *) * (cmd->ac + 1));
		cmd->av[cmd->ac] = NULL;
		i = 0;
		while (head)
		{
			cmd->av[i] = head->value;
			head = head->next;
			++i;
		}
		return (true);
	}
	return (false);
}

void	create_commands(t_token *head, int nc)
{
	int		i;
	t_token	*copy;

	i = 0;
	g_memory.commands = allocate(sizeof(t_command) * nc);
	while (head)
	{
		if (head->type == ETT_PIPE)
		{
			if (pipe(g_memory.pipes + i * 2) == -1)
				throw_("unable to pipe", true, 0);
			++i;
		}
		else
		{
			copy = allocate(sizeof(t_token));
			create_commands_part_2(copy, head, i);
		}
		head = head->next;
	}
}

void	close_pipes(int np)
{
	int	i;

	i = -1;
	while (++i < np)
	{
		close(((int *)(g_memory.pipes + i * 2))[STDIN_FILENO]);
		close(((int *)(g_memory.pipes + i * 2))[STDOUT_FILENO]);
	}
}

void	exec_cmds(t_command *cmds, int nc, int np)
{
	int			i;
	t_command	*cmd;

	i = -1;
	while (++i < nc)
	{
		cmd = &cmds[i];
		if (cmd->runnable == false)
			continue ;
		if (check_first(cmd, nc))
			continue ;
		cmd->pid = fork();
		pid_zero_or_neg(cmd, nc, np);
	}
	close_pipes(np);
	second_while(cmds, nc);
	third_while(cmds, nc);
}

void	execflow(t_token *head)
{
	int	np;
	int	nc;

	g_memory.commands = NULL;
	g_memory.pipes = NULL;
	np = 0;
	while (head)
	{
		if (head->type == ETT_PIPE)
			++np;
		head = head->next;
	}
	nc = np + 1;
	if (nc >= 3333)
	{
		__putstr_fd("minishell: syntax error near unexpected token `|'\n",
			STDERR_FILENO);
		return ;
	}
	g_memory.pipes = allocate(sizeof(int) * (np * 2));
	create_commands(g_memory.tokens, nc);
	redirect_commands(nc);
	alduin(nc);
	exec_cmds(g_memory.commands, nc, np);
}
