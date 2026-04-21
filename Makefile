NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include
RM      = rm -rf
LIBS    = -lreadline 
MAKEFLAGS += --no-print-directory

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
LIBFT	= ./Lib/libft.a

# Sources 
SRCS    = main.c \
          utils/env_build.c \
		  utils/utils.c \
          parse/prompt_loop.c \
          parse/parse.c \
          parse/parse_errors.c \
          parse/parse_build.c \
		  parse/parse_build_utils.c \
          parse/signals.c \
		  parse/signal_helper.c \
          parse/tokenize.c \
		  parse/tokenize_utils.c \
          parse/token_syntax.c \
          parse/expand.c \
		  parse/expand_split.c \
		  parse/expand_utils.c \
          parse/expand_utils2.c \
          parse/expand_utils3.c \
          parse/remove_quotes.c \
          parse/remove_empty_words.c \
          execute/executor.c \
          execute/pipeline.c \
		  execute/pipeline_utils.c \
          execute/pipeline_utils_2.c \
		  execute/redir.c \
		  execute/redir_utils.c \
          execute/path.c \
          execute/env_utils.c \
          execute/builtins/cd.c \
          execute/builtins/pwd.c \
          execute/builtins/echo.c \
          execute/builtins/env.c \
          execute/builtins/export.c \
		  execute/builtins/export_helper.c \
		  execute/builtins/export_helper_2.c \
          execute/builtins/unset.c \
          execute/builtins/exit.c \


SRCS    := $(addprefix $(SRC_DIR), $(SRCS))
OBJS    = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Rules
all: $(NAME)

$(LIBFT):
					@make -C ./Lib/

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
