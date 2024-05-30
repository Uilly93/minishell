name = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -lreadline

OBJ = $(SRC:.c=.o)

all: $(name)

$(name): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(name)

re: fclean all

.PHONY: all clean fclean r