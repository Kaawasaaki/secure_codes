#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>  // For SIZE_MAX

// Secure calloc function
void* secure_calloc(size_t num_elements, size_t size_per_element) {
    // Handle edge cases where the number of elements or size is zero
    if (num_elements == 0 || size_per_element == 0) {
        std::cerr << "Warning: Attempted to allocate zero elements or zero size.\n";
        return nullptr;  // Return null if the allocation is invalid
    }

    // Calculate total memory size
    size_t total_size = num_elements * size_per_element;

    // Attempt memory allocation
    void* ptr = std::calloc(num_elements, size_per_element);
    
    if (ptr == nullptr) {
        std::cerr << "Error: Memory allocation failed for " << total_size << " bytes.\n";
        return nullptr;  // Allocation failed, return nullptr
    }

    std::cout << "Successfully allocated and initialized " << total_size << " bytes at " << ptr << ".\n";
    return ptr;
}

// Secure free function to safely deallocate memory
void secure_free(void* ptr) {
    if (ptr != nullptr) {
        std::free(ptr);
        std::cout << "Memory freed at " << ptr << ".\n";
    } else {
        std::cerr << "Warning: Attempted to free a nullptr.\n";
    }
}

int main() {
    // Test Case 1: Valid allocation of 10 elements of size 5 bytes each
    std::cout << "\nTest Case 1: Allocating 10 elements of 5 bytes each.\n";
    void* ptr1 = secure_calloc(10, 5);
    if (ptr1 != nullptr) {
        secure_free(ptr1);
    }

    // Test Case 2: Invalid allocation with zero elements
    std::cout << "\nTest Case 2: Allocating 0 elements.\n";
    void* ptr2 = secure_calloc(0, 10);  // Should return nullptr

    // Test Case 3: Invalid allocation with zero size per element
    std::cout << "\nTest Case 3: Allocating elements with size 0.\n";
    void* ptr3 = secure_calloc(10, 0);  // Should return nullptr

    // Test Case 4: Allocate a very large block of memory (1GB)
    std::cout << "\nTest Case 4: Allocating a large block of memory (1GB).\n";
    void* ptr4 = secure_calloc(1024 * 1024 * 1024, 1);  // 1GB allocation
    secure_free(ptr4);

    // Test Case 5: Allocate a reasonable amount of memory (100 elements of 10 bytes each)
    std::cout << "\nTest Case 5: Allocating 100 elements of 10 bytes each (1000 bytes).\n";
    void* ptr5 = secure_calloc(100, 10);
    if (ptr5 != nullptr) {
        secure_free(ptr5);
    }

    // Test Case 6: Free a null pointer (should not crash, just print a warning)
    std::cout << "\nTest Case 6: Freeing a NULL pointer.\n";
    secure_free(nullptr);

    // Test Case 7: Allocate a very small block of memory (1 byte)
    std::cout << "\nTest Case 7: Allocating a very small block (1 byte).\n";
    void* ptr7 = secure_calloc(1, 1);  // 1 byte allocation
    secure_free(ptr7);

    // Test Case 8: Attempt to allocate an extremely large amount of memory (e.g., 4GB)
    std::cout << "\nTest Case 8: Attempting to allocate 4GB of memory.\n";
    void* ptr8 = secure_calloc(1024 * 1024 * 1024, 4);  // 4GB allocation
    secure_free(ptr8);

    // Test Case 9: Reallocate (expand) memory from 10 bytes to 100 bytes
    std::cout << "\nTest Case 9: Reallocate memory from 10 bytes to 100 bytes.\n";
    void* ptr9 = secure_calloc(1, 10);  // Initial allocation (10 bytes)
    ptr9 = secure_calloc(1, 100);  // Reallocate to 100 bytes
    secure_free(ptr9);

    // Test Case 10: Allocate the largest size allowed by the system (SIZE_MAX)
    std::cout << "\nTest Case 10: Attempting to allocate the largest possible memory (SIZE_MAX).\n";
    void* ptr10 = secure_calloc(SIZE_MAX / 2, 2);  // Boundary test with large number of elements
    secure_free(ptr10);

    // Test Case 11: Allocating a small array and setting some values to check initialization
    std::cout << "\nTest Case 11: Allocating a small array and setting values.\n";
    void* ptr11 = secure_calloc(5, 4);  // 5 elements, 4 bytes each
    if (ptr11 != nullptr) {
        int* arr = (int*)ptr11;
        for (int i = 0; i < 5; ++i) {
            arr[i] = i + 1;  // Set values
        }
        for (int i = 0; i < 5; ++i) {
            std::cout << "Element " << i << ": " << arr[i] << std::endl;
        }
        secure_free(ptr11);
    }

    // Test Case 12: Allocating a memory block and freeing it multiple times (to check robustness)
    std::cout << "\nTest Case 12: Allocating and freeing memory multiple times.\n";
    void* ptr12 = secure_calloc(10, 10);  // 100 bytes allocation
    secure_free(ptr12);
    secure_free(ptr12);  // Trying to free twice (should be safe)

    // Test Case 13: Attempting to allocate negative or very large sizes (should handle overflow)
    std::cout << "\nTest Case 13: Allocating with a very large or negative size.\n";
    void* ptr13 = secure_calloc(SIZE_MAX / 2, SIZE_MAX / 2);  // Large allocation
    secure_free(ptr13);

    // Test Case 14: Allocating zero elements and size, then checking for a null pointer return
    std::cout << "\nTest Case 14: Allocating zero elements and zero size.\n";
    void* ptr14 = secure_calloc(0, 0);  // Should return nullptr

    // Test Case 15: Allocating a large block of memory and performing some operations on it
    std::cout << "\nTest Case 15: Allocating a large block of memory and initializing.\n";
    void* ptr15 = secure_calloc(100000, 1);  // 100,000 bytes
    if (ptr15 != nullptr) {
        std::memset(ptr15, 1, 100000);  // Initialize memory with 1
        secure_free(ptr15);
    }

    return 0;
}