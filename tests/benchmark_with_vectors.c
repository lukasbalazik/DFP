#include <stdio.h>
#include <sys/time.h>

#if __has_include(<time.h>)
#include <time.h>
#endif

#include "DFP/ipv4.h"
#include "DFP/domain.h"
#include "vector.h"
#include "readfile.h"


int main(int argc, char **argv)
{
    char *suricata = read_file("log_examples/suricata.log");
    char *apache = read_file("log_examples/apache_access.log");
    
    vector domain_list;
    vector_init(&domain_list);
    
    vector ip_list;
    vector_init(&ip_list);
    
    struct timespec start, end;
    double elapsed;

    /* IP DFP Benchmark */
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    ip_list = get_all_ips(suricata);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;

    printf("IPv4 DFP benchmark with vectors parsing takes: %f\n", elapsed);

    /* Domain DFP Benchmark */
    clock_gettime(CLOCK_MONOTONIC, &start);

    domain_list = get_all_domains(apache);

    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed = ((end.tv_sec - start.tv_sec) * 1e9 + end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Domain DFP benchmark with vectors parsing takes: %f\n", elapsed);

    // Print all IP
    //for (int i = 0; i < ip_list.pfVectorTotal(&ip_list); i++) {
    //    printf("ip: %s\n", (char*)domain_list.pfVectorGet(&ip_list, i));
    //}
    
    // Print all Domain
    //for (int i = 0; i < domain_list.pfVectorTotal(&domain_list); i++) {
    //    printf("domain: %s\n", (char*)domain_list.pfVectorGet(&domain_list, i));
    //}

    return 0;
}
