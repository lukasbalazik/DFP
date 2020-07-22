#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "DFP/hash.h"
#include "vector.h"
#include "iterator.h"

void hash_iterator_init(iterator *i, char *data, int datalen, int hashtype)
{
    i->pfIterate = iterate_hash;
    i->original_position = data;
    i->actual_position = data;
    i->original_data_length = datalen;
    i->total_parsed = 0;
    i->hash_type = hashtype;
}

vector get_all_hashes(char *c, int hashtype) {
    int datalen = strlen(c);

    vector found_hashes;
    vector_init(&found_hashes);

    iterator i;
    hash_iterator_init(&i, c, datalen, hashtype);

    while(strlen(c = i.pfIterate(&i))) {
        found_hashes.pfVectorAdd(&found_hashes, c);
    }

    return found_hashes;
}

char *iterate_hash(iterator *i)
{
    int len;
    for (char *p = i->actual_position; p != i->original_position+i->original_data_length; p++) {
        len = is_hash(p, p, i->original_position+i->original_data_length);
        if (len == i->hash_type) {
            *(p+len) = 0x00;
            i->actual_position = p+len;
            i->total_parsed++;
            return p;
        }
        p += len;
        if (p+i->hash_type/2 < i->original_position+i->original_data_length)
            if (!hash_char(p+i->hash_type/2)) {
                p +=i->hash_type/2;
            }
    }

    return i->original_position+i->original_data_length;
}


int hash_char(char *c)
{
    if (*c >= 'a' && *c <= 'f') { 
        return 1;
    } else if (*c >= 'A' && *c <= 'F') {
        return 1;
    } else if (*c >= '0' && *c <= '9') {
        return 1;
    } 

    return 0;
}

int is_hash(char *p, char *cbegin, char *cend) 
{
    while (1) {
        if (p == cend) {
            return -1;
        }

        if (!hash_char(p)) 
            break;

        p++;
    }

    return p-cbegin;
}

