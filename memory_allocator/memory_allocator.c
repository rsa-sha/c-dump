/*
ASSUMING WE ARE USING LINUX/UNIX LIKE SYSTEM
*/
#include <assert.h>
#include <stdio.h>
#include <unistd.h>


/*----------------------------------------*/
void *my_malloc(size_t size_requested){
    void *block;
    block = sbrk(size_requested);
    if (block == (void *) -1){
        return NULL;
    }
    return block;
}

int memory_allocation_test_result(){
    int *ptr;
    ptr = (int *) my_malloc(sizeof(int));
    if (ptr == NULL){
        return 1;
    }
    *ptr = 10;
    printf("Value of ptr: %d\n", *ptr);
    return 0;
}
/*----------------------------------------*/





int main(char argc, char *argv[]){
    if(argc!=1){
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    // run memeory alllocation tests
    if (memory_allocation_test_result() == 0){
        printf("Memory allocation test passed\n");
    } else {
        printf("Memory allocation test failed\n");
    }
    return 0;
}