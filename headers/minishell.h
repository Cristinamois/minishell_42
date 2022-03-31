/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madiallo <madiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:56:33 by madiallo          #+#    #+#             */
/*   Updated: 2022/03/30 14:56:33 by madiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>

typedef enum e_token_type
{
	ETT_SPACE,
	ETT_SQWORD = '\'',
	ETT_DQWORD = '\"',
	ETT_SRINPUT = '<',
	ETT_SROUTPUT = '>',
	ETT_DRINPUT,
	ETT_DROUTPUT,
	ETT_PIPE = '|',
	ETT_WORD,
	ETT_REDIRECT,
	ETT_NONE
}	t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_command
{
	t_token	*tokens;
	int		io[2];
	int		ac;
	char	**av;
	pid_t	pid;
	bool	runnable;
}	t_command;

typedef struct s_variable
{
	struct s_variable	*next;
	char				*key;
	char				*value;
}	t_variable;

typedef struct s_allocation	t_next;

typedef struct s_allocation
{
	struct s_allocation	*next;
	void				*value;
}	t_allocation;

typedef struct s_memory
{
	t_allocation	*allocated;
	t_variable		*environment;
	char			*cwd;
	t_token			*tokens;
	int				flag;
	t_command		*commands;
	int				*pipes;
	int				status;
	bool			active;
}	t_memory;

extern t_memory				g_memory;

void		*__memset(void *__s, int __c, size_t __n);
char		*__strdup(char *__s);
size_t		__strlen(char *__s);
char		*__strndup(char *__string, size_t __n);
char		*__strchr(char *__s, int __c);
void		*__memcpy(void *dest, void *src, size_t len);
size_t		__strnlen(char *s, size_t maxlen);
int			__isspace(int c);
int			__isalnum(int c);
int			__isalpha(int c);
int			__isdigit(int c);
char		*__strstr(char *string, char *substring);
int			__strcmp(char *p1, char *p2);
char		*__strjoin(char *s1, char *s2);
char		*__strrep(char *base, char *oldw, char *neww);
void		__putstr_fd(char *str, int fd);
char		*__itoa(int n);
char		*ft_strcat(char *dst, const char *src);
void		__sortarr(char **arr);
char		**ft_split(char const *s, char c);
void		__putnstr(char *str, size_t n);
int			__atoi(char *str);
void		close_pipes(int np);
void		execflow(t_token *head);
void		pid_zero_or_neg(t_command *cmd, int nc, int np);
bool		create_main_args(t_command *cmd);
void		create_commands(t_token *head, int nc);
void		exec_cmds(t_command *cmds, int nc, int np);
void		create_commands_part_2(t_token *copy, t_token *head, int i);
void		third_while(t_command *cmds, int nc);
void		second_while(t_command *cmds, int nc);
void		cmp_dot(t_command *cmd);
int			check_first(t_command *cmd, int nc);
void		alduin(int nc);
void		notvaliderr(char *arg);
void		overwrite_var(char *key, char *newvalue);
void		exec_exit(t_command *cmd, int nc);
void		exec_unset(t_command *cmd);
bool		is_valid_id(char *id);
void		__export_external(void);
void		exec_export(int ac, char **av);
void		export_error(char *error);
void		*builtin_cd(int ac, char **av, int nc);
void		exec_echo(int argc, char **argv);
bool		exec_env(void);
bool		exec_pwd(void);
void		relocate(t_command *cmd, int nc);
char		**export_env(t_variable *env);
size_t		get_next_size(void *head);
void		redirect_commands(int nc);
void		execflow(t_token *head);
char		*on_dollar(t_token *token, char *dollar);
t_variable	*search_environment(char *key);
void		environment_patch(t_token *head);
void		check_token(t_token *token, int mode, t_token *previous);
void		link_tokens(t_token *head);
int			no_syntax_errors(t_token *head);
void		tokenize(char *cmd);
void		update_token(void);
void		fork_check_syntax_err(t_token *head);
int			__toktype(t_token *token);
bool		__issupported(int c);
char		*on_word(char *word);
void		drinput_error(int line, char *eof);
void		closing_pipes_redirect(char *buffer, t_command *command, int io[2]);
void		redirection_error(char *error);
void		print_execve_errors(char *path, char *type);
void		execve_errors(char *path, struct stat *sb);
char		*on_redirect(char *redirect);
char		*on_qword(char *fquote);
void		add_token(t_token_type type, char *value, size_t vallen);
void		show_environment(t_variable *environment);
void		export_variable(char *key, size_t keylen, char *value);
void		build_environment(char **ep);
void		*get_last_next(void *head);
void		add_next(void **head, void *value);
void		*allocate(size_t size);
void		redirect_signals(void);
void		quit(t_allocation *allocated, int status, bool nexit);
void		throw_(char *errstr, bool prefix, int code);

#endif
