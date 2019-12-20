#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int * _array;
    int size;
    int capacity;
}Vector;

void vInitialize(Vector * v)
{
    v->size = 0;
    v->capacity = 2;
    v->_array = malloc(sizeof(int) * v->capacity);
}

/*
 * frees the memory associated with the vector
 */
void vFinalize(Vector * v)
{
    if(v->_array)
        free(v->_array);
}

/*
 * sets val to the value at index idx
 * returns 1 if successful, 0 if out of bounds error
 */
int vGet(Vector * v, const unsigned int idx, int * val)
{
    if(idx < v->size)
    {
        *val = v->_array[idx];
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * sets the specified element to value
 * returns 1 if successful, 0 if out of bounds error
 */
int vSet(Vector * v, const unsigned int idx, const int val)
{
    if(idx < v->size)
    {
        v->_array[idx] = val;
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * assigns value to end of vector, doubles vector capacity
 */
void vPushBack(Vector * v, const int val)
{
    if(v->size >= v->capacity)
    {
        int * temp;
        v->capacity *= 2;
        temp = (int *)calloc(v->capacity, sizeof(int));
        memcpy((void *)temp, (void*)v->_array, v->size * sizeof(int));
        free(v->_array);
        v->_array = temp;
    }
    if(v->size < v->capacity)
    {
        v->_array[v->size] = val;
        v->size++;
    }
}

/*
 * decreases vector size
 */
void vPopBack(Vector * v)
{
    v->size--;
    if(v->size < (v->capacity / 4))
    {
        int * temp;
        v->capacity /= 2;
        temp = (int *)calloc(v->capacity, sizeof(int));
    }
}
