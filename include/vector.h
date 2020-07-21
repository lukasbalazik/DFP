#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE -1
#define SUCCESS 0

typedef struct sVector vector;

typedef struct vectorList {
    void **items;
    int capacity;
    int total;
} vectorList;

struct sVector {
    vectorList vectorList;
    int (*pfVectorTotal)(vector *);
    int (*pfVectorResize)(vector *, int);
    int (*pfVectorAdd)(vector *, void *);
    int (*pfVectorSet)(vector *, int, void *);
    void *(*pfVectorGet)(vector *, int);
    int (*pfVectorDelete)(vector *, int);
    int (*pfVectorFree)(vector *);
};

int vectorTotal(vector *);
int vectorResize(vector *, int);
int vectorPushBack(vector *, void *);
int vectorSet(vector *, int, void *);
void *vectorGet(vector *, int);
int vectorDelete(vector *, int);
int vectorFree(vector *);
void vector_init(vector *);

#endif
