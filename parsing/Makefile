name = minishell
CC = cc -g #-fsanitize=address
flags = -lreadline 
SRC = minishell.c parsing.c syntax_error.c ft_execution.c ft_check_path.c ft_split.c
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
