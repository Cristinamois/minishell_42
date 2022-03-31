/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:56:49 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:56:49 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	*__cderr(char *dir, char *err)
{
	g_memory.status = 1;
	__putstr_fd("minishell: cd: ", STDOUT_FILENO);
	if (dir)
	{
		__putstr_fd(dir, STDOUT_FILENO);
		__putstr_fd(": ", STDOUT_FILENO);
	}
	__putstr_fd(err, STDOUT_FILENO);
	__putstr_fd("\n", STDOUT_FILENO);
	return (NULL);
}

void	free_cwd(void)
{
	if (g_memory.cwd)
		free(g_memory.cwd);
}

static void	__changedir(char *dir)
{
	t_variable	*var;
	char		*save;

	if (!*dir)
		return ;
	if (chdir(dir) == -1)
	{
		__cderr(dir, strerror(errno));
		return ;
	}
	save = __strdup(g_memory.cwd);
	free_cwd();
	g_memory.cwd = getcwd(NULL, 0);
	if (!g_memory.cwd)
		throw_("unable to getcwd", true, 0);
	var = search_environment("PWD");
	if (!var)
		export_variable("PWD", 3, g_memory.cwd);
	else
		overwrite_var("PWD", g_memory.cwd);
	var = search_environment("OLDPWD");
	if (!var)
		export_variable("OLDPWD", 6, save);
	else
		overwrite_var("OLDPWD", save);
}

void	*builtin_cd(int ac, char **av, int nc)
{
	t_variable	*variable;

	--ac;
	++av;
	if (!ac && nc != 1)
		return (NULL);
	if (ac > 1)
		return (__cderr(NULL, "too many arguments"));
	else if (!ac)
	{
		variable = search_environment("HOME");
		if (!variable)
			return (__cderr(NULL, "HOME not set"));
		__changedir(variable->value);
	}
	else if (!__strcmp(av[0], "-"))
	{
		variable = search_environment("OLDPWD");
		if (!variable)
			return (__cderr(NULL, "OLDPWD not set"));
		__changedir(variable->value);
	}
	else
		__changedir(av[0]);
	return (NULL);
}
