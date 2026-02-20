#############
# Variables #
#############

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -fPIC

NAME				= libftprintf.a

LIBFT_PATH			= ../libft
LIBFT				= $(LIBFT_PATH)/libft.a

SRCS_PATH 			= srcs
INCLUDES_PATH 		= includes
LIBFT_INCLUDES_PATH = $(LIBFT_PATH)/includes

INCLUDES 			= -I$(INCLUDES_PATH) -I$(LIBFT_INCLUDES_PATH)

SRCS_FILES			= ft_printf.c \
						ft_print_utils.c \
						ft_print_unsigned.c \
						ft_print_hex.c \
						ft_print_ptr.c

SRCS 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))
OBJS				= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME)

# Make Make depend on libft
$(NAME): $(OBJS) $(LIBFT)
# cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

# Define how to build libft
$(LIBFT): $(LIBFT_INCLUDES_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

# Compilation rule
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES_PATH)/ft_printf.h $(LIBFT_INCLUDES_PATH)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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