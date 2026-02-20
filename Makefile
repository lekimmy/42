#############
# Variables #
#############

CC						= cc
CFLAGS					= -Wall -Wextra -Werror -fPIC -g3 #-fsanitize=address

NAME					= minitalk

LIBFT_PATH				= libft
LIBFT 					= $(LIBFT_PATH)/libft.a

FT_PRINTF_PATH			= ft_printf
FT_PRINTF				= $(FT_PRINTF_PATH)/libftprintf.a

SRCS_PATH 				= srcs
SRCS_FILES				= minitalk.c

INCLUDES_PATH 			= includes
FT_PRINTF_INCLUDES_PATH = $(FT_PRINTF_PATH)/includes
LIBFT_INCLUDES_PATH		= libft/includes
INCLUDES 				= -I$(INCLUDES_PATH) -I$(FT_PRINTF_INCLUDES_PATH) -I$(LIBFT_INCLUDES_PATH)

SRCS 					= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))
OBJS					= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(FT_PRINTF) $(LIBFT) -o $(NAME)

$(FT_PRINTF): $(FT_PRINTF_INCLUDES_PATH)/ft_printf.h $(LIBFT)
	$(MAKE) -C $(FT_PRINTF_PATH)

$(LIBFT): $(LIBFT_INCLUDES_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES_PATH)/minitalk.h $(FT_PRINTF_INCLUDES_PATH)/ft_printf.h $(LIBFT_INCLUDES_PATH)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

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