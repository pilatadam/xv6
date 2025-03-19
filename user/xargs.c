#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"


int
main(int argc, char *argv[])
{
  char **argarr = malloc(MAXARG * sizeof(char *));

  int i = 0, j = 0, in = 0;
  
  // Fill arguments
  for(int k = 1; k < argc; k++)
    argarr[i++] = argv[k];

  argarr[i] = malloc(100);

  char c;
  while (read(0, &c, 1) > 0) {

    if (c == '\n')
      break;

    if (c == ' ') {
      if (in) {
        argarr[i++][j] = '\0';
        argarr[i] = malloc(100);
        j = 0;
        in = 0;
      }
    }
    else {
      argarr[i][j++] = c;
      in = 1;
    }
  }

  if (in)
    argarr[i++][j] = '\0';
  argarr[i] = 0;

  exec(argv[1], argarr);

  exit(0);
}
