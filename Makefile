# Makefile

# Standard
NAME							= minishell

# Directories

HDR								= hdr/
SRC_DIR							= src/
PARSING_DIR						= parse/
EXECUTE_DIR 					= execute/
UTL_DIR							= utils/
OBJ_DIR							= obj/
LIBS 							= -lreadline -lncurses

# Compiler and CFlags

CC								= cc
CFLAGS							= -Wall -Wextra -I$(HDR) -Iinclude
RM								= rm -f

# Sources Files

MAIN_SRC						= main.c
MAIN_SRC 						:= $(addprefix $(SRC_DIR), $(MAIN_SRC))

UTL_SRC							= str.c mem.c
UTL_SRC 						:= $(addprefix $(SRC_DIR)$(UTL_DIR), $(UTL_SRC))

PARSING_SRC						= parse.c prompt_loop.c
PARSING_SRC 					:= $(addprefix $(SRC_DIR)$(PARSING_DIR), $(PARSING_SRC))

EXECUTE_SRC						= execute.c
EXECUTE_SRC 					:= $(addprefix $(SRC_DIR)$(EXECUTE_DIR), $(EXECUTE_SRC))

# Concatenate all source files

SRCS							= $(MAIN_SRC) $(PARSING_SRC) $(EXECUTE_SRC) $(UTL_SRC)

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

.PHONY:							all clean fclean re
