/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:56:55 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:56:58 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	__contains_only_n(char *av)
{
	if (!av)
		return (false);
	if (*av++ != '-')
		return (false);
	while (*av)
		if (*av++ != 'n')
			return (false);
	return (true);
}

void	exec_echo(int ac, char **av)
{
	bool	opt_n;

	opt_n = false;
	(void)ac;
	++av;
	while (*av && __contains_only_n(*av))
	{
		opt_n = true;
		++av;
	}
	while (av && *av)
	{
		if (**av)
		{
			__putstr_fd(*av, STDOUT_FILENO);
			if (*(av + 1))
				__putstr_fd(" ", STDOUT_FILENO);
		}
		++av;
	}
	if (!opt_n)
		__putstr_fd("\n", STDOUT_FILENO);
}
