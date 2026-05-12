#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC #-fsanitize=address

NAME						= minishell
TEST_NAME					= lexer_test

VALGRIND					= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS_PATH 					= srcs
SRCS_FILES					= lexer.c lexer_quotes.c parser.c utils.c libft.c main.c
SRCS_FILES_TEST				= lexer.c lexer_quotes.c parser.c parser_test.c utils.c libft.c lexer_test.c

INCLUDES_PATH 				= includes
INCLUDES 					= -I$(INCLUDES_PATH)

SRCS		 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))
SRCS_TEST		 			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_TEST))

OBJS						= $(SRCS:.c=.o)
OBJS_TEST					= $(SRCS_TEST:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME) 

# Mandatory
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -lreadline -lhistory -o $(NAME)

# Test
test: $(TEST_NAME)
$(TEST_NAME): $(OBJS_TEST)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_TEST) -lreadline -lhistory -o $(TEST_NAME)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Append debug flags
# run re = rebuild project with debug flags (re must complete before debug succeeds)
debug: $(CFLAGS) += -g3 -fsanitize=address
debug: re

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test: $(TEST_NAME)
	$(VALGRIND) ./$(TEST_NAME)

# Clean
clean:
	rm -f $(OBJS) $(OBJS_TEST)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus