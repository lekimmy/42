#############
# Variables #
#############

CC							= cc
CFLAGS						= -Wall -Wextra -Werror -fPIC -g3 -fsanitize=address

NAME						= fractol

LIBFT_PATH					= libft
LIBFT 						= $(LIBFT_PATH)/libft.a

FT_PRINTF_PATH				= ft_printf
FT_PRINTF					= $(FT_PRINTF_PATH)/libftprintf.a

MLX_PATH					= minilibx-linux
MLX_FLAGS					= -Lminilibx-linux -l:libmlx.a -lX11 -lXext -lm #math
MLX 						= $(MLX_PATH)/libmlx.a

SRCS_PATH 					= srcs
SRCS_FILES					= main.c hooks.c utils_parser.c utils_img.c utils_fractal.c mandelbrot.c julia.c tricorn.c burning_ship.c

INCLUDES_PATH 				= includes
FT_PRINTF_INCLUDES_PATH 	= $(FT_PRINTF_PATH)/includes
LIBFT_INCLUDES_PATH			= $(LIBFT_PATH)/includes
INCLUDES 					= -I$(INCLUDES_PATH) -I$(FT_PRINTF_INCLUDES_PATH) -I$(LIBFT_INCLUDES_PATH) -I$(MLX_PATH)

SRCS		 				= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS						= $(SRCS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME) 

# Mandatory + bonus
$(NAME): $(OBJS) $(FT_PRINTF) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(FT_PRINTF) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# mlx
$(MLX): $(MLX_PATH)/mlx.h $(FT_PRINTF) $(LIBFT)
	$(MAKE) -C $(MLX_PATH)

# ft_printf
$(FT_PRINTF): $(FT_PRINTF_INCLUDES_PATH)/ft_printf.h $(LIBFT)
	$(MAKE) -C $(FT_PRINTF_PATH)

# libft
$(LIBFT): $(LIBFT_INCLUDES_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

# Pattern rule for .o files
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_PATH) clean
	$(MAKE) -C $(FT_PRINTF_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

re: fclean 
	$(MAKE) all

.PHONY: all clean fclean re bonus