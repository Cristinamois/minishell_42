/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:00:13 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 15:00:15 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	drinput_error(int line, char *eof)
{
	__putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	__putstr_fd(__itoa(line), STDERR_FILENO);
	__putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	__putstr_fd(eof, STDERR_FILENO);
	__putstr_fd("`)\n", STDERR_FILENO);
}

void	closing_pipes_redirect(char *buffer, t_command *command, int io[2])
{
	__putstr_fd(buffer, io[STDOUT_FILENO]);
	close(io[STDOUT_FILENO]);
	if (command->io[STDIN_FILENO] > 2)
		close(command->io[STDIN_FILENO]);
	command->io[STDIN_FILENO] = io[STDIN_FILENO];
}

void	redirection_error(char *error)
{
	__putstr_fd("minishell: ", STDERR_FILENO);
	__putstr_fd(error, STDERR_FILENO);
	__putstr_fd(": ", STDERR_FILENO);
	__putstr_fd(strerror(errno), STDERR_FILENO);
	__putstr_fd("\n", STDERR_FILENO);
}
