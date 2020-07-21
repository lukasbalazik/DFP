#ifndef DFP_DOMAIN_H
#define DFP_DOMAIN_H

#include "iterator.h"
#include "vector.h"

int allowed_char(char *);
int is_domain(char *, char *, char *);

void domain_iterator_init(iterator *, char *, int);

char *iterate_domain(iterator *);
vector get_all_domains(char *);

#endif
