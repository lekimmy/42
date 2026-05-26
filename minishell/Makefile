#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC #-fsanitize=address

NAME						= minishell
TEST_LEXER					= test_lexer
TEST_PARSER					= test_parser
TEST_EXPANDER				= test_expander

VALGRIND					= valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS_PATH 					= srcs
LEXER_PATH					= lexer
PARSER_PATH					= parser
EXPANDER_PATH				= expander
LIBFT_PATH					= libft
UTILS_PATH					= utils

SRCS_FILES					= main.c
SRCS_FILES_LEXER			= lexer.c operators.c words.c segments.c
SRCS_FILES_PARSER			= parser.c bools.c
SRCS_FILES_EXPANDER			= expander.c
SRCS_FILES_LIBFT			= bools.c str.c
SRCS_FILES_UTILS			= utils.c

INCLUDES_PATH 				= includes
INCLUDES 					= -I$(INCLUDES_PATH)

SRCS		 				= $(addprefix $(SRCS_PATH)/$(LEXER_PATH)/, $(SRCS_FILES_LEXER)) \
							$(addprefix $(SRCS_PATH)/$(UTILS_PATH)/, $(SRCS_FILES_UTILS)) \
							$(addprefix $(SRCS_PATH)/$(LIBFT_PATH)/, $(SRCS_FILES_LIBFT)) \
							$(addprefix $(SRCS_PATH)/$(PARSER_PATH)/, $(SRCS_FILES_PARSER)) \
							$(addprefix $(SRCS_PATH)/$(EXPANDER_PATH)/, $(SRCS_FILES_EXPANDER))

OBJS						= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME) 

# Mandatory
$(NAME): $(OBJS) srcs/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/main.c -lreadline -lhistory -o $(NAME)

# Test lexer
test-lexer: $(TEST_LEXER)
$(TEST_LEXER): $(OBJS) srcs/lexer/lexer_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/lexer/lexer_test.c -lreadline -lhistory -o $(TEST_LEXER)

# Test parser
test-parser: $(TEST_PARSER)
$(TEST_PARSER): $(OBJS) srcs/parser/parser_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/parser/parser_test.c -lreadline -lhistory -o $(TEST_PARSER)

# Test parser
test-expander: $(TEST_EXPANDER)
$(TEST_EXPANDER): $(OBJS) srcs/expander/expander_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/expander/expander_test.c -lreadline -lhistory -o $(TEST_EXPANDER)

# Pattern rule for .o files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Append debug flags
# run re = rebuild project with debug flags (re must complete before debug succeeds)
debug: $(CFLAGS) += -g3 -fsanitize=address
debug: re

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test-lexer: $(TEST_LEXER)
	$(VALGRIND) ./$(TEST_LEXER)

valgrind-test-parser: $(TEST_PARSER)
	$(VALGRIND) ./$(TEST_PARSER)

valgrind-test-expander: $(TEST_EXPANDER)
	$(VALGRIND) ./$(TEST_EXPANDER)
# Clean
clean:
	rm -f $(OBJS) srcs/main.o

fclean: clean
	rm -f $(NAME) $(TEST_LEXER) $(TEST_PARSER)

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus