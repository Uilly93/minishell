# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 16:51:19 by wnocchi           #+#    #+#              #
#    Updated: 2024/08/15 10:22:27 by wnocchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
SRCS = ft_isalpha.c ft_isprint.c ft_memset.c ft_strlcpy.c ft_realloc.c \
	ft_bzero.c ft_isascii.c ft_memcpy.c ft_strchr.c ft_strlen.c \
	ft_toupper.c ft_tolower.c ft_isalnum.c ft_isdigit.c ft_memmove.c \
	ft_strlcat.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
	ft_strcat.c ft_strcpy.c \
	ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
	ft_putendl_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
	ft_lstiter.c ft_lstmap.c ft_strcmp.c ft_isspace.c ft_strndup.c \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c \
	ft_printf.c ft_is_c.c ft_is_di.c ft_is_p.c ft_is_s.c ft_is_u.c \
	ft_is_xl.c ft_is_xu.c ft_mandatory.c ft_putchar.c ft_putnbr_base.c \
	ft_putnbr_base_long.c ft_putnbr.c ft_putstr.c \
	get_next_line.c get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar r $(NAME) $(OBJS)
	
clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re