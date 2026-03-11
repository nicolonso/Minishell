# Makefile

# Standard
NAME							= mini_shell

# Directories

HDR								= hdr/
SRC_DIR							= src/
OBJ_DIR							= obj/
LIBS 							= -lreadline -lncurses

# Compiler and CFlags

CC								= cc
CFLAGS							= -Wall -Wextra -Werror -I$(HDR) -Iinclude
RM								= rm -f

# Sources Files

#FUNCTIONS_DIR					= $(SRC_DIR)Functions/function.c

MINI_SHELL_DIR					= $(SRC_DIR)Mini_Shell/mini_shell.c

# Concatenate all source files

SRCS							= $(MINI_SHELL_DIR)

# Apply the pattern substitution to each SRC and produce a corresponding list of object files in the OBJ_DIR

OBJ								= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# Build rules

all:							$(NAME)

$(NAME):						$(OBJ)
								@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

# Compile object files from source files
$(OBJ_DIR)%.o:					$(SRC_DIR)%.c
								@mkdir -p $(@D)
								@$(CC) $(CFLAGS) -c $< -o $@

clean:
								@$(RM) -r $(OBJ_DIR)

fclean:							clean
								@$(RM) $(NAME)

re:								fclean all

# Phony targets represen action not files

.PHONY:							start all clean fclean re