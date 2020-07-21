#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "DFP/domain.h"
#include "DFP/ipv4.h"
#include "vector.h"
#include "iterator.h"

void domain_iterator_init(iterator *i, char *data, int datalen)
{
    i->pfIterate = iterate_domain;
    i->original_position = data;
    i->actual_position = data;
    i->original_data_length = datalen;
    i->total_parsed = 0;
}

vector get_all_domains(char *c) {
    int datalen = strlen(c);

    vector founded_domains;
    vector_init(&founded_domains);

    iterator i;
    domain_iterator_init(&i, c, datalen);

    while(strlen(c = i.pfIterate(&i))) {
        if (is_ipv4(c, c, i.original_position+i.original_data_length) < 0)
            founded_domains.pfVectorAdd(&founded_domains, c);
    }

    return founded_domains;
}

char *iterate_domain(iterator *i)
{
    int len;
    for (char *p = i->actual_position; p != i->original_position+i->original_data_length; p++) {
        len = is_domain(p, p, i->original_position+i->original_data_length);
        if (len <= 0) {
            len = 0;
        } else {
            *(p+len) = 0x00;
            i->actual_position = p+len;
            i->total_parsed++;
            return p;
        }
    }

    return i->original_position+i->original_data_length;
}


int allowed_char(char *c)
{
    if (*c >= 97 && *c <= 122) { 
        return 1;
    } else if (*c >= 65 && *c <= 90) {
        return 1;
    } else if (*c >= 48 && *c <= 57) {
        return 1;
    } 

    return 0;
}

int is_domain(char *p, char *cbegin, char *cend) 
{
    int haveDot = 0;

    while (1) {
        if (p == cend) {
            return -1;
        }

        if (*p == '.') {
            if (allowed_char(p+1))
                haveDot = 1;
            else
                return -1;
        }

        if (allowed_char(p)) {
        } else if (*p == '-' || *p == '.') {
        } else {
            if (!haveDot) {
                return -1;
            }
            break;
        }

        p++;
    }

    return p-cbegin;
}

