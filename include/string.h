/* ================================== *\
 @file     string.h
 @project  string
 @author   moosm
 @date     11/20/2025
*\ ================================== */

#ifndef STRING_STRING_H
#define STRING_STRING_H
//////////////////////////////////////
// string declaration
//////////////////////////////////////

// ------------------------------------
// string struct
// ------------------------------------
typedef
struct string
{
    char* data;
    int size;
    int capacity;
}
string_t;

#define STRING_NULL (0)
#define STRING_NULL_STRING (struct string){STRING_NULL,0,0}

struct string string_new_null();
struct string string_new_empty();
struct string string_new(int size);
void string_delete(struct string *this);

const char* string_get(struct string s);

extern const char NULL_STRING[];


#ifdef STRING_IMPLEMENTATION
//////////////////////////////////////
// string implementations
//////////////////////////////////////

// ------------------------------------
// customizable memory management
// ------------------------------------
#ifndef STRING_MALLOC
#   define STRING_MALLOC malloc
#endif
#ifndef STRING_FREE
#   define STRING_FREE free
#endif
#ifndef STRING_REALLOC
#   define STRING_REALLOC realloc
#endif

// --------- size to capacity ---------
#define sstc(size) (size+1)

const char NULL_STRING[] = "[null]";

struct string string_new_null()
{
    return STRING_NULL_STRING;
}

struct string string_new(const int size)
{
    struct string s;
    s.data = (char*)STRING_MALLOC(sizeof(char) * sstc(size));
    for (int i = 0; i < sstc(size); i++) s.data[i] = 0;
    s.size = size;
    s.capacity = sstc(size);
    return s;
}


struct string string_new_empty()
{
    return string_new(0);
}

void string_delete(struct string* this)
{
    if (this == 0) return;
    if (this->data) STRING_FREE(this->data);
    this->data = 0;
    this->size = 0;
    this->capacity = 0;
}

const char* string_get(const struct string s)
{
    return s.data ? s.data : NULL_STRING;
}


#endif


#endif //STRING_STRING_H