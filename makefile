# Makefile

# The name of the final executable
NAME = so_long

# Compiler and flags
CC = cc
CFLAGS   = -Wall -Wextra -Werror -I/usr/local/include -Iincludes  -Ilibft/includes
MLX_FLAGS= -L/usr/local/lib -lmlx -lXext -lX11

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Directories
SRCDIR = src
OBJDIR = obj

# Source and object files
SRC = so_long.c \
	  end_game.c \
	  file_io.c \
	  handle_input.c \
	  init_game.c \
	  key_hooks.c \
	  parse_map.c \
	  render_map.c\
	  valid_path.c \
# Add the source directory prefix to source files
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Generate object file names in the object directory
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#  Prevents make from confusing these targets with files of the same name.
.PHONY: all clean fclean re

# Default rule
all: $(LIBFT_LIB) $(NAME)

# Rule to build executable program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -o $(NAME)

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build Libft library
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Clean up object files
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
# Full clean (removes executable as well)
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
# Rule for re-making the project from scratch

re: fclean all

# To prevent unnecessary relinks, we make sure that the `all` target
# does not force a rebuild of the $(NAME) if the object files have not changed.
# This is implicit in the way make works by checking the timestamps of prerequisites.
