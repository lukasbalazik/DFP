#ifndef ITERATOR_H
#define ITERATOR_H

typedef struct sIterator iterator;

struct sIterator {
    void (*pfSetupIterator)(iterator *, char *, int);
    char *(*pfIterate)(iterator *);
    char *original_position;
    char *actual_position;
    int original_data_length;
    int total_parsed;
    int hash_type;
};

#endif
