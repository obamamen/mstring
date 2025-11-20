/* ================================== *\
 @file     mstring.h
 @project  mstring
 @author   moosm
 @date     11/20/2025
*\ ================================== */

#ifndef MSTRING_MSTRING_H
#define MSTRING_MSTRING_H
//////////////////////////////////////
// mstring declaration
//////////////////////////////////////

// ------------------------------------
// mstring struct
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
mstring mstring_new_from_cstring(const char* cs);
mstring mstring_new_from(mstring);
mstring mstring_steal(mstring*);

void mstring_delete(mstring* ms);

const char* mstring_get(mstring ms);
int mstring_size(mstring ms);
int mstring_capacity(mstring ms);

void mstring_realloc(mstring* ms, int bytes);

void mstring_append(mstring*, mstring);
void mstring_resize(mstring*, int);


#ifdef MSTRING_IMPLEMENTATION
//////////////////////////////////////
// mstring implementations
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

mstring mstring_new_from_cstring(const char* cs)
{
    if (!cs) return mstring_new_null();

    int size = 0;
    const char* p = cs;
    while ((*p++) != '\0') size++;

    mstring ms = mstring_new(size);
    for (int i = 0; i < size; i++) ms->data[i] = cs[i];

    return ms;
}

mstring mstring_new_from(mstring ms)
{
    if (!ms) return mstring_new_null();

    mstring rms = mstring_new(ms->size);
    for (int i = 0; i < mstring_size(ms); i++) rms->data[i] = ms->data[i];
    return rms;
}

mstring mstring_steal(mstring* other)
{
    if (!other) return mstring_new_null();
    mstring ms = (*other);
    (*other) = 0;
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

void mstring_realloc(mstring* ms, const int bytes)
{
    if (!ms || !(*ms)) return;

    mstring nms = (mstring) MSTRING_REALLOC(*ms, sizeof(struct internal_mstring) + bytes);
    if (nms == 0) return;

    nms->capacity = bytes;
    *ms = nms;
}

void mstring_append(mstring* to, mstring from)
{
    if (!to || !(*to) || !from) return;

    int old_size = (*to)->size;
    mstring_realloc(to, MSTRING_stc(old_size + from->size));

    if ((*to)->capacity < MSTRING_stc(old_size + from->size)) return;

    (*to)->size = old_size + from->size;
    for (int i = 0; i < from->size; i++) { (*to)->data[old_size+i] = from->data[i]; }
    (*to)->data[(*to)->size] = '\0';
}

void mstring_resize(mstring* ms, const int new_size)
{
    if (!ms || !(*ms)) return;

    mstring_realloc(ms, MSTRING_stc(new_size));
    if ((*ms)->capacity < MSTRING_stc(new_size)) return;

    for (int i = (*ms)->size; i < (*ms)->capacity; i++) (*ms)->data[i] = 0;
    (*ms)->size = new_size;
    for (int i = (*ms)->size; i < (*ms)->capacity; i++) (*ms)->data[i] = 0;
}


#endif


#endif //MSTRING_MSTRING_H