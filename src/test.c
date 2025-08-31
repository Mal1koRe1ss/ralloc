#include "ralloc.h"
#include <stdio.h>
#include <string.h>

int main() {
    printf("\n1. Testing basic allocation...\n");
    int *numbers = (int *)rallocmem(10 * sizeof(int));
    if (numbers == NULL) {
        printf("FAIL: Basic allocation failed\n");
        return 1;
    }
    printf("PASS: Basic allocation succeeded\n");
    
    printf("\n2. Testing memory usage...\n");
    for (int i = 0; i < 10; i++) {
        numbers[i] = i * i;
    }
    
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        sum += numbers[i];
    }
    printf("PASS: Memory usage test (sum of squares: %d)\n", sum);
    
    printf("\n3. Testing memory freeing...\n");
    rallocfree(numbers);
    printf("PASS: Memory freed successfully\n");
    
    printf("\n4. Testing multiple allocations...\n");
    void *pointers[5];
    for (int i = 0; i < 5; i++) {
        pointers[i] = rallocmem(100 * (i + 1));
        if (pointers[i] == NULL) {
            printf("FAIL: Allocation %d failed\n", i);
            return 1;
        }
        printf("Allocation %d successful at %p\n", i, pointers[i]);
    }
    
    printf("\n5. Freeing all allocations...\n");
    for (int i = 0; i < 5; i++) {
        rallocfree(pointers[i]);
        printf("Freed allocation %d\n", i);
    }
    
    printf("\n6. Testing large allocation...\n");
    size_t large_size = 1024 * 1024; // 1MB
    char *large_buffer = (char *)rallocmem(large_size);
    if (large_buffer == NULL) {
        printf("FAIL: Large allocation failed\n");
        return 1;
    }
    
    memset(large_buffer, 'A', large_size);
    large_buffer[large_size - 1] = '\0';
    printf("PASS: Large allocation and usage successful\n");
    
    rallocfree(large_buffer);
    printf("PASS: Large buffer freed successfully\n");
   
    printf("\n7. Testing reallocation...\n");
    int *new_numbers = (int *)rallocmem(10 * sizeof(int));
    if (new_numbers == NULL) {
        printf("FAIL: Allocation for realloc test failed\n");
        return 1;
    }

    for (int i = 0; i < 10;i++) {
        new_numbers[i] = i * 2;
    }

    int *resized = (int *)rreallocmem(new_numbers, 20 * sizeof(int));
    if (resized == NULL) {
        printf("FAIL: Reallocation failed\n");
        return 1;
    }
    printf("PASS: Reallocation successful\n");
    rallocfree(resized);

    printf("\n8. Testing NULL reallocation...\n");
    void *new_alloc = rreallocmem(NULL, 100);
    if (new_alloc == NULL) {
        printf("FAIL: NULL reallocation failed\n");
        return 1;
    }
    printf("PASS: NULL reallocation successful\n");
    rallocfree(new_alloc);

    printf("\n9. Testing zero-size reallocation...\n");
    void *ptr = rallocmem(100);
    void *freed_ptr = rreallocmem(ptr, 0);
    if (freed_ptr != NULL) {
        printf("FAIL: Zero-size reallocation failed\n");
        return 1;
    }
    printf("PASS: Zero-size reallocation successful\n");

    printf("\n11. Testing memory contents preservation after realloc...\n");
    int *test_data = (int *)rallocmem(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        test_data[i] = i + 1;
    }
    test_data = (int *)rreallocmem(test_data, 20 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        if (test_data[i] != i + 1) {
            printf("FAIL: Data not preserved after realloc\n");
            return 1;
        }
    }
    printf("PASS: Data preservation test successful\n");
    rallocfree(test_data);

    printf("\nAll tests passed! Your allocator is working correctly.\n");
    return 0;
}
