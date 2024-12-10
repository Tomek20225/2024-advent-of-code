#include <stdio.h>
#include <stdlib.h>
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

int count_occurences(int_vector* v, int n) {
    if (!v) {
        return -1;
    }

    int occurences = 0;

    for (int i = 0; i < v_len(v); i++) {
        int* num_ptr = v_get(v, i);
        if (!num_ptr) {
            continue;
        }
        int num = *num_ptr;
        if (num == n) {
            occurences++;
        }
    }

    return occurences;
}

int main() {
    FILE *file_ptr;

    file_ptr = fopen("./input.txt", "r");
    if (file_ptr == NULL) {
        printf("There was an error during the opening of the file. Aborting.");
        fclose(file_ptr);
        return 1;
    }

    // Processing
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

    // Q2
    int similarity_score = 0;

    for (int i = 0; i < v_len(nums1); i++) {
        int* num_ptr = v_get(nums1, i);
        if (!num_ptr) {
            continue;
        }

        int num = *num_ptr;
        similarity_score += num * count_occurences(nums2, num);
    }

    // Q1
    int distance_sum = 0;

    while (v_len(nums1) != 0) {
        int min1 = find_and_pop_min(nums1);
        int min2 = find_and_pop_min(nums2);
        distance_sum += abs(min1 - min2);
    }

    // Results
    printf("Q1 result: %i\n", distance_sum);
    printf("Q2 result: %i\n", similarity_score);

    // Cleanup
    v_delete(nums1);
    v_delete(nums2);
    fclose(file_ptr);

    return 0;
}