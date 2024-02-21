# Makefile for minishell

# Program name
NAME := minishell

# Directory paths
SYS_HEADERS_PATH := ../
LIBFT_PATH := ../libft/
OBJS_PATH := ./objs/

# Source files
SRCS := character_check_1.c \
		character_check_2.c \
		character_check_3.c \
		quote_handling.c \
		custom_strtok.c \
		env_check.c \
		get_next_env.c \
		get_input_line_utils.c \
		get_input_line.c \
		expand_env_utils.c \
		expand_env.c \
		minishell.c

# Object files
OBJS := $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

# Run the make tool in another directory
LIBFT_MAKE := $(MAKE) -C$(LIBFT_PATH)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra $(if $(FSANITIZE), -fsanitize=$(FSANITIZE))

# Include flags, for the compiler to find additional header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)
INCLUDE_LIBFT := -I$(LIBFT_PATH)includes/

# Locate, and Link flags, for the compiler to find and link the static library
LDFLAGS := -L$(LIBFT_PATH)
LDLIBS := -lft -lreadline

# Remove command and flags
RM := rm
RMFLAGS := -rf

# Default target
all: $(NAME)

# Rule to build program
$(NAME): $(OBJS)
	@$(LIBFT_MAKE) re
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

# Pattern rule to compile .c files into .o files
$(OBJS_PATH)%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE_SYS_HEADERS) $(INCLUDE_LIBFT) -c $< -o $@

# Remove all object files
clean:
	@$(LIBFT_MAKE) clean
	@$(RM) $(RMFLAGS) $(OBJS)

# Remove all generated files
fclean: clean
	@$(LIBFT_MAKE) fclean
	@$(RM) $(RMFLAGS) $(NAME)

# Rebuild the program
re: fclean all

# Phony targets
.PHONY: all clean fclean re
