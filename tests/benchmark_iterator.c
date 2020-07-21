#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#if __has_include(<time.h>)
#include <time.h>
#endif

#include "DFP/ipv4.h"
#include "iterator.h"
#include "readfile.h"


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: ./benchmark_iterator <filename>");
        return -1;
    }

    char *ip;

    char *data = read_file(argv[1]);
    struct timespec start, end;
    double elapsed;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
  
    int datalen = strlen(data);

    int ip_count = 0;
    
    iterator i;
    ips_iterator_init(&i, data, datalen);

    while(strlen(ip = i.pfIterate(&i))) { 
        ip_count++;
        /* Print parsed IP
        printf("ip: %s\n", ip);  
        */
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Total IPS: %d\n", ip_count);
    printf("Benchmark iterator parsing takes: %f\n", elapsed);

    return 0;
}
