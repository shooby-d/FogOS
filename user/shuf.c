#include "shuf.h"
#include "user.h"

/* Requirements for use 
* 1. Makefile
*     - Add shuf to UPROGS
*     - Add vec.o to ULIB
*     - Add randomizer.o to ULIB
* 2. Additional
*     - System call for unix-time
*/
void arg_error(char* error)
{
  printf("shuf error: %s\n", error);
  exit(-1);
}

void update_file(config_t* cp, char* fn, int option)
{
  int len = strlen(fn);
  if (len > FILE_NAME_LEN - 1) {
    arg_error("Output file name too long");
  }
  switch (option) {
    case 1:
      strcpy(cp->input, fn);
      break;
    case 2:
      strcpy(cp->output, fn);
      break;
    default:
      arg_error("Inproper use of update_file function");
  }
}

void update_lines_printed(config_t* cp, int n)
{
  cp->num_lines = n;
}

void parse_input(int argc, char** argv, config_t* cp)
{
  int i = 1;
  while (i < argc) {
    if (strcmp(argv[i], "-f") == 0) {
      if (argv[++i] == NULL) {
        arg_error("No file present after -f flag");
      }
      update_file(cp, argv[i], 1);
    } else if (strcmp(argv[i], "-o") == 0) {
      if (argv[++i] == NULL) {
         arg_error("No file present after -o flag");
      }
      update_file(cp, argv[i], 2);
    } else if (strcmp(argv[i], "-n") == 0) {;
      if (argv[++i] == NULL) {
        arg_error("No line count present after -n flag");
      }
      int n = atoi(argv[i]);
      update_lines_printed(cp, n);
    } else {
      arg_error("Unknown flag found");
    }
    i++;
  }

  if (strlen(cp->input) == 0) {
    arg_error("No input file found");
  }
}

int main(int argc, char** argv)
{
  vec_t vec;
  config_t config = {"", "", 0};
  parse_input(argc, argv, &config);
  vec_init(&vec, 5);

  printf("input file name: %s\n", config.input);
  printf("input output name: %s\n", config.output);
  printf("input lines output: %d\n", config.num_lines);

  srand((uint32)(time() % 1000000));
  printf("and a random number: %d\n", lcg());

  vec_free(&vec);

  return 0;
}
