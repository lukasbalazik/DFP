#include <string.h>

#include "DFP/ipv4.h"
#include "iterator.h"
#include "vector.h"


void ips_iterator_init(iterator *i, char *data, int datalen)
{
    i->pfIterate = iterate;
    i->original_position = data;
    i->actual_position = data;
    i->original_data_length = datalen;
    i->total_parsed = 0;
}


char *iterate(iterator *i)
{
    int len;
    for (char *p = i->actual_position; p != i->original_position+i->original_data_length; p++) {
        len = is_ipv4(p, p, i->original_position+i->original_data_length);
        if (len <= 0) {
            len = 0;
            if (p+8 < i->original_position+i->original_data_length)
                if (*(p+7) != '.' && (*(p+7)<'0'||*(p+7)>'9'))
                    p +=7;
        } else {
            *(p+len) = 0x00;
            i->actual_position = p+len;
            i->total_parsed++;
            return p;
        }
    }

    return i->original_position+i->original_data_length;
}

vector get_all_ips(char *c) {
    int datalen = strlen(c);
    
    vector founded_ip;
    vector_init(&founded_ip);

    iterator i;
    ips_iterator_init(&i, c, datalen);

    while(strlen(c = i.pfIterate(&i))) { 
        founded_ip.pfVectorAdd(&founded_ip, c);
    }

    return founded_ip;
}

int check_octet(char **p, char *cend) 
{
        int val;
        val = 0; 
        if (*p == cend) 
                return -1; 
        if ((**p < '0') || (**p > '9')) 
                return -1; 
        val += (unsigned int)(**p - '0'); 
        if (++(*p) == cend) 
                return -1; 
        if (**p == '.') 
                goto ret; 
        if (**p < '0' || **p > '9') 
                return -1; 
        val = val * 10 + (unsigned int)(**p - '0'); 
        if (++(*p) == cend) 
                return -1; 
        if (**p == '.') 
                goto ret; 
        if (**p < '0' || **p > '9') 
                return -1; 
        val = val * 10 + (unsigned int)(**p - '0'); 
        ++(*p); 
        if (**p != '.') 
                return -8; 
ret: 
        ++(*p); 
        if (val > 255) 
                return -1;

        return val;

}

int is_ipv4(char *p, char *cbegin, char *cend)
{
        int val;
        
        if (check_octet(&p, cend) < 0)
                return -1; 
        if (check_octet(&p, cend) < 0)
                return -1; 
        if (check_octet(&p, cend) < 0)
                return -1; 

//////////

        val = 0; 
        if (p == cend) 
                return -1; 
        if ((*p < '0') || (*p > '9')) 
                return -1; 
        val += (unsigned int)(*p - '0'); 
        if (++p == cend) 
                goto ret;
        if (*p < '0' || *p > '9') 
                goto ret;
        val = val * 10 + (unsigned int)(*p - '0'); 
        if (++p == cend) 
                goto ret;
        if (*p < '0' || *p > '9') 
                goto ret;
        val = val * 10 + (unsigned int)(*p - '0'); 
        ++p;
ret: 
        if (val > 255) 
                return -1;


        return p-cbegin;
}
