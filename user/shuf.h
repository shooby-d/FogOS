#include "user.h"
#include "../kernel/fcntl.h"

#define FILE_NAME_LEN 64
#define NULL ((void *) 0)

#define INPUT 1
#define OUTPUT 2

typedef struct {
  int cap;
  int len;
  char** strings;
} vec_t;

typedef struct {
  char input[FILE_NAME_LEN];
  char output[FILE_NAME_LEN];
  int num_lines;
} config_t;

/* Tests */
extern void test_shuf(void);

/* Vector structure functions */
extern void vec_init(vec_t* vec, int start_sz);
extern void vec_push(vec_t* vec, char* string);

/* Randomizing functions */
extern void srand(int x);
extern int lcg();
extern void fisher_yates(vec_t* vec, int flag);

extern int rseed;
