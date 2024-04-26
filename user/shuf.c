/* Requirements for use 
* 1. Makefile
*     - Add shuf to UPROGS
*     - Add vec.o to ULIB
*     - Add shuffler.o to ULIB
* 2. Additional
*     - System call for unix-time
*/

#include "shuf.h"

int seedflag = 0;

void arg_error(char* error)
{
  printf("shuf: %s\n", error);
  exit(-1);
}

void parse_file(config_t* cp, vec_t *vec) 
{
  // init line size, line ptr
  uint sz = 0;
  char *line = NULL;
  int fd = open(cp->input, O_RDONLY);
  if (fd == -1) arg_error("Input file doesn't exist");
  while (1) {
    if (getline(&line, &sz, fd) <= 0) {
      break;
	}
	// add string to vector
    vec_push(vec, line);
  }
  free(line);
}

void update_file(config_t* cp, char* fn, int option)
{
  int len = strlen(fn);
  if (len > FILE_NAME_LEN - 1) {
    arg_error("Output file name too long");
  }
  switch (option) {
    case INPUT:
      strcpy(cp->input, fn);
      break;
    case OUTPUT:
      strcpy(cp->output, fn);
      break;
    default:
      arg_error("Improper use of update_file function");
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
    if (strcmp(argv[i], "-o") == 0) {
      if (argv[++i] == NULL) {
         arg_error("No file present after -o flag");
      }
      update_file(cp, argv[i], OUTPUT);
    } else if (strcmp(argv[i], "-n") == 0) {;
      if (argv[++i] == NULL) {
        arg_error("No line count present after -n flag");
      }
      int n = atoi(argv[i]);
      if (n <= 0) arg_error("Requesting 0 or less lines in output");
      update_lines_printed(cp, n);
    } else if (strcmp(argv[i], "-h") == 0) {
      printf("Usage: shuf \"file name\" *required*\nAdditional flags:\n-n \"# of lines to output\"\n-o \"file name to output to\"\n-t \"set seed for tests\"\n");
      exit(0);
    } else if (strcmp(argv[i], "-t") == 0) {
      if (argv[++i] == NULL) {
        arg_error("No seed given after -t flag");
      }
      seedflag = atoi(argv[i]);
    } else {
      if (argv[i][0] == '-'){
      	  arg_error("Invalid flag");
      }
      if (strlen(cp->input) != 0) {
      	arg_error("Too many files: possibly missing flag for output file");
      }
	  update_file(cp, argv[i], INPUT);
    }  
    i++;
  }
  if (strlen(cp->input) == 0) {
    arg_error("No input file found");
  }
}

void print_num_lines(config_t* cp, vec_t* vec, int fd)
{
  int writeout = (fd != -1) ? fd : 1; // write to file or stdout
  switch (cp->num_lines) {
    case -1:
      for (int i = 0; i < vec->len; i++) {
        fprintf(writeout, "%s", vec->strings[i]);
      }
      break;
    default:
     if (cp->num_lines >= vec->len) arg_error("Requesting more lines printed than found in file");
     for (int i = 0; i < cp->num_lines; i++) {
       fprintf(writeout, "%s", vec->strings[i]);
     }
     break;
  }
}

void handle_output(config_t* cp, vec_t* vec)
{
  fisher_yates(vec, seedflag);
  int fd = (strlen(cp->output) == 0) ? -1 : open(cp->output, O_CREATE | O_RDWR); // do we have an output file
  print_num_lines(cp, vec, fd);
}

void shuf(int argc, char** argv)
{
  // init data structures
  vec_t vec;
  vec_init(&vec, 5);
  config_t config = {"", "", -1};
  
  parse_input(argc, argv, &config);
  parse_file(&config, &vec);
  handle_output(&config, &vec);
}

int main(int argc, char** argv)
{
  shuf(argc, argv);
  return 0;
}
