#ifndef UTIL_DYNARR_H
#define UTIL_DYNARR_H

#include <stdlib.h>
#include <debug.h>

#define DYNARR_INITIAL_CAPACITY 100

#define DYNARR_DEF(NAME, TYPE)                                                                     \
    typedef struct {                                                                               \
        int size;                                                                                  \
        int capacity;                                                                              \
        TYPE * data;                                                                               \
    } DynArr##NAME;                                                                                \
                                                                                                   \
    void DynArr##NAME##_Init(DynArr##NAME *);                                                      \
    void DynArr##NAME##_Free(DynArr##NAME *);                                                      \
    void DynArr##NAME##_Append(DynArr##NAME *, TYPE);                                              \
    TYPE DynArr##NAME##_Get(DynArr##NAME *, int);                                                  \
    void DynArr##NAME##_Set(DynArr##NAME *, int, TYPE);                                            \
    void DynArr##NAME##_DoubleIfFull(DynArr##NAME *);

#define DYNARR_IMP(NAME, TYPE, NULLVAL)                                                            \
                                                                                                   \
    void DynArr##NAME##_Init(DynArr##NAME * da)                                                    \
    {                                                                                              \
        da->size = 0;                                                                              \
        da->capacity = DYNARR_INITIAL_CAPACITY;                                                    \
        da->data = (TYPE *)malloc(sizeof(TYPE) * DYNARR_INITIAL_CAPACITY);                         \
        CHECK_MEM(da->data);                                                                       \
                                                                                                   \
        return;                                                                                    \
                                                                                                   \
    error:                                                                                         \
        DynArr##NAME##_Free(da);                                                                   \
    }                                                                                              \
                                                                                                   \
    void DynArr##NAME##_Free(DynArr##NAME * da)                                                    \
    {                                                                                              \
        da->capacity = -1;                                                                         \
        free(da->data);                                                                            \
        da->data = NULL;                                                                           \
    }                                                                                              \
                                                                                                   \
    void DynArr##NAME##_Append(DynArr##NAME * da, TYPE val)                                        \
    {                                                                                              \
        DynArr##NAME##_DoubleIfFull(da);                                                           \
        da->data[da->size++] = val;                                                                \
    }                                                                                              \
                                                                                                   \
    TYPE DynArr##NAME##_Get(DynArr##NAME * da, int index)                                          \
    {                                                                                              \
        CHECK(index >= da->size || index < 0, "Index %d out of bounds for DynArr of size %d",      \
            index, da->size);                                                                      \
                                                                                                   \
        return da->data[index];                                                                    \
                                                                                                   \
    error:                                                                                         \
        return NULLVAL;                                                                            \
    }                                                                                              \
                                                                                                   \
    void DynArr##NAME##_Set(DynArr##NAME * da, int index, TYPE val)                                \
    {                                                                                              \
        while (index >= da->size) {                                                                \
            DynArr##NAME##_Append(da, NULLVAL);                                                    \
        }                                                                                          \
                                                                                                   \
        da->data[index] = val;                                                                     \
    }                                                                                              \
                                                                                                   \
    void DynArr##NAME##_DoubleIfFull(DynArr##NAME * da)                                            \
    {                                                                                              \
        if (da->size >= da->capacity) {                                                            \
            da->capacity *= 2;                                                                     \
            TYPE * tmp = (TYPE *)realloc(da->data, sizeof(TYPE) * da->capacity);                   \
            CHECK_MEM(da->data);                                                                   \
            CHECK_MEM(tmp);                                                                        \
            da->data = tmp;                                                                        \
        }                                                                                          \
                                                                                                   \
        return;                                                                                    \
                                                                                                   \
    error:                                                                                         \
        DynArr##NAME##_Free(da);                                                                   \
    }

#endif // UTIL_DYNARR_H
