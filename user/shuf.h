#ifndef SHUF_H
#define SHUF_H

typedef struct {
    int cap;
    int len;
    char** strings;
} vec_t;

/* Vector structure functions */
extern void vec_init(vec_t* vec, int start_sz);
extern void vec_push(vec_t* vec, char* string);
extern void vec_free(vec_t* vec);

/* Randomizing functions */
extern void srand(int x);
extern int rand();
extern void fisher_yates(vec_t* vec);

extern int rseed;

#endif /* SHUF_H */
