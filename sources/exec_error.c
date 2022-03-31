/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:59:20 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:59:26 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	print_execve_errors(char *path, char *type)
{
	__putstr_fd("minishell: ", 2);
	__putstr_fd(path, 2);
	__putstr_fd(": ", 2);
	__putstr_fd(type, 2);
	__putstr_fd("\n", 2);
}

void	execve_errors(char	*path, struct stat *sb)
{
	if (stat(path, sb) != -1 && S_ISDIR(sb->st_mode))
	{
		print_execve_errors(path, "Is a directory");
		quit(g_memory.allocated, 126, true);
	}
	else if (stat(path, sb) != -1 && S_ISREG(sb->st_mode))
	{
		print_execve_errors(path, strerror(errno));
		if (errno == ENOENT)
			quit(g_memory.allocated, 127, true);
		quit(g_memory.allocated, 126, true);
	}
	if (__strchr(path, '/'))
		print_execve_errors(path, "No such file or directory");
	else if (*path)
		print_execve_errors(path, "command not found");
	quit(g_memory.allocated, 127, true);
}
