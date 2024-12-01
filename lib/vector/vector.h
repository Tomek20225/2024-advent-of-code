#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    size_t size;
    size_t items;
    int* data;
} int_vector;

int_vector* v_create();
void v_delete(int_vector* v);
void v_append(int_vector* v, int n);
int* v_get(int_vector* v, size_t i);
void v_set(int_vector* v, size_t i, int n);
void v_remove(int_vector* v, size_t i);
void v_print(int_vector* v);

#endif
