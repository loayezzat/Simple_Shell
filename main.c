#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
void type_prompt(void) ;
void read_command(char *input, char **parameters) ;

int main()
{
    pid_t fork_return;
    char *input ;
    char  *parameters[64];


input = malloc(4098);




    while(1){
            type_prompt() ;
            fgets(input, 4098,stdin);
            read_command(input ,parameters);


    //forking

    fork_return = fork() ;

    if (fork_return == -1)
    {
        printf("Forking failed, child process can't be created\n") ;

    }else if (fork_return == 0 )
    {
        //child process excution

        execvp(parameters[0], parameters) ;
        printf("\n");

    }else
    {
        //parent process excution





        if ( strcmp(parameters[0] ,"exit")==0 )
        {   free(input);
            exit(0);

        }

    }}



free(input);
    return 0;
}




void type_prompt(void){
printf("ALOShell $ ");

}

void read_command(char*input , char **parameters){


 while (*input != '\0') {       /* if not the end of input ....... */
          while (*input == ' ' || *input == '\t' || *input == '\n')
               *input++ = '\0';     /* replace white spaces with 0    */
          *parameters++ = input;          /* save the argument position     */
          while (*input != '\0' && *input != ' ' &&
                 *input != '\t' && *input != '\n')
               input++;             /* skip the argument until ...    */
     }
     *(parameters-1) = NULL;                 /* mark the end of argument list  */


}



















