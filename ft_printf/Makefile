#############
# Variables #
#############

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fPIC

NAME		= libftprintf.a

LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRCS		= ft_printf.c \
				ft_print_utils.c \
				ft_print_unsigned.c \
				ft_print_hex.c \
				ft_print_ptr.c

OBJS		= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME)

# Lib rule : copy libft into lib before archiving it
$(NAME): $(OBJS) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

# libft first
$(LIBFT): $(LIBFT_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

# Compilation rule
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus