/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:47 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:47 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_memory	g_memory;

static bool	is_cmd_spaced(char *cmd)
{
	while (*cmd)
	{
		if (!__isspace(*cmd))
			return (false);
		++cmd;
	}
	return (true);
}

void	main_master_flash(int ac, char **ep)
{
	if (ac)
		throw_("too many arguments", true, 0);
	redirect_signals();
	build_environment(ep);
}

int	main(int ac, char **av, char **ep)
{
	char	*cmd;

	__memset(&g_memory, 0x00, sizeof(t_memory));
	--ac;
	++av;
	main_master_flash(ac, ep);
	while (1)
	{
		g_memory.active = true;
		cmd = readline("minishell-1.0$ ");
		if (!cmd)
		{
			__putstr_fd("exit\n", STDERR_FILENO);
			quit(g_memory.allocated, 0, true);
		}
		if (!*cmd || is_cmd_spaced(cmd))
			continue ;
		add_history(cmd);
		tokenize(cmd);
		if (g_memory.flag)
			continue ;
		g_memory.active = false;
		execflow(g_memory.tokens);
	}
	return (0);
}
