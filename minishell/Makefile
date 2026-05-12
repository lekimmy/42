#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC -fsanitize=address

NAME						= minishell

SRCS_PATH 					= srcs
SRCS_FILES					= lexer.c lexer_quotes.c parser.c utils.c libft.c main.c
# SRCS_FILES					= lexer.c lexer_quotes.c parser.c utils.c libft.c lexer_test.c

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
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -lreadline -lhistory -o $(NAME)

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