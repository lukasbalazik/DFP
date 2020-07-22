#ifndef DFP_DOMAIN_H
#define DFP_DOMAIN_H

#include "iterator.h"
#include "vector.h"

#define MD5 32
#define SHA1 40
#define SHA256 64
#define SHA512 128

int hash_char(char *);
int is_hash(char *, char *, char *);

void hash_iterator_init(iterator *, char *, int, int);

char *iterate_hash(iterator *);
vector get_all_hashes(char *, int);

#endif
