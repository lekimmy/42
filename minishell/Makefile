#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC #-fsanitize=address #-g3 

NAME						= minishell

SRCS_PATH 					= srcs
SRCS_FILES					= main.c

INCLUDES_PATH 				= includes
INCLUDES 					= -I$(INCLUDES_PATH)

SRCS		 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS						= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME) 

# Mandatory
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

# Clean
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus