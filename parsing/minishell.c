#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// -lreadline

int	check_quote(char *str)
{
	int	i;
	int	sinqot;
	int	dbqot;

	i = 0;
	sinqot = 1;
	dbqot = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && sinqot == 1)
			dbqot *= (-1);
		if (str[i] == '\'' && dbqot == 1)
			sinqot *= (-1);
		i++;
	}
	if (dbqot == -1 || sinqot == -1)
		return (0);
	return (1);
}

int	get_next_qout(char *str)
{
	int	i;
	int	sinqot;
	int	dobqot;

	i = 0;
	sinqot = 1;
	dobqot = 1;
	while (str[i])
	{
		if (str[i] == '\'' && dobqot == 1)
			sinqot *= -1;
		if (str[i] == '\"' && sinqot == 1)
			dobqot *= -1;
		if (sinqot == 1 && dobqot == 1 &&ft_strsrch("<> |\t\v",str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_token(char *len, int i, int *singl, int *doubl)
{
	if (len[i] == '\'' && *doubl != -1)
		*singl *= -1;
	if (len[i] == '\"' && *singl != -1)
		*doubl *= -1;
	if (len[i] == '\'' && (len[i + 1] == ' ' || len[i + 1] == '\t'))
		return (0);
	if (len[i] == '\"' && (len[i + 1] == ' ' || len[i + 1] == '\t'))
		return (0);
	if (ft_strsrch("<>|\t\v ",len[i])&& (*singl != -1 && *doubl != -1))
		return (0);
	else
		return (1);
}

void handle_signal(int sig)
{
	(void)sig;
	printf ("\n");
	rl_replace_line("",0);
	rl_on_new_line();
	rl_redisplay();
	return;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_lexer	*lexer;
	char	*len;
	t_env *envp;
	(void)ac;
	(void)av;
	//signal(SIGINT,handle_signal);
	ft_setenv(env,&envp);
	while (1)
	{
		
		len = readline("minshell $>");
		if (!check_quote(len))
		{
			printf("syntax error\n");
		}
		else
		{
			lexer = NULL;
			lexer_phase(len, &lexer,envp);
			data = ft_parsing(lexer, env);
			 ft_execution(data, env,envp);
			    // while (data)
			    // {
			    //      printf("------------------------------------\n");
			    //      printf ("command is %s\n",data->cmd[0]);
			    //      int i = 1;
			    //      while (data->cmd && data->cmd[i])
			    //      {
			    //         printf("args = %s\n",data->cmd[i]);
			    //         i++;
			    //      }
			    //     if (data->file)
			    //     {
			    //         while (data->file)
			    //         {
			    //             if (data->file->infile == 1)
			    //                 printf("infile is  %s\n",data->file->file);
			    //             else if (data->file->herdoc == 1)
			    //                 printf("herdoc is %s\n",data->file->file);
			    //             else if (data->file->apend == 1)
			    //                 printf("apend is %s\n",data->file->file);
			    //             else
			    //                 printf("outfile is  %s\n",data->file->file);
			    //             data->file = data->file->next;
			    //         printf("------------------------------------\n");
			    //         }
			    //     }
			    //     printf ("other pipe______________________________________|\n");
			    //     data = data->next;
			    // }
		}
		//free (data);
		add_history(len);
		free (len);
	}
	rl_clear_history();
}
