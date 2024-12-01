#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int_vector* v_create() {
    int_vector* v = malloc(sizeof(int_vector));
    if (v) {
        v->data = malloc(sizeof(int));
        v->size = 1;
        v->items = 0;
    }
    return v;
}

void v_delete(int_vector* v) {
    if (v) {
        free(v->data);
        free(v);
    }
}

void v_append(int_vector* v, int n) {
    if (!v) {
        return;
    }

    if (v->items + 1 > v->size) {
        size_t new_size = v->size * 2;
        int* p = realloc(v->data, new_size * sizeof(int));
        if (p) {
            v->data = p;
            v->size = new_size;
        }
    }

    v->data[v->items] = n;
    v->items++;
}

int* v_get(int_vector* v, size_t i) {
    if (v && i < v->size) {
        return &v->data[i];
    }
    return NULL;
}

void v_set(int_vector* v, size_t i, int n) {
    if (v && i < v->size) {
        v->data[i] = n;
    }
}

void v_remove(int_vector* v, size_t i) {
    if (!v || i >= v->items) {
        return;
    }

    for (; i < v->items - 1; i++) {
        v->data[i] = v->data[i + 1];
    }

    v->items--;
}

void v_print(int_vector* v) {
    if (!v) {
        printf("The given vector doesn't exist.");
        return;
    }

    for (int i = 0; i < v->items; i++) {
        int* value = v_get(v, i);
        if (value) {
            printf("%i, ", *value);
        }
    }

    printf("\n");
}
