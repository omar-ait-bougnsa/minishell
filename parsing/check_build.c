#include "minishell.h"

int check_cmd_build(t_data *data,t_env **envp,t_var_us var)
{
    int flag;
    
    flag = 0;
    if (!ft_strcmp (data->cmd[0],"pwd") ||!ft_strcmp (data->cmd[0],"cd"))
        flag = 1;
    else if (!ft_strcmp (data->cmd[0],"echo") ||!ft_strcmp (data->cmd[0],"export"))
        flag = 1;
    else if (!ft_strcmp (data->cmd[0],"env") ||!ft_strcmp (data->cmd[0],"unset"))
        flag = 1;
   if (flag == 1)
   {
        if (var.outfd != -2)
            dup2 (var.outfd,1);
        else
            dup2(var.fd1[var.i][1],1);
        close (var.fd1[var.i][0]);
        close (var.fd1[var.i][1]);
        check_buildin(data, envp);
        return (1);
   }
   return (0);
}

int check_singcmd_build(t_data *data,t_env **envp,t_var_us var)
{
    int flag;
    int fd;


    flag = 0;
    if (data->cmd == NULL)
        return (0);
    if (!ft_strcmp (data->cmd[0],"pwd") ||!ft_strcmp (data->cmd[0],"cd"))
        flag = 1;
    else if (!ft_strcmp (data->cmd[0],"echo") ||!ft_strcmp (data->cmd[0],"export"))
        flag = 1;
    else if (!ft_strcmp (data->cmd[0],"env") ||!ft_strcmp (data->cmd[0],"unset"))
        flag = 1;
   if (flag == 1)
   {
        fd = dup(1);
        check_file (data,&var);
        if (var.outfd != -2)
            dup2 (var.outfd,1);
        close (var.outfd);
        check_buildin(data, envp);
        dup2 (fd,1);
        close (fd);
        return (1);
   }
   return (0);
}