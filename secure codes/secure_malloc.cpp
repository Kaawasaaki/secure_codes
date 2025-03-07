#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdint>  // For SIZE_MAX

// Secure malloc function
void* secure_malloc(size_t size) {
    if (size == 0) {
        std::cerr << "Warning: Attempted to allocate zero bytes.\n";
        return nullptr;  // Return nullptr if trying to allocate zero bytes
    }

    // Attempt memory allocation
    void* ptr = std::malloc(size);
    
    if (ptr == nullptr) {
        std::cerr << "Error: Memory allocation failed for " << size << " bytes.\n";
        return nullptr;  // Allocation failed, return nullptr
    }

    std::cout << "Successfully allocated " << size << " bytes at " << ptr << ".\n";
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
    // Test Case 1: Valid allocation of 50 bytes
    std::cout << "\nTest Case 1: Allocating 50 bytes.\n";
    void* ptr1 = secure_malloc(50);
    if (ptr1 != nullptr) {
        secure_free(ptr1);
    }

    // Test Case 2: Invalid allocation of zero bytes
    std::cout << "\nTest Case 2: Allocating 0 bytes.\n";
    void* ptr2 = secure_malloc(0);  // Should return nullptr

    // Test Case 3: Allocate a large block of memory (1MB)
    std::cout << "\nTest Case 3: Allocating a large block of memory (1MB).\n";
    void* ptr3 = secure_malloc(1024 * 1024);  // 1MB allocation
    secure_free(ptr3);

    // Test Case 4: Allocate a small block of memory (10 bytes)
    std::cout << "\nTest Case 4: Allocating a small block (10 bytes).\n";
    void* ptr4 = secure_malloc(10);  // Small allocation
    secure_free(ptr4);

    // Test Case 5: Allocate memory for 100 integers (4 bytes each)
    std::cout << "\nTest Case 5: Allocating memory for 100 integers (400 bytes).\n";
    void* ptr5 = secure_malloc(100 * sizeof(int));
    if (ptr5 != nullptr) {
        secure_free(ptr5);
    }

    // Test Case 6: Freeing nullptr (should just print a warning)
    std::cout << "\nTest Case 6: Freeing a nullptr.\n";
    secure_free(nullptr);

    // Test Case 7: Allocate and initialize 100 bytes (use the allocated memory)
    std::cout << "\nTest Case 7: Allocating and initializing 100 bytes.\n";
    void* ptr7 = secure_malloc(100);
    if (ptr7 != nullptr) {
        std::memset(ptr7, 1, 100);  // Initialize memory to 1
        secure_free(ptr7);
    }

    // Test Case 8: Allocate a very large block (e.g., 1GB)
    std::cout << "\nTest Case 8: Allocating a very large block of memory (1GB).\n";
    void* ptr8 = secure_malloc(1024 * 1024 * 1024);  // 1GB allocation
    secure_free(ptr8);

    // Test Case 9: Allocate a very small block of memory (1 byte)
    std::cout << "\nTest Case 9: Allocating a very small block (1 byte).\n";
    void* ptr9 = secure_malloc(1);  // 1 byte allocation
    secure_free(ptr9);

    // Test Case 10: Allocate the maximum possible size (SIZE_MAX)
    std::cout << "\nTest Case 10: Allocating the maximum possible size (SIZE_MAX).\n";
    void* ptr10 = secure_malloc(SIZE_MAX);  // This may fail depending on system constraints
    secure_free(ptr10);

    // Test Case 11: Allocating a memory block and setting values to check initialization
    std::cout << "\nTest Case 11: Allocating and setting values.\n";
    void* ptr11 = secure_malloc(5 * sizeof(int));  // 5 integers
    if (ptr11 != nullptr) {
        int* arr = (int*)ptr11;
        for (int i = 0; i < 5; ++i) {
            arr[i] = i + 1;  // Set values to verify the allocation
        }
        for (int i = 0; i < 5; ++i) {
            std::cout << "Element " << i << ": " << arr[i] << std::endl;
        }
        secure_free(ptr11);
    }

    // Test Case 12: Allocating and freeing memory multiple times
    std::cout << "\nTest Case 12: Allocating and freeing memory multiple times.\n";
    void* ptr12 = secure_malloc(10);
    secure_free(ptr12);
    secure_free(ptr12);  // Freeing the same memory again should print a warning

    // Test Case 13: Allocating a very large size to check overflow handling
    std::cout << "\nTest Case 13: Allocating a very large size.\n";
    void* ptr13 = secure_malloc(SIZE_MAX / 2);  // Half of the maximum possible size
    secure_free(ptr13);

    // Test Case 14: Allocating zero elements but a non-zero size (should return nullptr)
    std::cout << "\nTest Case 14: Allocating zero elements with a non-zero size.\n";
    void* ptr14 = secure_malloc(0);  // Zero size allocation
    secure_free(ptr14);

    // Test Case 15: Allocate a large memory block, use it and free it
    std::cout << "\nTest Case 15: Allocating a large memory block and using it.\n";
    void* ptr15 = secure_malloc(50000);  // 50,000 bytes
    if (ptr15 != nullptr) {
        std::memset(ptr15, 2, 50000);  // Initialize memory with a different value
        secure_free(ptr15);
    }

    return 0;
}