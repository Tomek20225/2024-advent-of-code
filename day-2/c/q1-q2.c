#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../lib/vector/vector.h"

int_vector* calculate_diffs(int_vector* v) {
    if (!v) {
        return 0;
    }

    int_vector* diffs = v_create();

    int prev_num;
    for (int i = 0; i < v_len(v); i++) {
        int num = *v_get(v, i);

        if (i > 0) {
            v_append(diffs, num - prev_num);
        }

        prev_num = num;
    }

    return diffs;
}

int is_report_safe_handler(int_vector* v_diffs) {
    if (!v_diffs) {
        return 0;
    }

    int all_decreasing = 1;
    int all_increasing = 1;
    for (int i = 0; i < v_len(v_diffs); i++) {
        int diff = *v_get(v_diffs, i);

        if (abs(diff) > 3) {
            return 0;
        }

        if (diff > 0) {
            all_decreasing = 0;
        }
        else if (diff < 0) {
            all_increasing = 0;
        }
        else {
            return 0;
        }
    }

    return all_decreasing + all_increasing;
}

int is_report_safe(int_vector* v) {
    if (!v) {
        return 0;
    }

    // The levels are either all increasing or all decreasing.
    // Any two adjacent levels differ by at least one and at most three.

    int_vector* diffs = calculate_diffs(v);
    // v_print(diffs);

    int result = is_report_safe_handler(diffs);

    v_delete(diffs);

    return result;
}

int is_report_safe_dampened(int_vector* v) {
    if (!v) {
        return 0;
    }

    // The levels are either all increasing or all decreasing.
    // Any two adjacent levels differ by at least one and at most three.
    // If removing a single level from an unsafe report would make it safe, the report instead counts as safe.

    int len = v_len(v);

    for (int i = 0; i < len; i++) {
        int_vector* variant = v_create();

        for (int j = 0; j < len; j++) {
            if (j == i) {
                continue;
            }
            v_append(variant, *v_get(v, j));
        }

        int_vector* diffs = calculate_diffs(variant);
        v_delete(variant);

        if (is_report_safe_handler(diffs) == 1) {
            v_delete(diffs);
            return 1;
        }
    }

    return 0;
}

int main() {
    FILE* file_ptr;

    file_ptr = fopen("./input.txt", "r");
    if (file_ptr == NULL) {
        printf("There was an error during the opening of the file. Aborting.");
        fclose(file_ptr);
        return 1;
    }

    matrix* nums = matrix_create();

    int char_code;
    string* num_str = str_create();
    int_vector* row = v_create();

    while (1) {
        char_code = fgetc(file_ptr);

        if (char_code == EOF) {
            if (str_len(num_str) > 0) {
                int num = str_to_int(num_str);
                v_append(row, num);
                matrix_append(nums, row);
            }
            str_delete(num_str);
            break;
        }

        if (char_code >= '0' && char_code <= '9') {
            str_append(num_str, char_code);
            continue;
        }

        if (char_code == '\n') {
            int num = str_to_int(num_str);
            v_append(row, num);
            matrix_append(nums, row);

            row = v_create();

            str_delete(num_str);
            num_str = str_create();
            continue;
        }

        if (str_len(num_str) > 0) {
            int num = str_to_int(num_str);
            v_append(row, num);

            str_delete(num_str);
            num_str = str_create();
        }
    };

    // matrix_print(nums);

    // Q1
    int safe_report_count = 0;
    for (int i = 0; i < nums->items; i++) {
        if (is_report_safe(matrix_get(nums, i))) {
            safe_report_count++;
        }
    }

    // Q2
    int safe_dampened_report_count = 0;
    for (int i = 0; i < nums->items; i++) {
        if (is_report_safe_dampened(matrix_get(nums, i))) {
            safe_dampened_report_count++;
        }
    }

    // Results
    printf("Q1 result: %i\n", safe_report_count);
    printf("Q2 result: %i\n", safe_dampened_report_count);

    // Cleanup
    matrix_delete(nums);
    fclose(file_ptr);

    return 0;
}