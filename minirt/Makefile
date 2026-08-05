# ******************************************************************** #
#   Makefile                                                           #
#   Builds $(NAME) from src/, plus a standalone `test` target that     #
#   links only the parsing sources against a small local test harness  #
#   (tests/test_parsing.c) so parsing can be exercised without MLX.    #
# ******************************************************************** #

NAME		= miniRT
TEST_NAME	= test_parsing

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

VALGRIND	= valgrind --track-fds=yes --leak-check=full \
						--track-origins=yes --show-leak-kinds=all #-q

FSANITIZE	= -fsanitize=address	

MLX_PATH					= minilibx-linux
MLX_FLAGS					= -Lminilibx-linux -l:libmlx.a -lX11 -lXext -lm #math
MLX 						= $(MLX_PATH)/libmlx.a

INCLUDES	= -I includes -I libft -I$(MLX_PATH)

OBJ_DIR		= obj

SRCS		= $(shell find src -name "*.c") main.c
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

HEADERS		= $(shell find includes -name "*.h")

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) -lm

# mlx
$(MLX): $(MLX_PATH)/mlx.h $(FT_PRINTF) $(LIBFT)
	$(MAKE) -C $(MLX_PATH)

fsanitize: $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FSANITIZE) -o $(NAME) -lm

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME)

valgrind-test: $(NAME)
	$(VALGRIND) ./$(NAME) scenes/example.rt

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus: all

clean:
	$(MAKE) -C $(MLX_PATH) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re test
