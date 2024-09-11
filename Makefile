name = minishell
CC = cc 
flags = -Wall -Wextra -Werror  -g -fsanitize=address 
SRC = minishell.c parsing.c syntax_error.c ft_execution.c ft_check_path.c ft_split.c ft_expending.c lexer_phase.c minishell_utilis.c\
ft_apend_struct.c execut_comand.c ft_setenv.c ft_getenv.c ft_export.c ft_unset.c check_build.c ft_free.c ft_itoa.c apend_to_file.c\
ft_exit.c ft_herdoc.c ft_cd.c execut_build.c ft_catstr.c addstring.c ft_echo.c  ft_env.c check_file.c exec_coammd.c libift.c\
ft_strdup.c ft_strjoin.c hundle_signal.c ft_expand_her.c set_env.c print_sort.c
OBG = $(SRC:.c=.o)

all : $(name)

$(name) : $(OBG)
	$(CC) $(flags) $(OBG) -o $(name) -lreadline
%.o : %.c
	$(CC) $(flags) -c $< -o $@
clean :
	rm -f $(OBG)
fclean : clean
	rm -f $(name)
re : fclean all
