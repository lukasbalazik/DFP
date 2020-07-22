#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#if __has_include(<time.h>)
#include <time.h>
#endif

#include "DFP/ipv4.h"
#include "DFP/hash.h"
#include "DFP/domain.h"
#include "iterator.h"
#include "readfile.h"


int main(int argc, char **argv)
{
    iterator i;
    
    char *suricata = read_file("log_examples/suricata.log");
    char *apache = read_file("log_examples/apache_access.log");
    char *hashfile = read_file("log_examples/hash.log");

    char *ip;
    char *domain;
    char *hash;

    int ip_count = 0;
    int domain_count = 0;
    int hash_count = 0;
    int datalen = 0;

    struct timespec start, end;
    double elapsed;
   
    /* IP DFP Benchmark Iterator */ 
    clock_gettime(CLOCK_MONOTONIC, &start);
  
    datalen = strlen(suricata);

    ips_iterator_init(&i, suricata, datalen);

    while(strlen(ip = i.pfIterate(&i))) { 
        ip_count++;
        /* Print parsed IP
        printf("ip: %s\n", ip);  
        */
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    printf("IPv4 DFP benchmark iterator parsing takes: %f and parsed %d ip addresses\n", elapsed, ip_count);


    /* Domain DFP Benchmark Iterator */ 
    clock_gettime(CLOCK_MONOTONIC, &start);
  
    datalen = strlen(apache);

    domain_iterator_init(&i, apache, datalen);

    while(strlen(domain = i.pfIterate(&i))) { 
        domain_count++;
        /* Print parsed Domains
        printf("Domain: %s\n", domain);  
        */
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Domain DFP benchmark iterator parsing takes: %f and parsed %d domains\n", elapsed, domain_count);

    /* Hash DFP Benchmark Iterator */ 
    clock_gettime(CLOCK_MONOTONIC, &start);
  
    datalen = strlen(hashfile);

    hash_iterator_init(&i, hashfile, datalen, MD5);

    while(strlen(hash = i.pfIterate(&i))) { 
        hash_count++;
        /* Print parsed Hash
        printf("Hash: %s\n", hash);  
        */
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Hash DFP benchmark iterator parsing takes: %f and parsed %d hashes\n", elapsed, hash_count);

    return 0;
}
