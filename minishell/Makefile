#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC #-fsanitize=address

NAME						= minishell
TEST_LEXER					= test_lexer
TEST_PARSER					= test_parser

VALGRIND					= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS_PATH 					= srcs
SRCS_FILES					= lexer.c lexer_quotes.c parser.c utils.c libft.c main.c
SRCS_FILES_LEXER			= lexer.c lexer_quotes.c utils.c libft.c lexer_test.c
SRCS_FILES_PARSER			= lexer.c lexer_quotes.c parser.c utils.c libft.c parser_test.c

INCLUDES_PATH 				= includes
INCLUDES 					= -I$(INCLUDES_PATH)

SRCS		 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))
SRCS_LEXER		 			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_LEXER))
SRCS_PARSER		 			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES_PARSER))

OBJS						= $(SRCS:.c=.o)
OBJS_LEXER					= $(SRCS_LEXER:.c=.o)
OBJS_PARSER					= $(SRCS_PARSER:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME) 

# Mandatory
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -lreadline -lhistory -o $(NAME)

# Test
test-lexer: $(TEST_LEXER)
$(TEST_LEXER): $(OBJS_LEXER)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_LEXER) -lreadline -lhistory -o $(TEST_LEXER)
# Test
test-parser: $(TEST_PARSER)
$(TEST_PARSER): $(OBJS_PARSER)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS_PARSER) -lreadline -lhistory -o $(TEST_PARSER)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Append debug flags
# run re = rebuild project with debug flags (re must complete before debug succeeds)
debug: $(CFLAGS) += -g3 -fsanitize=address
debug: re

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test-lexer: $(TEST_LEXER)
	$(VALGRIND) ./$(TEST_LEXER)

valgrind-test-lexer: $(TEST_PARSER)
	$(VALGRIND) ./$(TEST_PARSER)

# Clean
clean:
	rm -f $(OBJS) $(OBJS_LEXER) $(OBJS_PARSER)

fclean: clean
	rm -f $(NAME) $(TEST_LEXER) $(TEST_PARSER)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus