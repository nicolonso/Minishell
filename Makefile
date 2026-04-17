NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include
RM      = rm -rf
LIBS    = -lreadline 

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT	= ./Lib/libft.a

# Sources 
SRCS    = main.c \
          parse/prompt_loop.c \
          parse/parse.c \
          parse/parse_errors.c \
          parse/parse_build.c \
          parse/signals.c \
          parse/tokenize.c \
          parse/token_syntax.c \
          parse/expand.c \
          parse/remove_quotes.c \
          execute/executor.c \
          execute/pipeline.c \
          execute/redir.c \
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
		  utils/ft_isalpha.c \
          utils/ft_isalnum.c \
          utils/ft_isdigit.c \
          utils/ft_itoa.c \
          utils/ft_substr.c \
          utils/ft_memmove.c \
          utils/error.c

SRCS    := $(addprefix $(SRC_DIR), $(SRCS))
OBJS    = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Rules
all: $(NAME)

$(LIBFT):
					@make -C ./Lib

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(LIBFT)
	@echo "minishell compiled"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@make clean -C ./Lib

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
