#############
# Variables #
#############

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fPIC -g3 #-fsanitize=address

NAME		= minitalk

FT_PRINTF_PATH	= ft_printf
FT_PRINTF		= $(FT_PRINTF_PATH)/libftprintf.a

SRCS		= parser.c \
				push_swap.c \
				utils.c \
				list_init.c \
				list_utils.c \
				op_push.c \
				op_swap.c \
				op_rotate.c \
				op_reverse_rotate.c \
				algo_mini.c \
				algo_chunk.c \
				algo_ops.c \
				algo_utils.c 

OBJS		= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME)

# Lib rule : copy libft & ft_printf into lib before archiving it
$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -Iincludes -o $(NAME)

# ft_printf first
$(FT_PRINTF): $(FT_PRINTF_PATH)/ft_printf.h
	$(MAKE) -C $(FT_PRINTF_PATH)

# Clean
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(FT_PRINTF_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus