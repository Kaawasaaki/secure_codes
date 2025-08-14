//Overflow Example using calloc

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

// Function to implement calloc
void* my_calloc(size_t num_elements, size_t element_size) {
    // Check for overflow in the multiplication of num_elements and element_size
    if (num_elements != 0 && element_size > SIZE_MAX / num_elements) {
        // Overflow detected, return NULL
        return NULL;
    }

    // Allocate memory using malloc (calloc functionality is achieved by malloc + memset)
    void* ptr = malloc(num_elements * element_size);
    
    if (ptr == NULL) {
        // Memory allocation failed, return NULL
        return NULL;
    }

    // Zero out the allocated memory
    for (size_t i = 0; i < num_elements * element_size; i++) {
        *((char*)ptr + i) = 0;
    }

    return ptr;
}

int main() {
    size_t num_elements, element_size;
    
    printf("Enter the number of elements: ");
    scanf("%zu", &num_elements);
    
    printf("Enter the size of each element (in bytes): ");
    scanf("%zu", &element_size);

    void* memory = my_calloc(num_elements, element_size);

    if (memory == NULL) {
        printf("Memory allocation failed due to overflow or insufficient memory.\n");
    } else {
        printf("Memory allocated and initialized to zero.\n");

        
        if (element_size == sizeof(int)) {
            int* int_array = (int*)memory;
            for (size_t i = 0; i < num_elements; i++) {
                printf("int_array[%zu] = %d\n", i, int_array[i]);
            }
        }

       
        free(memory);
    }

    return 0;
}
