#include "shuf.h"

// shuf file, output certain number of lines, print to stdio
char* test1[]={"shuf", "README.md", "-n", "10", "-t", "5432", (char *) NULL};
int t1_len = 6;

// shuf file, print to stdio
char* test2[]={"shuf", "README.md", "-t", "54", (char *) NULL};
int t2_len = 4;

// should fail for asking for less than 1 line
char* test3[]={"shuf", "README.md", "-t", "90", "-n", "0", (char *) NULL};
int t3_len = 6;

int p_fork(char *msg) {
  int pid = fork();
  if (pid == -1) {
    fprintf(2, "fork failed: %s\n", msg);
    exit(1);
  }
  return pid;
}

void run_test(int test_no) {
  printf("\n***************\nStarting TEST #%d\n***************\n", test_no + 1);
  int i;
  switch (test_no) {
    case 0:
      for (i = 0; i < t1_len; i++) {
        printf("arg[%d] = %s\n", i, test1[i]);
      }
      exec(test1[0], test1);
      fprintf(2, "exec: first test failed\n");
      exit(1);
    case 1:
      for (i = 0; i < t2_len; i++) {
        printf("arg[%d] = %s\n", i, test2[i]);
      }
      exec(test2[0], test2);
      fprintf(2, "exec: second test failed\n");
      exit(1);
    case 2:
      for (i = 0; i < t3_len; i++) {
        printf("arg[%d] = %s\n", i, test3[i]);
      }
      exec(test3[0], test3);
      fprintf(2, "exec: third test failed\n");
      exit(1);
  }
  exit(0);
}

int main()
{
  printf("TESTING SHUF\n");
  int test_no = 0;
  while (test_no < 3) {
    int pid = p_fork("test fork");
    if (pid == 0) {
      run_test(test_no);
    } else {
      wait(0);
    }
    test_no++;
  }

  return 0;
}

