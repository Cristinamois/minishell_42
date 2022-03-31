/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:00:18 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:21 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	handle_drinput(t_command *command, char *eof)
{
	int		io[2];
	char	*input;
	char	*buffer;
	int		line;

	line = 1;
	if (pipe(io) == -1)
		throw_("unable to pipe", true, 0);
	buffer = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			drinput_error(line, eof);
			break ;
		}
		if (!__strcmp(eof, input))
			break ;
		buffer = __strjoin(buffer, input);
		buffer = __strjoin(buffer, "\n");
	}
	closing_pipes_redirect(buffer, command, io);
}

int	flags_master(t_token *redir)
{
	int	flags;

	flags = 0;
	if (redir->type == ETT_SROUTPUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == ETT_DROUTPUT)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	return (flags);
}

static void	handle_redirection(t_command *cmd, t_token *redir)
{
	int	flags;
	int	target;

	if (redir->type == ETT_DRINPUT)
	{
		handle_drinput(cmd, redir->next->value);
		return ;
	}
	target = STDOUT_FILENO;
	if (redir->type == ETT_SROUTPUT || redir->type == ETT_DROUTPUT)
		flags = flags_master(redir);
	else if (redir->type == ETT_SRINPUT)
	{
		target = STDIN_FILENO;
		flags = O_RDONLY;
	}
	if (cmd->io[target] > 2)
		close(cmd->io[target]);
	if (*redir->next->value)
	{
		cmd->io[target] = open(redir->next->value, flags, 0644);
		if (cmd->io[target] < 0)
			redirection_error(redir->next->value);
	}
}

static void	remove_redirections(int nc, int i)
{
	t_token	*previous;
	t_token	*head;

	i = -1;
	while (++i < nc)
	{
		previous = NULL;
		head = g_memory.commands[i].tokens;
		while (head)
		{
			if (__toktype(head) == ETT_REDIRECT)
			{
				if (!previous)
					g_memory.commands[i].tokens = head->next->next;
				else
					previous->next = head->next->next;
				head = head->next->next;
			}
			else
			{
				previous = head;
				head = head->next;
			}
		}
	}
}

void	redirect_commands(int nc)
{
	int		i;
	int		io[2];
	t_token	*head;

	i = -1;
	io[STDIN_FILENO] = 1;
	io[STDOUT_FILENO] = 4;
	while (++i < nc)
	{
		if (i != 0)
			g_memory.commands[i].io[STDIN_FILENO] = io[STDIN_FILENO];
		if ((i + 1) != nc)
			g_memory.commands[i].io[STDOUT_FILENO] = io[STDOUT_FILENO];
		head = g_memory.commands[i].tokens;
		while (head)
		{
			if (__toktype(head) == ETT_REDIRECT && head->type != ETT_PIPE)
				handle_redirection(&g_memory.commands[i], head);
			head = head->next;
		}
		io[STDIN_FILENO] += 2;
		io[STDOUT_FILENO] += 2;
	}
	remove_redirections(nc, i);
}
