#include "minishell.h"

void first_child (t_data *data, t_var_us var,char **env,t_env **envp)
{
    check_file(data,&var);
    if (check_cmd_build(data,envp,var))
        exit(0);
    var.pth = ft_getenv(*envp,"PATH");
    var.path = ft_split(var.pth,':');
    var.pth = check_path (var,data->cmd);
    if (var.infd != -2)
        {
            dup2(var.infd,0);
            close(var.infd);
        }
    if (var.outfd != -2)
    {
        dup2(var.outfd,1);
        close(var.outfd);
    }
    else
        dup2(var.fd1[var.i][1],1);
    close (var.fd1[var.i][0]);
    close (var.fd1[var.i][1]);
    execve(var.pth,data->cmd,env);
}

void secund_command(t_data *data,t_var_us var,char **env,t_env **envp)
{
    check_file(data,&var);
     if (check_cmd_build(data,envp,var))
        exit (0);
     var.pth = ft_getenv(*envp,"PATH");
    var.path = ft_split(var.pth,':');
    var.pth = check_path (var,data->cmd);
    if (var.infd != -2)
    {
        dup2(var.infd,0);
        close(var.infd);
    }
    else
        dup2(var.fd1[var.i -1][0],0);
    if (var.outfd != -2)
    {
        dup2(var.outfd,1);
        close(var.outfd);
    }
    else 
        dup2(var.fd1[var.i][1],1);
    close(var.fd1[var.i -1][0]);
    close (var.fd1[var.i][0]);
    close (var.fd1[var.i][1]);
    execve(var.pth,data->cmd,env);
}
void last_command (t_data *data,t_var_us var,char **env,t_env **envp)
{
    check_file (data,&var);
    if (check_singcmd_build(data, envp,var))
        exit(0);
    var.pth = ft_getenv(*envp,"PATH");
    var.path = ft_split(var.pth,':');
    var.pth = check_path (var,data->cmd);
    if (var.infd != -2)
    {
        dup2(var.infd,0);
        close(var.infd);
    }
    else
        dup2(var.fd1[var.i - 1][0],0);
    if (var.outfd != -2)
    {
        dup2(var.outfd,1);
        close(var.outfd);
    }
    close (var.fd1[var.i -1][0]);
    execve(var.pth,data->cmd,env);
}

void execut_comand(t_data *data,char **env,t_env **envp)
{
    int cont;
    t_var_us var;

    var.i = 0;
    cont = count_list(data);
    var.id = ft_calloc(sizeof(int),cont);
    var.fd1 = malloc (sizeof(int *) * cont);
    if (var.id == NULL || !var.fd1)
        return;
    while (var.i< cont)
    {
        var.fd1[var.i] = malloc (sizeof(int *) * cont);
        if (var.i< cont -1)
        {
            if (pipe(var.fd1[var.i]) == -1)
                 return;
        }
        var.id[var.i] = fork();
        if (var.id[var.i] == 0)
        {
            if (var.i== 0)
                first_child (data,var,env,envp);
            else if (var.i< cont - 1)
                secund_command(data,var,env,envp);
            else
                last_command (data,var,env,envp);
        }
        if (var.i> 0)
            close(var.fd1[var.i-1][0]);
        if (var.i< cont - 1)
            close (var.fd1[var.i][1]);
        var.i++;
        data = data->next;
    }
    var.i= 0;
    while (var.i<cont)
    {
        waitpid(var.id[var.i],0,0);
        var.i++;
    }
}
