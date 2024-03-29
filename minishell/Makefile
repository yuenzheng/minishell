# Makefile for minishell

# Program name
NAME := minishell

# Directory paths
SYS_HEADERS_PATH := ../
LIBFT_PATH := ../libft/
OBJS_PATH := ./objs/
BUILTINS_PATH := ./builtins/

# Source files
SRCS := character_check_1.c \
		character_check_2.c \
		character_check_3.c \
		character_check_4.c \
		character_check_5.c \
		character_check_6.c \
		operator_check.c \
		double_array_utils.c \
		clone_envp_with_special.c \
		quote_handling.c \
		get_next_token_utils.c \
		get_next_token.c \
		get_next_subtoken_utils.c \
		get_next_subtoken.c \
		custom_strtok.c \
		env_check.c \
		get_next_env.c \
		string_utils.c \
		read_inputline_utils_1.c \
		read_inputline_utils_2.c \
		read_inputline_utils_3.c \
		read_inputline_helper.c \
		read_inputline.c \
		expand_env_utils_1.c \
		expand_env_utils_2.c \
		expand_env.c \
		get_next_line_utils.c \
		get_next_line.c \
		expand_tilde_utils_1.c \
		expand_tilde_utils_2.c \
		expand_tilde_helper.c \
		expand_tilde.c \
		expand_escaped_utils.c \
		expand_escaped.c \
		subtoken_list_utils_1.c \
		subtoken_list_utils_2.c \
		token_list_utils.c \
		get_token_list_utils.c \
		get_token_list.c \
		build_tree_utils_1.c \
		build_tree_utils_2.c \
		build_tree.c \
		evaluate_tree.c \
		free_list.c \
		minishell.c

BUILTINS_SRCS := blt_echo_utils.c \
				 blt_echo.c \
				 blt_cd_utils_1.c \
				 blt_cd_utils_2.c \
				 blt_cd.c \
				 blt_pwd.c \
				 blt_export_utils_1.c \
				 blt_export_utils_2.c \
				 blt_export_utils_3.c \
				 blt_export_utils_4.c \
				 blt_export.c \
				 blt_unset.c \
				 blt_env.c \
				 blt_exit_utils.c \
				 blt_exit.c

# Object files
SRCS_OBJS := $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
BUILTINS_OBJS := $(addprefix $(OBJS_PATH), $(BUILTINS_SRCS:.c=.o))
OBJS := $(SRCS_OBJS) $(BUILTINS_OBJS)

# Run the make tool in another directory
LIBFT_MAKE := $(MAKE) -C$(LIBFT_PATH)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra $(if $(FSANITIZE), -fsanitize=$(FSANITIZE)) -w

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

$(OBJS_PATH)%.o: $(BUILTINS_PATH)%.c
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
