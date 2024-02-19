#include "shuf.h"
#include "user.h"
#include "../kernel/fcntl.h"

/* Requirements for use 
* 1. Makefile
*     - Add shuf to UPROGS
*     - Add vec.o to ULIB
*     - Add randomizer.o to ULIB
* 2. Additional
*     - System call for unix-time
*/

void parse_file(config_t* cp, vec_t *vec) 
{
  vec_init(vec, 5);
  uint sz = 0;
  char *line = NULL;
  int fd = open(cp->input, O_RDONLY);
  while (1) {
    if (getline(&line, &sz, fd) <= 0) {
      break;
	}
    vec_push(vec, line);
  }
  free(line);
}

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
  parse_file(&config, &vec);

  int i;
  for (i = 0; i < vec.len; i++) {
    printf("%s\n", vec.strings[i]);
  }

  vec_free(&vec);

  return 0;
}
