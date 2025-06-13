# The name of your final program
NAME = push_swap

# The compiler to use (gcc is standard)
CC = cc -g

# Compiler flags:
CPPFLAGS = -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft
CFLAGS = -Wall -Wextra -Werror $(CPPFLAGS)

# List of all your .c source files
# We're organizing them into subdirectories for cleanliness
INC_DIR := inc/

LIBFT_DIR := inc/libft/
LIBFT_A := $(LIBFT_DIR)libft.a

SRCS_DIR := src/
SRCS += main.c
SRCS += parsing.c
SRCS += error_handling.c
SRCS += operations_push.c
SRCS += operations_swap.c
SRCS += operations_rotate.c
SRCS += operations_rev_rotate.c
SRCS += validation.c
SRCS += preprocessing.c
SRCS += stack_init.c
SRCS += stack_utils.c
SRCS += sorting_logic.c
SRCS += sorting_helpers.c
SRCS += sorting_helpers_utils.c

# Automatically generate the object file names (.o) from the source file names
OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))

# --- Rules ---

# The default rule: 'make' or 'make all' will build the program
all: $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

# Rule to link all the object files into the final executable
$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $(NAME) $(LIBFT_A)
	@echo "Push_swap compiled successfully!"

# Rule to compile a .c file into a .o file
$(OBJ_DIR)%.o: $(SRCS_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@


# Rule to remove all temporary object files
clean:
	rm -f $(OBJS)
	rm -fr $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean
	@echo "Object files cleaned."

# Rule to remove object files AND the final executable
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	@echo "Full clean complete."

# Rule to re-compile the whole project from scratch
re: fclean all

# Phony rules are targets that are not actual files
.PHONY: all clean fclean re