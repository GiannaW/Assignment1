/* ----------------------------------------------------------------- */
/* PROGRAM  shell.c                                                  */
/*    This program reads in an input line, parses the input line     */
/* into tokens, and use execvp() to execute the command.             */
/* ----------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXINPUT 100

/* ----------------------------------------------------------------- */
/* FUNCTION  parse:                                                  */
/*    This function takes an input line and parse it into tokens.    */
/* It first replaces all white spaces with zeros until it hits a     */
/* non-white space character which indicates the beginning of an     */
/* argument.  It saves the address to argv[], and then skips all     */
/* non-white spaces which constitute the argument.                   */
/* ----------------------------------------------------------------- */

void  parse(char *line, char **argv)
{
    while (*line != '\0') {       /* if not the end of line ....... */ 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';     /* replace white spaces with 0    */
        *argv++ = line;          /* save the argument position     */
        while (*line != '\0' && *line != ' ' && 
               *line != '\t' && *line != '\n') 
            line++;             /* skip the argument until ...    */
    }
    *argv = "\0";                 /* mark the end of argument list  */
}

/* ----------------------------------------------------------------- */
/* FUNCTION execute:                                                 */
/*    This function receives a commend line argument list with the   */
/* first one being a file name followed by its arguments.  Then,     */
/* this function forks a child process to execute the command using  */
/* system call execvp().                                             */
/* ----------------------------------------------------------------- */

void  execute(char **argv)
{
    pid_t  pid;
    int    status;
    int    answer = 0;
    int    dividend, divisor;
    int length;

    if ((pid = fork()) < 0) {     /* fork a child process           */
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0) {          /* for the child process:         */

        //Subtraction
        if (strcmp(argv[0], "S") == 0) {
         
            
           
            
            
            
            answer = atoi(argv[1]) - atoi(argv[2]);
            printf("%d\n", answer);
        }

        // Multiplication
        else if (strcmp(argv[0], "M") == 0) {
            answer = atoi(argv[1]) * atoi(argv[2]);
            printf("%d\n", answer);
        }

        //Division
        else if (strcmp(argv[0], "D") == 0) {
            dividend = atoi(argv[1]);
            divisor = atoi(argv[2]);
            answer = dividend / divisor;
            printf("%d\n", answer);
        }

        //Addition
        else if (strcmp(argv[0], "A") == 0) {
            answer = atoi(argv[1]) + atoi(argv[2]);
            printf("%d\n", answer);
        }
        /*
      This is the code we wanted to use for Addition, however, nothing returned:

      if (strcmp(argv[0], "A") == 0) {
        for (int i = 1; argv[i] != NULL; ++i) {
          answer += atoi(argv[i]);       
        }
        printf("%d\n", answer);
      }

*/

        if (execvp(*argv, argv) < 0) {     /* execute the command  */
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else {                                  /* for the parent:      */
        while (wait(&status) != pid)       /* wait for completion  */
            ;
    }
}

/* ----------------------------------------------------------------- */
/*                  The main program starts here                     */
/* ----------------------------------------------------------------- */

int main(void)
{
    char  line[1024];             /* the input line                 */
    char  *argv[64];              /* the command line argument      */

    while (1) {                   /* repeat until done .... 
    */
        printf("If you decide to Subtact or Divide only input 2 numbers");
        printf("\n");
        printf("Calculator -> ");     /*   display a prompt             */
        fgets(line, sizeof(line), stdin);              /*   read in the command line     */

        parse(line, argv);       /*   parse the line               */
        if (strcmp(argv[0], "exit") == 0)  /* is it an "exit"?     */
            exit(0);            /*   exit if it is                */
        execute(argv);           /* otherwise, execute the command */
    }
}
