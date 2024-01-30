# Makefile for libft

# Static library name
NAME := libft.a

# Directory paths
SYS_HEADERS_PATH := ../
OBJS_PATH := ./objs/

# Source files
SRCS :=	ft_atoi.c \
		ft_atoll.c \
		ft_itoa.c \
		ft_strlen.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strtok.c \
		ft_split.c

# Object files
OBJS := $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

# Compiler and flags
CC := cc
CFLAGS := -Wall -Werror -Wextra $(if $(FSANITIZE), -fsanitize=$(FSANITIZE))

# Include flags, for the compiler to find additional header files
INCLUDE_SYS_HEADERS := -I$(SYS_HEADERS_PATH)

# Archive command and flags
AR := ar
ARFLAGS := -rcs

# Remove command and flags
RM := rm
RMFLAGS := -rf

# Default target
all: $(NAME)

# Rule to build static library
$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJS)

# Pattern rule to compile .c files into .o files
$(OBJS_PATH)%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE_SYS_HEADERS) -c $< -o $@

# Remove all object files
clean:
	@$(RM) $(RMFLAGS) $(OBJS)

# Remove all generated files
fclean: clean
	@$(RM) $(RMFLAGS) $(NAME)

# Rebuild the static library
re: fclean all

# Phony targets
.PHONY: all clean fclean re