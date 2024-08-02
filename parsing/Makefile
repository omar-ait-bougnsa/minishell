name = minishell
CC = cc -Wall -Wextra -Werror -g #-fsanitize=address
flags = -lreadline 
SRC = minishell.c parsing.c syntax_error.c ft_execution.c ft_check_path.c ft_split.c ft_expending.c lexer_phase.c minishell_utilis.c\
ft_apend_struct.c execut_comand.c ft_setenv.c ft_getenv.c ft_export.c ft_unset.c check_build.c ft_free.c
OBG = $(SRC:.c=.o)

all : $(name)

$(name) : $(OBG)
	$(CC)   $(OBG) -o $(name) $(flags)
%.o : %.c
	$(CC) -c $< -o $@
clean :
	rm -f $(OBG)
fclean : clean
	rm -f $(name)
re : fclean all
