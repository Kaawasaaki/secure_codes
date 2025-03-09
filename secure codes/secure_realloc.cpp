#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>  // Include this header for SIZE_MAX

void* secure_realloc(void* ptr, size_t new_size) {
    if (new_size == 0) {
        std::cerr << "Error: Invalid size of 0 bytes requested for realloc.\n";
        return nullptr;  // If size is 0, return nullptr (like free)
    }

    if (ptr == nullptr) {
        std::cerr << "Warning: Attempting to realloc a nullptr.\n";
        return std::malloc(new_size);  // If pointer is nullptr, act like malloc
    }

    void* new_ptr = std::realloc(ptr, new_size);

    if (new_ptr == nullptr) {
        std::cerr << "Error: Memory reallocation failed for " << new_size << " bytes.\n";
        return nullptr;  // Allocation failed
    }

    std::cout << "Successfully reallocated memory to " << new_size << " bytes at " << new_ptr << ".\n";
    return new_ptr;
}

void secure_free(void* ptr) {
    if (ptr != nullptr) {
        std::free(ptr);
        std::cout << "Memory freed at " << ptr << ".\n";
    } else {
        std::cerr << "Warning: Attempted to free a nullptr.\n";
    }
}

int main() {
    // Test Case 1: Reallocate a small memory block (resize from 10 bytes to 20 bytes)
    std::cout << "\nTest Case 1: Reallocate small memory block (10 bytes to 20 bytes).\n";
    void* ptr1 = std::malloc(10);
    ptr1 = secure_realloc(ptr1, 20);
    secure_free(ptr1);

    // Test Case 2: Reallocate memory to a larger size (10 bytes to 100 bytes)
    std::cout << "\nTest Case 2: Reallocate memory to a larger size (10 bytes to 100 bytes).\n";
    void* ptr2 = std::malloc(10);
    ptr2 = secure_realloc(ptr2, 100);
    secure_free(ptr2);

    // Test Case 3: Reallocate memory with size 0 (should free the memory)
    std::cout << "\nTest Case 3: Reallocate memory with size 0 (should free the memory).\n";
    void* ptr3 = std::malloc(50);
    ptr3 = secure_realloc(ptr3, 0);  // Equivalent to free
    secure_free(ptr3);

    // Test Case 4: Reallocate a null pointer (should behave like malloc)
    std::cout << "\nTest Case 4: Reallocate a null pointer (should behave like malloc).\n";
    void* ptr4 = nullptr;
    ptr4 = secure_realloc(ptr4, 50);  // Should behave like malloc
    secure_free(ptr4);

    // Test Case 5: Reallocate a large block of memory (1GB)
    std::cout << "\nTest Case 5: Reallocate a large block of memory (1GB).\n";
    void* ptr5 = std::malloc(1024 * 1024 * 1024);  // 1GB
    ptr5 = secure_realloc(ptr5, 1024 * 1024 * 1024);  // Reallocate to same size
    secure_free(ptr5);

    // Test Case 6: Attempt to reallocate a null pointer (should act as malloc)
    std::cout << "\nTest Case 6: Attempt to reallocate a null pointer (should act as malloc).\n";
    void* ptr6 = nullptr;
    ptr6 = secure_realloc(ptr6, 10);  // Equivalent to malloc
    secure_free(ptr6);

    // Test Case 7: Attempt to reallocate more than available system memory
    std::cout << "\nTest Case 7: Attempt to reallocate more than available system memory.\n";
    void* ptr7 = std::malloc(1024 * 1024 * 100);  // 100MB allocation
    ptr7 = secure_realloc(ptr7, SIZE_MAX);  // Try reallocating to the largest possible size
    secure_free(ptr7);

    // Test Case 8: Reallocate a memory block to a smaller size
    std::cout << "\nTest Case 8: Reallocate memory to a smaller size (100 bytes to 50 bytes).\n";
    void* ptr8 = std::malloc(100);
    ptr8 = secure_realloc(ptr8, 50);  // Reduce size
    secure_free(ptr8);

    // Test Case 9: Attempt to reallocate a previously freed block (undefined behavior, should return nullptr)
    std::cout << "\nTest Case 9: Reallocate a previously freed block.\n";
    void* ptr9 = std::malloc(50);
    secure_free(ptr9);
    ptr9 = secure_realloc(ptr9, 100);  // Undefined behavior
    secure_free(ptr9);

    // Test Case 10: Reallocate memory and fill it with a pattern to ensure it's being used
    std::cout << "\nTest Case 10: Reallocate memory and fill it with a pattern.\n";
    void* ptr10 = std::malloc(100);
    ptr10 = secure_realloc(ptr10, 100);
    for (size_t i = 0; i < 100; i++) {
        ((char*)ptr10)[i] = (i % 256);  // Fill with a simple pattern
    }
    secure_free(ptr10);

    return 0;
}
