#ifndef DFP_IPV4_H
#define DFP_IPV4_H

#include "iterator.h"
#include "vector.h"

int parse_octet(char **, char *);
int is_ipv4(char *, char *, char *);

void ips_iterator_init(iterator *, char *, int);

char *iterate_ip(iterator *);
vector get_all_ips(char *);

#endif
