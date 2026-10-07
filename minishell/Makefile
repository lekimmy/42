#############
# Variables #
#############

CC						= cc
CFLAGS					= -Wall -Wextra -Werror -fPIC

NAME					= minishell
TEST_LEXER				= test_lexer
TEST_PARSER				= test_parser
TEST_EXPANDER			= test_expander

VALGRIND				= valgrind --track-fds=yes --leak-check=full --suppressions=readline.supp \
						--track-origins=yes --show-leak-kinds=all #-q

SRCS_PATH				= srcs
LEXER_PATH				= lexer
PARSER_PATH				= parser
EXPANDER_PATH			= expander
LIBFT_PATH				= libft
UTILS_PATH				= utils
EXEC_PATH				= exec
BUILTINS_PATH			= builtins
SIGNALS_PATH			= signals

SRCS_FILES				= main.c
SRCS_FILES_LEXER		= lexer.c operators.c words.c segments.c
SRCS_FILES_PARSER		= cmd.c heredoc.c bools.c rules.c rules2.c setters.c
SRCS_FILES_EXPANDER		= expander.c len.c str.c
SRCS_FILES_LIBFT		= bools.c str.c str2.c split.c gnl.c
SRCS_FILES_UTILS		= utils.c utils2.c free.c free2.c envp.c env_ops.c signals.c signals2.c
SRCS_FILES_EXEC			= exec.c exec2.c \
						pipeline.c pipeline2.c \
						redirections.c redirections2.c heredoc.c heredoc2.c heredoc3.c word.c \
						external.c external2.c external3.c external4.c \
						expand_cmds.c field_split.c
SRCS_FILES_BUILTINS		= builtins.c echo.c cd.c cd2.c pwd.c env.c \
						export.c export2.c export3.c unset.c exit.c

INCLUDES_PATH			= includes
INCLUDES				= -I$(INCLUDES_PATH)

SRCS					= $(addprefix $(SRCS_PATH)/$(LEXER_PATH)/, $(SRCS_FILES_LEXER)) \
						$(addprefix $(SRCS_PATH)/$(UTILS_PATH)/, $(SRCS_FILES_UTILS)) \
						$(addprefix $(SRCS_PATH)/$(LIBFT_PATH)/, $(SRCS_FILES_LIBFT)) \
						$(addprefix $(SRCS_PATH)/$(PARSER_PATH)/, $(SRCS_FILES_PARSER)) \
						$(addprefix $(SRCS_PATH)/$(EXPANDER_PATH)/, $(SRCS_FILES_EXPANDER)) \
						$(addprefix $(SRCS_PATH)/$(EXEC_PATH)/, $(SRCS_FILES_EXEC)) \
						$(addprefix $(SRCS_PATH)/$(BUILTINS_PATH)/, $(SRCS_FILES_BUILTINS)) \

OBJS					= $(SRCS:.c=.o)

#########
# Rules #
#########

all: $(NAME)

$(NAME): $(OBJS) srcs/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/main.c -lreadline -lhistory -o $(NAME)

test-lexer: $(TEST_LEXER)
$(TEST_LEXER): $(OBJS) srcs/lexer/lexer_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/lexer/lexer_test.c \
	-lreadline -lhistory -o $(TEST_LEXER)

test-parser: $(TEST_PARSER)
$(TEST_PARSER): $(OBJS) srcs/parser/parser_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/parser/parser_test.c \
	-lreadline -lhistory -o $(TEST_PARSER)

test-expander: $(TEST_EXPANDER)
$(TEST_EXPANDER): $(OBJS) srcs/expander/expander_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/expander/expander_test.c \
	-lreadline -lhistory -o $(TEST_EXPANDER)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += -g3 -fsanitize=address
debug: re

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test-lexer: $(TEST_LEXER)
	$(VALGRIND) ./$(TEST_LEXER)

valgrind-test-parser: $(TEST_PARSER)
	$(VALGRIND) ./$(TEST_PARSER)

valgrind-test-expander: $(TEST_EXPANDER)
	$(VALGRIND) ./$(TEST_EXPANDER)

clean:
	rm -f $(OBJS) srcs/main.o

fclean: clean
	rm -f $(NAME) $(TEST_LEXER) $(TEST_PARSER) $(TEST_EXPANDER)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus debug valgrind \
	valgrind-test-lexer valgrind-test-parser valgrind-test-expander