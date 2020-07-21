#include <stdio.h>
#include <sys/time.h>

#if __has_include(<time.h>)
#include <time.h>
#endif

#include "DFP/ipv4.h"
#include "vector.h"
#include "readfile.h"


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./benchmark_with_vectors <filename>");
        return -1;
    }

    char *data = read_file(argv[1]);
    
    vector ip_list;
    vector_init(&ip_list);
    
    struct timespec start, end;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    ip_list = get_all_ips(data);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Benchmark with vectors parsing takes: %f\n", elapsed);

    /* Print all IP
    for (i = 0; i < ip_list.pfVectorTotal(&ip_list); i++) {
        printf("ip: %s\n", (char*)ip_list.pfVectorGet(&ip_list, i));
    }
    */

    return 0;
}
