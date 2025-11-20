/* ================================== *\
 @file     mstring.h
 @project  string
 @author   moosm
 @date     11/20/2025
*\ ================================== */

#ifndef MSTRING_MSTRING_H
#define MSTRING_MSTRING_H
//////////////////////////////////////
// string declaration
//////////////////////////////////////

// ------------------------------------
// string struct
// ------------------------------------
typedef
struct internal_mstring
internal_mstring_t;

typedef struct internal_mstring* mstring;

#define MSTRING_NULL (0)
#define MSTRING_NULL_INTERNAL_MSTRING (struct internal_mstring){0, 0}
#define MSTRING_NULL_MSTRING (mstring){STRING_NULL}

mstring mstring_alloc(int bytes);
mstring mstring_new_null();
mstring mstring_new_empty();
mstring mstring_new(int size);
mstring mstring_new_from(const char* s);
void mstring_delete(mstring* ms);

const char* mstring_get(mstring ms);
int mstring_size(mstring ms);
int mstring_capacity(mstring ms);

extern const char NULL_MSTRING[];


#ifdef MSTRING_IMPLEMENTATION
//////////////////////////////////////
// string implementations
//////////////////////////////////////

typedef
struct internal_mstring
{
    int size;
    int capacity;
    char data[];
}
internal_mstring_t;

// ------------------------------------
// customizable memory management
// ------------------------------------
#ifndef MSTRING_MALLOC
#   define MSTRING_MALLOC malloc
#endif
#ifndef MSTRING_FREE
#   define MSTRING_FREE free
#endif
#ifndef MSTRING_REALLOC
#   define MSTRING_REALLOC realloc
#endif

// --------- size to capacity ---------
#define MSTRING_stc(size) (size+1)

const char NULL_STRING[] = "[null]";

mstring mstring_alloc(const int bytes)
{
    mstring ms = (mstring) MSTRING_MALLOC(sizeof(struct internal_mstring) + bytes);
    ms->capacity = bytes;
    ms->size = 0;
    return ms;
}

mstring mstring_new_null()
{
    mstring ms = mstring_alloc(0);
    (*ms) = MSTRING_NULL_INTERNAL_MSTRING;
    return ms;
}

mstring mstring_new(const int size)
{
    mstring ms = mstring_alloc(MSTRING_stc(size));
    for (int i = 0; i < MSTRING_stc(size); i++) ms->data[i] = 0;
    ms->size = size;
    return ms;
}

mstring mstring_new_empty()
{
    return mstring_new(0);
}

mstring mstring_new_from(const char* s)
{
    if (!s) return mstring_new_null();

    int size = 0;
    const char* p = s;
    while ((*p++) != '\0') size++;

    mstring ms = mstring_new(size);
    for (int i = 0; i < size; i++) ms->data[i] = s[i];

    return ms;
}

void mstring_delete(mstring* ms)
{
    if (!ms) return;
    if (!*ms) return;

    MSTRING_FREE(*ms);
    *ms = NULL;
}

const char* mstring_get(mstring ms)
{
    return ((ms != 0) && (ms->capacity != 0))
        ? ms->data
        : 0;
}

int mstring_size(mstring ms)
{
    return (ms != 0) ? ms->size : 0;
}

int mstring_capacity(mstring ms)
{
    return (ms != 0) ? ms->capacity : 0;
}


#endif


#endif //MSTRING_MSTRING_H