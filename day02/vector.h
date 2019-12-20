#ifndef VECTOR_H
#define	VECTOR_H
typedef struct
{
    int * _array;
    int size;
    int capacity;
}Vector;
void vInitialize(Vector * v);
void vFinalize(Vector * v);
int vGet(Vector * v, const unsigned int idx, int * val);
int vSet(Vector * v, const unsigned int idx, const int val);
void vPushBack(Vector * v, const int val);
void vPopBack(Vector * v);
#endif	/* VECTOR_H */

