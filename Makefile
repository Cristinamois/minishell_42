NAME	:= minishell

FILES	:= execution.c main.c program.c redirections.c relocations.c tokenizer.c tokenizer_update.c exec_toruk.c exec_master.c redirections_utils.c exec_error.c
BUILT	:= cd.c echo.c exit.c export.c pwd.c unset.c
LIBC	:= ctype/is_something.c ctype/itoa.c string/memcpy.c string/strchr.c string/strcmp.c string/strcpy.c string/strlen.c string/strsplit.c
TDEFS	:= allocation.c next.c token.c variable.c token_error.c
SOURCES	:= $(addprefix sources/,$(FILES)) $(addprefix sources/builtins/,$(BUILT)) $(addprefix sources/libc/,$(LIBC)) $(addprefix sources/typedefs/,$(TDEFS))
OBJECTS	:= $(SOURCES:.c=.o)
DEPS	:= $(SOURCES:.c=.d)

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
DFLAGS	= -MMD -MF $(@:.o=.d)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(DFLAGS)

-include $(DEPS)
$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline

clean:
	$(RM) $(OBJECTS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
