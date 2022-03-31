/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:00:24 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:27 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static bool	__fexist(char *file, char *dir)
{
	DIR				*pdir;
	struct dirent	*ent;

	pdir = opendir(dir);
	if (!pdir)
		return (false);
	while (1)
	{
		ent = readdir(pdir);
		if (!ent)
			break ;
		if (!__strcmp(file, ent->d_name))
		{
			closedir(pdir);
			return (true);
		}
	}
	closedir(pdir);
	return (false);
}

static char	*get_path(char *av0)
{
	char		**paths;
	t_variable	*var;
	int			i;
	char		*ret;

	var = search_environment("PATH");
	if (!var)
		return (av0);
	paths = ft_split(var->value, ':');
	i = -1;
	while (paths[++i])
	{
		if (__fexist(av0, paths[i]))
		{
			ret = __strjoin(paths[i], "/");
			ret = __strjoin(ret, av0);
			return (ret);
		}
	}
	return (av0);
}

static bool	scan_for_builtins(t_command *cmd, int nc)
{
	char	*av0;

	av0 = cmd->av[0];
	if (!__strcmp(av0, "pwd"))
		return (exec_pwd());
	else if (!__strcmp(av0, "env"))
		return (exec_env());
	else if (!__strcmp(av0, "echo"))
	{
		exec_echo(cmd->ac, cmd->av);
		return (true);
	}
	else if (!__strcmp(av0, "export"))
	{
		__export_external();
		return (true);
	}
	else if (!__strcmp(av0, "exit"))
	{
		exec_exit(cmd, nc);
		return (true);
	}
	return (false);
}

void	relocate(t_command *cmd, int nc)
{
	char		*path;
	char		**ep;
	struct stat	sb;

	if (scan_for_builtins(cmd, nc))
		quit(g_memory.allocated, g_memory.status, true);
	path = get_path(cmd->av[0]);
	ep = export_env(g_memory.environment);
	if (execve(path, cmd->av, ep) == -1)
	{
		if (path == cmd->av[0])
			execve_errors(path, &sb);
		else
		{
			print_execve_errors(cmd->av[0], strerror(errno));
			quit(g_memory.allocated, errno, true);
		}
	}
}
