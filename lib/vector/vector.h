#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Integer Vector
typedef struct {
    size_t size;
    size_t items;
    int* data;
} int_vector;

int_vector* v_create();
int_vector* v_copy(int_vector* v);
void v_delete(int_vector* v);
void v_append(int_vector* v, int n);
int* v_get(int_vector* v, size_t i);
void v_set(int_vector* v, size_t i, int n);
void v_remove(int_vector* v, size_t i);
void v_print(int_vector* v);
size_t v_len(int_vector* v);

// Matrix (Vector of Integer Vectors)
typedef struct {
    size_t size;
    size_t items;
    int_vector** data;
} matrix;

matrix* matrix_create();
void matrix_delete(matrix* m);
void matrix_append(matrix* m, int_vector* v);
int_vector* matrix_get(matrix* m, size_t i);
void matrix_set(matrix* m, size_t i, int_vector* v);
void matrix_remove(matrix* m, size_t i);
void matrix_print(matrix* m);
size_t matrix_len(matrix* m);

// Char Vector (Mutabe String)
typedef struct {
    size_t size;
    size_t items;
    char* data;
} string;

string* str_create();
string* str_copy(string* str);
void str_delete(string* str);
void str_append(string* str, char c);
char* str_get(string* str, size_t i);
void str_set(string* str, size_t i, char c);
void str_remove(string* str, size_t i);
void str_print(string* str);
void str_print(string* str);
char* str(string* str);
size_t str_len(string* str);
int str_to_int(string* str);

#endif
