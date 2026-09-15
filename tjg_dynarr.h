#ifndef TJG_DYNARR_H_
#define TJG_DYNARR_H_

#include <assert.h>
#include <stdlib.h>

#ifndef TJG_DYNARR_INIT_CAPACITY
#define TJG_DYNARR_INIT_CAPACITY 8
#endif // TJG_DYNARR_INIT_CAPACITY

#define tjg_dynarr_reserve(dynarr, additional)                                 \
    do {                                                                       \
        size_t min_capacity = (dynarr)->len + (additional);                    \
        if (min_capacity > (dynarr)->capacity) {                               \
            if ((dynarr)->capacity == 0) {                                     \
                (dynarr)->capacity = TJG_DYNARR_INIT_CAPACITY;                 \
            }                                                                  \
            while (min_capacity > (dynarr)->capacity) {                        \
                (dynarr)->capacity *= 2;                                       \
            }                                                                  \
            (dynarr)->items = realloc(                                         \
                (dynarr)->items, (dynarr)->capacity * sizeof(*(dynarr)->items) \
            );                                                                 \
            assert((dynarr)->items != NULL && "Out of memory!");               \
        }                                                                      \
    } while (0)

#define tjg_dynarr_init(dynarr) \
    do {                        \
        (dynarr)->items = NULL; \
        (dynarr)->len = 0;      \
        (dynarr)->capacity = 0; \
    } while (0)

#define tjg_dynarr_init_capacity(dynarr, capacity) \
    do {                                           \
        tjg_dynarr_init((dynarr));                 \
        tjg_dynarr_reserve((dynarr), (capacity));  \
    } while (0)

#define tjg_dynarr_destroy(dynarr) free((dynarr)->items)

#define tjg_dynarr_append(dynarr, item)            \
    do {                                           \
        tjg_dynarr_reserve((dynarr), 1);           \
        (dynarr)->items[(dynarr)->len++] = (item); \
    } while (0)

#define tjg_dynarr_foreach(T, item, dynarr) \
    for (T *item = (dynarr)->items; item < (dynarr)->items + (dynarr)->len; ++item)


#ifdef TJG_STRIP_PREFIX
    #define dynarr_reserve tjg_dynarr_reserve
    #define dynarr_init tjg_dynarr_init
    #define dynarr_init_capacity tjg_dynarr_init_capacity
    #define dynarr_destroy tjg_dynarr_destroy
    #define dynarr_append tjg_dynarr_append
    #define dynarr_foreach tjg_dynarr_foreach
#endif // TJG_STRIP_PREFIX


#endif // TJG_DYNARR_H_
