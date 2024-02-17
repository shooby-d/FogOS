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

int main(void) {

    vec_t vec;
    vec_init(&vec, 5);

    printf("init success\n");

    vec_push(&vec, "The");
    vec_push(&vec, "Current");
    vec_push(&vec, "Implementation");
    vec_push(&vec, "For Vec");
    vec_push(&vec, "Works!!!!!!!!!!!!!!!!!!!!");
    vec_push(&vec, "as does resizing???");

    int i;
    for (i = 0; i < vec.len; i++) {
      printf("%s\n", vec.strings[i]);
    }

    vec_free(&vec);

    return 0;
}
