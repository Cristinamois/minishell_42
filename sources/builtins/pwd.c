/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:16 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:17 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	exec_pwd(void)
{
	if (g_memory.cwd)
		free(g_memory.cwd);
	g_memory.cwd = getcwd(NULL, 0);
	if (!g_memory.cwd)
		throw_("unable to getcwd", true, 0);
	printf("%s\n", g_memory.cwd);
	return (true);
}
