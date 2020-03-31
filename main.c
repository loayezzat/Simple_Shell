#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void type_prompt(void) ;
void read_command(char cmd []  , char** parameters) ;

int main()
{
    pid_t fork_return;
    char command [100] , char* parameters [20] ;

while(1)
{
    //type prompt
    type_prompt() ;
    //read input
    read_command( command ,parameters ) ;
    //forking
    fork_return = fork() ;

    if (fork_return == -1)
    {
        printf("Forking failed, child process can't be created\n") ;

    }else if (fork_return == 0 )
    {
        //child process excution
        //excepv(command, parameters) ;
    }else
    {
        //parent process excution
        if ( strcmp(command , ) == "exit"  )
        {
            break ;
        }

    }


}

    return 0;
}
