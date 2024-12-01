#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../lib/vector/vector.h"

int find_and_pop_min(int_vector* v) {
    int min = INT32_MAX;
    
    if (!v || v_len(v) == 0) {
        return min;
    }

    int min_idx = -1;

    for (int i = 0; i < v_len(v); i++) {
        int num = *v_get(v, i);
        if (num < min) {
            min = num;
            min_idx = i;
        }
    }

    if (min_idx != -1) {
        v_remove(v, min_idx);
    }

    return min;
}

int str_to_int(string* str) {
    int len = str_len(str);
    int num = 0;

    for (int i = len - 1; i >= 0; i--) {
        size_t str_idx = len - i - 1;
        char* char_value = str_get(str, str_idx);
        if (char_value) {
            int int_value = *char_value - '0';
            num += pow(10, i) * int_value;
        }
    }

    return num;
}

int main() {
    FILE *file_ptr;

    file_ptr = fopen("./input.txt", "r");
    if (file_ptr == NULL) {
        printf("There was an error during the opening of the file. Aborting.");
        fclose(file_ptr);
        return 1;
    }

    int_vector* nums1 = v_create();
    int_vector* nums2 = v_create();
    
    int char_code;
    string* num_str = str_create();

    while (1) {
        char_code = fgetc(file_ptr);

        if (char_code == EOF) {
            if (str_len(num_str) > 0) {
                int num = str_to_int(num_str);
                v_append(nums2, num);
            }
            str_delete(num_str);
            break;
        }

        if (char_code >= '0' && char_code <= '9') {
            str_append(num_str, char_code);
            continue;
        }

        if (str_len(num_str) > 0) {
            int num = str_to_int(num_str);

            if (v_len(nums1) > v_len(nums2)) {
                v_append(nums2, num);
            }
            else {
                v_append(nums1, num);
            }

            str_delete(num_str);
            num_str = str_create();
        }
    };

    int distance_sum = 0;

    while (v_len(nums1) != 0) {
        int min1 = find_and_pop_min(nums1);
        int min2 = find_and_pop_min(nums2);
        distance_sum += abs(min1 - min2);
    }

    printf("Result: %i\n", distance_sum);

    v_delete(nums1);
    v_delete(nums2);
    fclose(file_ptr);

    return 0;
}