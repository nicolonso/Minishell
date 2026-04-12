NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include
RM      = rm -rf
LIBS    = -lreadline

# Directories
SRC_DIR = src/
OBJ_DIR = obj/

# Sources — add new files here as you create them
SRCS    = main.c \
          parse/prompt_loop.c \
          parse/parse.c \
          execute/executor.c \
          execute/path.c \
          execute/env_utils.c \
          execute/builtins/cd.c \
          execute/builtins/pwd.c \
          execute/builtins/echo.c \
          execute/builtins/env.c \
          execute/builtins/export.c \
          execute/builtins/unset.c \
          execute/builtins/exit.c \
          utils/str.c \
          utils/mem.c \
		  utils/ft_strdup.c \
          utils/ft_split.c \
          utils/ft_strjoin.c \
          utils/ft_calloc.c \
          utils/error.c

SRCS    := $(addprefix $(SRC_DIR), $(SRCS))
OBJS    = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "minishell compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re