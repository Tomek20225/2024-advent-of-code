#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

// Integer Vector
int_vector* v_create() {
    int_vector* v = malloc(sizeof(int_vector));
    if (v) {
        v->data = malloc(sizeof(int));
        v->size = 1;
        v->items = 0;
    }
    return v;
}

int_vector* v_copy(int_vector* v) {
    if (!v) {
        return NULL;
    }

    int_vector* nv = malloc(sizeof(int_vector));
    if (!nv) {
        return NULL;
    }

    nv->size = v->size;
    nv->items = v->items;

    nv->data = malloc(v->size * sizeof(int));
    if (!nv->data) {
        free(nv);
        return NULL;
    }

    memcpy(nv->data, v->data, v->size * sizeof(int));

    return nv;
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

size_t v_len(int_vector* v) {
    if (!v) {
        return -1;
    }
    return v->items;
}


// Strings
string* str_create() {
    string* str = malloc(sizeof(string));
    if (str) {
        str->data = malloc(sizeof(char));
        str->size = 1;
        str->items = 0;
    }
    return str;
}

string* str_copy(string* str) {
    if (!str) {
        return NULL;
    }

    string* n_str = malloc(sizeof(string));
    if (!n_str) {
        return NULL;
    }

    n_str->size = str->size;
    n_str->items = str->items;

    n_str->data = malloc(n_str->size * sizeof(char));
    if (!n_str->data) {
        free(n_str);
        return NULL;
    }

    memcpy(n_str->data, str->data, str->size * sizeof(int));

    return n_str;
}

void str_delete(string* str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

void str_append(string* str, char c) {
    if (!str) {
        return;
    }

    if (str->items + 1 > str->size) {
        size_t new_size = str->size * 2;
        char* p = realloc(str->data, new_size * sizeof(char));
        if (p) {
            str->data = p;
            str->size = new_size;
        }
    }

    str->data[str->items] = c;
    str->items++;
}

char* str_get(string* str, size_t i) {
    if (str && i < str->size) {
        return &str->data[i];
    }
    return NULL;
}

void str_set(string* str, size_t i, char c) {
    if (str && i < str->size) {
        str->data[i] = c;
    }
}

void str_remove(string* str, size_t i) {
    if (!str || i >= str->items) {
        return;
    }

    for (; i < str->items - 1; i++) {
        str->data[i] = str->data[i + 1];
    }

    str->items--;
}

void str_print(string* str) {
    if (!str) {
        printf("The given string doesn't exist.");
        return;
    }

    for (int i = 0; i < str->items; i++) {
        char* value = str_get(str, i);
        if (value) {
            printf("%c", *value);
        }
    }

    printf("\n");
}

char* str(string* str) {
    return str->data;
}

size_t str_len(string* v) {
    if (!v) {
        return -1;
    }
    return v->items;
}