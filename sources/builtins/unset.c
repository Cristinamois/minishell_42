/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:57:22 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:57:24 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

bool	is_valid_id(char *id)
{
	char	*save;

	save = id;
	while (*id)
	{
		if (!__isalnum(*id) && *id != '_')
		{
			g_memory.status = 1;
			return (false);
		}
		++id;
	}
	if (!__isalpha(*save) && *save != '_')
	{
		g_memory.status = 1;
		return (false);
	}
	return (true);
}

void	unset_error(char *error)
{
	__putstr_fd("minishell: unset: `", STDERR_FILENO);
	__putstr_fd(error, STDERR_FILENO);
	__putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	unset_master(t_variable **tab)
{
	if (!(tab[0]))
		g_memory.environment = (tab[1])->next;
	else
		(tab[0])->next = (tab[1])->next;
}

void	exec_unset(t_command *cmd)
{
	int			i;
	t_variable	*tab[2];

	i = 0;
	while (++i < cmd->ac)
	{
		if (!is_valid_id(cmd->av[i]))
		{
			unset_error(cmd->av[i]);
			continue ;
		}
		tab[0] = NULL;
		tab[1] = g_memory.environment;
		while (tab[1])
		{
			if (!__strcmp(tab[1]->key, cmd->av[i]))
				unset_master(tab);
			tab[0] = tab[1];
			tab[1] = tab[1]->next;
		}
	}
}
