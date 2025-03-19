#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

void
freeargarr(char **argarr, int arrlen)
{
  for(int i = 0; i < arrlen; i++)
    free(argarr[i]);
}

int
main(int argc, char *argv[])
{
  char **argarr = malloc(MAXARG * sizeof(char *));
  if (argarr == 0) {
    fprintf(2, "Error: malloc failed!\n");
    exit(1);
  }
  int arrlen = 0;
  
  /** Fill the array with arguments to the command to be run.
   *  Arguments are same for each input line.
   */
  for(int k = 1; k < argc; k++)
    argarr[arrlen++] = argv[k];

  argarr[arrlen] = malloc(100);
  if (argarr[arrlen] == 0) {
    fprintf(2, "Error: malloc failed!\n");
    freeargarr(argarr, arrlen);
    exit(1);
  }

  /**
   * [argind]: index of the argument being parsed
   * [strind]: index of the string in the argument
   * [in]:     1 if we are reading word chars, 0 for spaces...
   */
  int argind, strind, in;
  char c;
  int readbytes = 1;
  while (readbytes) {
    argind = arrlen;
    strind = 0;
    in = 0;

    /**
     *  Parse the line and divide it into multiple arguments
     */
    while ((readbytes = read(0, &c, 1)) > 0) {

      if (c == '\n')
        break;

      if (c == ' ') {
        /**
         *  If we were reading argument and read ' ',
         *  so we are likely at the end of argument
         */
        if (in) {
          argarr[argind++][strind] = '\0';
          /**
           *  Allocate memory for next argument if not
           *  already allocated, handle malloc failure
           */
          if (argind >= arrlen) {
            argarr[argind] = malloc(100);
            if (argarr[argind] == 0) {
              fprintf(2, "Error: malloc failed!\n");
              freeargarr(argarr, arrlen);
              exit(1);
            }
          }
          strind = 0;
          in = 0;
        }
      }
      else {
        argarr[argind][strind++] = c;
        in = 1;
      }
    
    }

    if (in)
      argarr[argind++][strind] = '\0';
    /**
     *  Set the last argument in the array to NULL, since
     *  argv[argc] == NULL
     */
    argarr[argind] = 0;

    /**
     *  Break when no new arguments read
     */
    if (arrlen == argind)
      break;

    if (fork() == 0) {
      /**
       *  Run the command in the child, handle exec failure
       */
      exec(argv[1], argarr);
      fprintf(2, "Error: exec failed!\n");
      freeargarr(argarr, arrlen);
      exit(1);
    }
    else {
      /**
       *  Wait in the child for the execution of the command
       */
      wait(0);
    }
  }

  freeargarr(argarr, arrlen);
  exit(0);
}
