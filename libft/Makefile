#############
# Variables #
#############

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -fPIC

NAME			= libft.a

SRCS_PATH 		= srcs
INCLUDES_PATH = includes

SRCS_FILES		= ft_isalpha.c \
					ft_isdigit.c \
					ft_isalnum.c \
					ft_isascii.c \
					ft_isprint.c \
					ft_strlen.c \
					ft_memset.c \
					ft_bzero.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_strlcpy.c \
					ft_strlcat.c \
					ft_toupper.c \
					ft_tolower.c \
					ft_strchr.c \
					ft_strrchr.c \
					ft_strncmp.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_calloc.c \
					ft_strdup.c \
					ft_substr.c \
					ft_strjoin.c \
					ft_strtrim.c \
					ft_split.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putchar_fd.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c

SRCS 			= $(addprefix $(SRCS_PATH)/, $(SRCS_FILES))

OBJS			= $(SRCS:.c=.o)

SRCS_BONUS_FILES= ft_lstnew_bonus.c \
					ft_lstadd_front_bonus.c \
					ft_lstsize_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c \
					ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c

SRCS_BONUS		= $(addprefix $(SRCS_PATH)/, $(SRCS_BONUS_FILES))
OBJS_BONUS		= $(SRCS_BONUS:.c=.o)

#########
# Rules #
#########

# Default rule
all: $(NAME)

# Lib rule
$(NAME): $(OBJS) $(OBJS_BONUS)
	ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

# Compilation rule
$(SRCS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES_PATH)/libft.h
	$(CC) $(CFLAGS) -I$(INCLUDES_PATH) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus