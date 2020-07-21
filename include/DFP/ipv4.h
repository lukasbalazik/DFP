#ifndef IPV4_H
#define IPV4_H

#include "iterator.h"
#include "vector.h"

int parse_octet(char **, char *);
int is_ipv4(char *, char *, char *);

void setup_iterator(iterator *, char *, int);
void ips_iterator_init(iterator *, char *, int);

char *iterate(iterator *);
vector get_all_ips(char *);

#endif
