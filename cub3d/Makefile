#############
# Variables #
#############

CC						= cc
CFLAGS					= -Wall -Wextra -Werror

NAME					= cub3d

VALGRIND				= valgrind --track-fds=yes --leak-check=full --suppressions=readline.supp \
						--track-origins=yes --show-leak-kinds=all #-q

FSANITIZE	= -fsanitize=address

SRCS_PATH				= srcs
PARSER_PATH				= parser
LIBFT_PATH				= libft
UTILS_PATH				= utils

SRCS_FILES				= main.c
SRCS_FILES_PARSER		= cmd.c heredoc.c bools.c rules.c rules2.c setters.c
SRCS_FILES_LIBFT		= bools.c str.c str2.c split.c gnl.c
SRCS_FILES_UTILS		= utils.c utils2.c free.c free2.c envp.c env_ops.c signals.c signals2.c

MLX_PATH					= minilibx-linux
MLX_FLAGS					= -Lminilibx-linux -l:libmlx.a -lX11 -lXext -lm #math
MLX 						= $(MLX_PATH)/libmlx.a

INCLUDES_PATH			= includes
INCLUDES				= -I$(INCLUDES_PATH)

SRCS					= $(addprefix $(SRCS_PATH)/$(LEXER_PATH)/, $(SRCS_FILES_LEXER))

OBJS					= $(SRCS:.c=.o)

#########
# Rules #
#########

all: $(NAME)

$(NAME): $(OBJS) $(MLX) srcs/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/main.c $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME) -lm

$(MLX): $(MLX_PATH)/mlx.h $(LIBFT)
	$(MAKE) -C $(MLX_PATH)

test-parser: $(TEST_PARSER)
$(TEST_PARSER): $(OBJS) srcs/parser/parser_test.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) srcs/parser/parser_test.c -o $(TEST_PARSER)

fsanitize: $(LIBFT) $(GNL) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(FSANITIZE) -o $(NAME) -lm

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

debug: CFLAGS += -g3 FSANITIZE
debug: re

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test-parser: $(TEST_PARSER)
	$(VALGRIND) ./$(TEST_PARSER)

clean:
	rm -f $(OBJS) srcs/main.o

fclean: clean
	rm -f $(NAME) $(TEST_PARSER)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus debug valgrind \
	valgrind-test-parser