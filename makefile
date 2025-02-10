# Makefile

# The name of the final executable
NAME = so_long

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes

# Platform-specific includes and flags
ifeq ($(shell uname), Linux)
    INCLUDES = -I/usr/include -Imlx
else
    INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(shell uname).a
ifeq ($(shell uname), Linux)
    MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
    MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Directories
SRCDIR = src
OBJDIR = obj

# Source and object files
SRC = so_long.c \
	  init_game.c \
	  update_game.c \
	  end_game.c \
	  parse_map.c \
	  validate_map.c \
	  load_map.c \
	  render.c \
	  render_map.c \
	  render_player.c \
	  handle_input.c \
	  key_hooks.c \
	  mouse_hooks.c \
	  errors.c \
	  memory.c \
	  helpers.c 
# Add the source directory prefix to source files
SRCS = $(addprefix $(SRCDIR)/, $(SRC))

# Generate object file names in the object directory
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#  Prevents make from confusing these targets with files of the same name.
.PHONY: all clean fclean re

# Default rule
all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

# Rule to build executable program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME) 

#Link object files to create the executable

# Ensure the object directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule for compiling source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $< $(INCLUDES)

# Build MiniLibX library
$(MLX_LIB):
	make -C $(MLX_DIR)
# Build Libft library
$(LIBFT_LIB):
	make -C $(LIBFT_DIR)
# Clean up object files
clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean
# Full clean (removes executable as well)
fclean: clean
	rm -f $(NAME)
	make -C $(MLX_DIR) fclean
	make -C $(LIBFT_DIR) fclean
# Rule for re-making the project from scratch

re: fclean all

# To prevent unnecessary relinks, we make sure that the `all` target
# does not force a rebuild of the $(NAME) if the object files have not changed.
# This is implicit in the way make works by checking the timestamps of prerequisites.
