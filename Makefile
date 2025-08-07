# Compiler and flags
# Compiler and flags
CC      = cc
CFLAGS  =  -Wall -Wextra -Werror -I$(HOME)/readline-install/include
LDFLAGS = -L$(HOME)/readline-install/lib
LIBS    = -lreadline
# CFLAGS  = -g -Wall -Wextra -Werror -I/Users/slamhaou/.brew/opt/readline/include
# LDFLAGS = -L/Users/slamhaou/.brew/opt/readline/lib
# LIBS    = -lreadline

# Source and object files
NAME    = minishell
SRCS    =  ./pars/expand.c  \
			./pars/utils1.c  \
			./pars/utils.c \
			./pars/pars.c \
			./pars/get_value.c \
			./pars/expand1.c \
			./pars/dq_expand.c \
			./pars/cmd.c main.c \
			./pars/free_cmd.c \
			./pars/filter_token.c  \
			./pars/get_files.c \
			./pars/get_param.c \
			./pars/tokenization.c \
			./pars/second_tokinization.c \
			./pars/lst_utils1.c \
			./pars/utils_gvalue.c \
			./pars/listUtils.c \
			./pars/check_error.c \
			./pars/expand_utils.c \
			./pars/quotes.c \
			./pars/empty_node.c\
			./exec/gt_l.c \
			./exec/small_libft.c ./exec/exc.c \
			./exec/helper.c  ./exec/all_env.c \
			./exec/bilt_in/pwd.c ./exec/bilt_in/env.c ./exec/bilt_in/cd.c \
			 ./exec/bilt_in/unset.c ./exec/bilt_in/export.c ./exec/helper2.c\
			 ./exec/bilt_in/exit.c ./exec/bilt_in/echo.c ./exec/helper_heredoc.c\
			./exec/ignor_fun_now.c ./exec/rediraction.c ./exec/path.c ./exec/cmd_herdoc.c ./exec/child.c
OBJS    = $(SRCS:.c=.o)

# Build target
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and binary
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all
s : all clean
.PHONY: all clean fclean re
