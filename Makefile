NAME = minishell
CC = cc

LIBFT = includes/libft/
CFLAGS = -Wall -Wextra -Werror -g3 -Iincludes -Isrc -MMD

SRCS = src/main.c \
	src/exec/child.c src/exec/heredoc.c src/exec/signal.c \
	src/exec/env_create.c src/exec/env_manage.c \
	src/exec/exec.c src/exec/exec_utils.c src/exec/init_prompt.c \
	src/exec/minishell_utils.c src/exec/minishell_loop.c \
	src/parsing/get_msh.c src/parsing/parsing_utils.c \
	src/parsing/fill_token.c src/parsing/token_utils.c \
	src/parsing/fill_msh.c src/parsing/msh_utils.c \
	src/builtins/echo.c src/builtins/cd.c src/builtins/pwd.c \
	src/builtins/exit.c src/builtins/export.c src/builtins/export_print.c \
	src/builtins/env.c src/builtins/unset.c src/builtins/export_utils.c

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -lreadline

-include $(DEPS)

$(LIBFT)libft.a:
	make -C $(LIBFT)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT) clean
	rm -f $(OBJS) $(DEPS)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
