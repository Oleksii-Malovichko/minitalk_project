NAME1 = libftprintf.a
NAME2 = client
NAME3 = server

CC = cc 
C_FLAGS = -Wall -Wextra -Werror

SRCS1 = ft_printf/funcs.c ft_printf/funcs2.c ft_printf/ft_printf.c ft_printf/process_string.c ft_printf/process_string2.c
SRCS2 = client.c client_utils.c 
SRCS3 = server.c server_utils.c

OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
OBJS3 = $(SRCS3:.c=.o)


all: $(NAME1) $(NAME2) $(NAME3)

$(NAME1): $(OBJS1)
	ar rcs $@ $^

$(NAME2): $(OBJS2) $(NAME1)
	$(CC) $(C_FLAGS) -o $(NAME2) $(OBJS2) -L. -lftprintf

$(NAME3): $(OBJS3) $(NAME1)
	$(CC) $(C_FLAGS) -o $(NAME3) $(OBJS3) -L. -lftprintf

%.o: %.c
	$(CC) $(C_FLAGS) -Ift_printf -c $< -o $@

clean:
	rm -f $(OBJS1) $(OBJS2) $(OBJS3) 

fclean: clean
	rm -f $(NAME1) $(NAME2) $(NAME3)

re: fclean all

.PHONY: all clean fclean re