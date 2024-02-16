#include "../kernel/types.h"
#include "user.h"

int main(void) {

  uint64 seconds;
  uint64 minutes;
  uint64 hours;
  uint32 days;
  uint32 years;

  seconds = time() / 1000000000;
  printf("***********\n*UNIX TIME*\n***********\n");
  printf("Time in seconds: %d\n", seconds);
  return 0;
}