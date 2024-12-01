#include <stdio.h>
#include <stdlib.h>
#include "../../lib/vector/vector.h"

int main() {
    FILE *fptr;

    fptr = fopen("./input-example.txt", "r");
    if (fptr == NULL) {
        printf("There was an error during the opening of the file. Aborting.");
        fclose(fptr);
        return 1;
    }

    int_vector* nums1 = v_create();
    int_vector* nums2 = v_create();

    v_append(nums1, 1);
    v_append(nums1, 2);
    v_append(nums1, 3);
    v_append(nums1, 4);

    v_remove(nums1, 1);
    v_remove(nums1, 3);

    v_print(nums1);

    v_delete(nums1);
    v_delete(nums2);
    fclose(fptr);

    return 0;
}