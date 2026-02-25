#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC -g3 #-fsanitize=address

NAME_CLIENT					= client
NAME_SERVER					= server
NAME_CLIENT_BONUS			= client_bonus
NAME_SERVER_BONUS			= server_bonus

LIBFT_PATH					= libft
LIBFT 						= $(LIBFT_PATH)/libft.a

FT_PRINTF_PATH				= ft_printf
FT_PRINTF					= $(FT_PRINTF_PATH)/libftprintf.a

SRCS_PATH 					= srcs
SRCS_FILES_CLIENT			= client.c 
SRCS_FILES_CLIENT_BONUS		= client_bonus.c 

SRCS_FILES_SERVER			= server.c
SRCS_FILES_SERVER_BONUS		= server_bonus.c

INCLUDES_PATH 				= includes
FT_PRINTF_INCLUDES_PATH 	= $(FT_PRINTF_PATH)/includes
LIBFT_INCLUDES_PATH			= libft/includes
INCLUDES 					= -I$(INCLUDES_PATH) -I$(FT_PRINTF_INCLUDES_PATH) -I$(LIBFT_INCLUDES_PATH)

SRCS_CLIENT 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_CLIENT))
SRCS_SERVER					= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_SERVER))
SRCS_CLIENT_BONUS			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_CLIENT_BONUS))
SRCS_SERVER_BONUS			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_SERVER_BONUS))

OBJS_CLIENT					= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER					= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT_BONUS			= $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS			= $(SRCS_SERVER_BONUS:.c=.o)

MANDATORY					= mandatory

#########
# Rules #
#########

# Default rule
all: $(MANDATORY)

# Bonus
bonus: $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_CLIENT_BONUS) $(FT_PRINTF) $(LIBFT) -o $(NAME_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_SERVER_BONUS) $(FT_PRINTF) $(LIBFT) -o $(NAME_SERVER_BONUS)

# Mandatory
$(MANDATORY): $(OBJS_CLIENT) $(OBJS_SERVER) $(FT_PRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_CLIENT) $(FT_PRINTF) $(LIBFT) -o $(NAME_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_SERVER) $(FT_PRINTF) $(LIBFT) -o $(NAME_SERVER)

# ft_printf
$(FT_PRINTF): $(FT_PRINTF_INCLUDES_PATH)/ft_printf.h $(LIBFT)
	$(MAKE) -C $(FT_PRINTF_PATH)

# libft
$(LIBFT): $(LIBFT_INCLUDES_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES_PATH)/minitalk.h $(FT_PRINTF_INCLUDES_PATH)/ft_printf.h $(LIBFT_INCLUDES_PATH)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	rm -f $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)
	$(MAKE) -C $(FT_PRINTF_PATH) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	rm -f $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus