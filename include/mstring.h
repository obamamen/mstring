/* ================================== *\
 @file     mstring.h
 @project  mstring
 @author   moosm
 @date     11/20/2025
*\ ================================== */

// templates

// ------------------------------------

///////////////////////////////////////
// ...
///////////////////////////////////////

// ------------------------------------
// ...
// ------------------------------------

#ifndef MSTRING_MSTRING_H
#define MSTRING_MSTRING_H
///////////////////////////////////////
// mstring declaration
///////////////////////////////////////

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

// ------------------------------------
// tries to preallocate the size needed.
// size 0,
// capacity arg.
// ------------------------------------
// is null terminated.
mstring mstring_new_prealloc(int size);

// ------------------------------------
// fully null string meaning 0 capacity.
// ------------------------------------
// ! not null terminated.
mstring mstring_new_null();

// ------------------------------------
// size 0, capacity 1.
// ------------------------------------
// is null terminated.
mstring mstring_new_empty();

// ------------------------------------
// will allocate enough memory.
// ------------------------------------
// is null terminated.
mstring mstring_new(int size);

// ------------------------------------
// will copy arg into a new mstring.
// tight size and cap.
// ------------------------------------
// is null terminated.
mstring mstring_new_from_cstring(const char* cs);

// ------------------------------------
// will copy arg into a new mstring.
// tight size and cap.
// ------------------------------------
// is null terminated.
mstring mstring_new_from(mstring);

// ------------------------------------
// will move arg into a new mstring.
// tight size and cap.
// ------------------------------------
// ! other will be nulled fully.
// is null terminated.
mstring mstring_steal(mstring* other);

// ------------------------------------
// will delete 'free' the mstring.
// ------------------------------------
// ! won't clear it, use mstring_clear().
// mstring* will be nulled.
void mstring_delete(mstring* ms);

// ------------------------------------
// will return the underlying c string.
// ------------------------------------
// ! can be null or non-null-terminated.
const char* mstring_get(mstring ms);

// ------------------------------------
// returns underlying size.
// ------------------------------------
int mstring_size(mstring ms);

// ------------------------------------
// returns underlying capacity.
// ------------------------------------
// capacity means with the terminator.
int mstring_capacity(mstring ms);


// ------------------------------------
// fills mstring with char.
// ------------------------------------
void mstring_fill(mstring, char);

// ------------------------------------
// safely resets size to 0.
// ------------------------------------
// ! won't correct nulled strings.
// will be correctly terminated.
void mstring_reset(mstring);

// ------------------------------------
// appends mstring to mstring*.
// meaning copying the bytes, and resizing
// ------------------------------------
// might realloc.
void mstring_append(mstring*, mstring);

// ------------------------------------
// resizes size.
// ------------------------------------
// might realloc.
void mstring_resize(mstring*, int);


#ifdef MSTRING_IMPLEMENTATION
///////////////////////////////////////
// mstring implementations
///////////////////////////////////////

typedef
struct internal_mstring
{
    int size;
    int capacity;
    char data[];
}
internal_mstring_t;

///////////////////////////////////////
// customizable memory management
///////////////////////////////////////
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


///////////////////////////////////////
// private
///////////////////////////////////////

inline static mstring mstring_alloc(const int bytes)
{
    mstring ms = (mstring) MSTRING_MALLOC(sizeof(struct internal_mstring) + bytes);
    ms->capacity = bytes;
    ms->size = 0;
    return ms;
}

inline static void mstring_realloc(mstring* ms, const int bytes)
{
    if (!ms || !(*ms)) return;

    mstring nms = (mstring) MSTRING_REALLOC(*ms, sizeof(struct internal_mstring) + bytes);
    if (nms == 0) return;

    nms->capacity = bytes;
    *ms = nms;
}


///////////////////////////////////////
// public
///////////////////////////////////////

mstring mstring_new_prealloc(const int size)
{
    mstring ms = (mstring) MSTRING_MALLOC(sizeof(struct internal_mstring) + MSTRING_stc(size));
    ms->capacity = MSTRING_stc(size);
    ms->size = 0;
    ms->data[0] = '\0';
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

void mstring_fill(mstring ms, char c)
{
    if (!ms) return;
    for (int i = 0; i < mstring_size(ms); i++) ms->data[i] = c;
}

void mstring_reset(mstring ms)
{
    if (!ms) return;
    if (ms->capacity == 0) return;
    ms->data[0] = '\0';
    ms->size = 0;
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