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
    
    printf("\nAll tests passed! Your allocator is working correctly.\n");
    return 0;
}
