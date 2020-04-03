/**
###############################################
##################ALO SHELL####################
################# MADE BY . ###################
######### OMAR MOHAMED GHANEM 166 #############
######### AMR KHALID RAMADAN  177 #############
############# LOAY EZZAT 199  #################
**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


void type_prompt(void) ; // Fuction which called to promet the fixed header "ALO SHELL $" also used for color formating
void parsing_command(char *input, char **parameters) ; // This Function handle the input and point to every argument start
unsigned char read_error_check(char *input); // this fuucntion check the input for error to avoid segmentation errors !
void read_command(char *input); // this fuction read the input
unsigned char  wait_flag  = 0 ; // simple flag to chech whether the parent MUST wait or not
const char * color_string = "--color"; // the color argument for LS which is add in the parsing part if the command is LS

int main()
{
    pid_t fork_return; // shall hold process id
    char *input ;
    char  *parameters[64];


input = malloc(4098);   // Dynamic allocation for the input to avoid  memory Runtime errors



// The shell core
    while(1){

        read_command(input);
        parsing_command(input ,parameters);

    //forking

        fork_return = fork() ; // save the fork order for furtur checks

        if (fork_return == -1)
        {
            printf("Forking failed,Child process can't be created \n");

        }else if (fork_return == 0 )
            {
        //child process excution

            execvp(parameters[0], parameters) ;  // pass parameters list to execvp which change the enviroment to another process "the desired command "
            // just  for formating style  ERROR will be printed if the execvp failed else it won't return to the code again
            if(strcmp(parameters[0] ,"exit")!=0)
            printf("ERROR: Wrong Command\n");

            exit(0);

        }else
        {
            //parent process excution
            // if & is in the command parent process will wait ;

            if(wait_flag ==0)
                wait(NULL);
            else{
                wait_flag= 0 ;
                printf("%d \n",fork_return);
            }

        //Check for exit call

            if ( strcmp(parameters[0] ,"exit")==0 )
            {
                // Free the allocated mem for the input
                free(input);
                exit(0);
        }

    }}


// Free the allocated mem for the input
free(input);
return 0;
}




void type_prompt(void){
printf("\033[0;32m"); // chenge text color to green
printf("ALOShell $ ");
printf("\033[0m"); // Reset text color

}

void parsing_command(char*input , char **parameters){
char * first_cmd  = input;
unsigned char dir_flag = 0 ;
 while (*input != '\0') {       /* if not the end of input ....... */

           while ((*input == ' ' || *input == '\t' || *input == '\n' ||*input == '&' ||*input == '"' )&& dir_flag ==0 ){
               if(*input=='"'){dir_flag=1;
               input++;
               }
               else{
               if(*input == '&'){

                 wait_flag = 1 ; /*Check for the & and  replace it and set the flagg */
               }

               *input++ = '\0';     /* replace white spaces with 0    */

         } }
          *parameters++ = input;     /* save the argument position     */


          if(dir_flag==1){
            while(*input != '"')
            input++ ;

          *input++ = '\0';
          dir_flag = 0 ;  }
        while ((*input != '\0' && *input != ' ' &&
                 *input != '\t' && *input != '\n' && *input != '"') && dir_flag == 0)
               input++;             /* skip the argument until ...    */
     }
     if(strcmp(first_cmd,"ls")==0){
            *(parameters-1) = color_string;
            *parameters = NULL ;
            }
    else
     *(parameters-1) = NULL;                 /* mark the end of argument list  */
}


unsigned char read_error_check(char *input){
int i = 0 ;
/** this fuction scan the input to make sure it's not white space **/
while(*(input + i) != '\0'){
    if(*(input + i)!=' ' && *(input + i) != '\t' && *(input + i) !='\n' )
     return 0 ; // return 0 ===> NO ERROR
    i++;
}
return 1 ; //return 1 ====>ERROR

}


void read_command(char *input){
/** this fucntion ask for the input and keep asking if ERROR exists **/
type_prompt() ;
fgets(input, 4098,stdin); //Reads the input MAX size is 4098

while(read_error_check(input)){
    type_prompt();
    fgets(input, 4098,stdin);

}

}

