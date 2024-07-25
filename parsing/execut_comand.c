#include "minishell.h"

void first_child (t_data *data, t_var_us var,char **env,int i)
{
     var.pth = getenv("PATH");
    var.path = ft_split(var.pth,':');

    check_file(data,&var);
    printf ("here is working\n");
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
        dup2(var.fd1[i][1],1);
    close (var.fd1[i][0]);
    close (var.fd1[i][1]);
    execve(var.pth,data->cmd,env);
}
void secund_command(t_data *data,t_var_us var,char **env,int i)
{
     var.pth = getenv("PATH");
    var.path = ft_split(var.pth,':');
    check_file(data,&var);
    var.pth = check_path (var,data->cmd);
    if (var.infd != -2)
    {
        dup2(var.infd,0);
        close(var.infd);
    }
    else
        dup2(var.fd1[i -1][0],0);
    if (var.outfd != -2)
    {
        dup2(var.outfd,1);
        close(var.outfd);
    }
    else 
        dup2(var.fd1[i][1],1);
    close(var.fd1[i -1][0]);
    close (var.fd1[i][0]);
    close (var.fd1[i][1]);
    execve(var.pth,data->cmd,env);
}
void last_command (t_data *data,t_var_us var,char **env,int i)
{
     var.pth = getenv("PATH");
    var.path = ft_split(var.pth,':');
    check_file (data,&var);
    var.pth = check_path (var,data->cmd);
    if (var.infd != -2)
    {
        dup2(var.infd,0);
        close(var.infd);
    }
    else
        dup2(var.fd1[i - 1][0],0);
    if (var.outfd != -2)
    {
        dup2(var.outfd,1);
        close(var.outfd);
    }
    close (var.fd1[i -1][0]);
    close (var.fd1[i][0]);
    close (var.fd1[i][1]);
    execve(var.pth,data->cmd,env);
}
void execut_comand(t_data *data,char **env)
{
    int cont;
    int i;

    i = 0;
    cont = count_list(data);
    t_var_us var;
    var.id = ft_calloc(sizeof(int),cont);
    var.fd1 = malloc (sizeof(int *) * cont);
    if (var.id == NULL || !var.fd1)
        return;
    while (i < cont)
    {
        var.fd1[i] = malloc (sizeof(int *) * cont);
        if (i < cont -1)
        {
            printf ("yes\n");
            if (pipe(var.fd1[i]) == -1)
                 return;
        }
        var.id[i] = fork();
        if (var.id[i] == 0)
        {
            if (i == 0)
                first_child (data,var,env,i);
            else if (i < cont - 1)
                secund_command(data,var,env,i);
            else
                last_command (data,var,env,i);
        }
        if (i > 0)
            close(var.fd1[i -1][0]);
        if (i < cont - 1)
            close (var.fd1[i][1]);
        i++;
        data = data->next;
    }
    i = 0;
    while (i <cont)
    {
        waitpid(var.id[i],0,0);
        i++;
    }
}
